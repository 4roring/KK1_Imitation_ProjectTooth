#include "stdafx.h"
#include "ACommander.h"
#include "PlayerOperator.h"

ACommander::ACommander()
{
}


ACommander::~ACommander()
{
	Release();
}

HRESULT ACommander::Initialize()
{
	CActor::Initialize();

	m_tInfo.vPosition = { 680.f, 2600.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	ZeroMemory(m_tInfo.matWorld, sizeof(D3DXMATRIX));

	Vector3 vInitScroll((WINCX >> 1) - m_tInfo.vPosition.x, (WINCY >> 1) - m_tInfo.vPosition.y, 0.f);
	ViewMgr->SetScroll(vInitScroll);

	m_pTexMain = TextureMgr->GetTexture(TEXT("commander_commoners"));
	m_pTexTint = TextureMgr->GetTexture(TEXT("commander_commoners_tint"));

	SetAnimFrame(0.f, 9.f, 1.f);

	m_tFrame.fCenterX = (COMMANDER_CX >> 1);
	m_tFrame.fCenterY = (COMMANDER_CY * 0.9f);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;
	
	m_fSpeed = 130.f * fScreenZoom;
	m_iMaxHp = 10;
	m_iHp = 10;
	m_bDead = false;
	m_bFlipX = false;

	// TODO: Factory에서 정할 수 있는 멤버 변수를 넣는 등 설정.
	m_pOperator = new CPlayerOperator;
	m_pOperator->SetCommander(this);

	return S_OK;
}

OBJSTATE ACommander::Update(float deltaTime)
{
	// 플레이어 작업 우선.
	m_pOperator->Update();
	
	UpdateState(deltaTime);

	// Actor 공통 작업 호출.
	CActor::Update(deltaTime);

	return STATE_PLAY;
}

void ACommander::LateUpdate()
{
	CActor::LateUpdate();
	SetAnimState();
}

void ACommander::Render()
{
	RenderShadow(80);
	RenderGroundChar();
}

void ACommander::Release()
{
	SafeDelete(m_pOperator);
}

void ACommander::UpdateState(float deltaTime)
{
	UpdateFlipX();
		
	switch (m_eCurAnimState)
	{
	case ACommander::Idle:
		if(m_fOrder > 0.f)
			m_eCurAnimState = ACommander::Order;

		if (true == m_bBuild)
			m_eCurAnimState = ACommander::Build;

		if (m_tInfo.vDir.x != 0.f || m_tInfo.vDir.y != 0.f)
			m_eCurAnimState = ACommander::Run;

		if (m_fReturn > 0.f)
			m_eCurAnimState = ACommander::ReturnHome;

		if(true == m_bDead)
			m_eCurAnimState = ACommander::Dead;
		break;
	case ACommander::Order:
		if (m_tInfo.vDir.x != 0.f || m_tInfo.vDir.y != 0.f)
			m_eCurAnimState = ACommander::RunOrder;
		
		if (m_fOrder == 0.f)
			m_eCurAnimState = ACommander::Idle;
		break;
	case ACommander::Build:
		if (m_tFrame.fFrame >= m_tFrame.fMax-0.1f)
		{
			m_bBuild = false;
			m_eCurAnimState = ACommander::Idle;
		}
		break;
	case ACommander::Run:
		Move(deltaTime);
		if (m_fOrder > 0.f)
			m_eCurAnimState = ACommander::RunOrder;

		if (true == m_bBuild)
			m_eCurAnimState = ACommander::RunBuild;

		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ACommander::Idle;
		break;
	case ACommander::RunOrder:
		Move(deltaTime);

		if(m_fOrder == 0.f)
			m_eCurAnimState = ACommander::Run;

		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ACommander::Idle;
		break;
	case ACommander::RunBuild:
		Move(deltaTime);
		if (m_tFrame.fFrame >= m_tFrame.fMax - 0.1f)
		{
			m_bBuild = false;
			m_eCurAnimState = ACommander::Run;
		}
		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ACommander::Idle;
		break;
	case ACommander::ReturnHome:
		if (m_fReturn == 0.f)
			m_eCurAnimState = ACommander::Idle;
		break;
	case ACommander::Dead:
		// TODO: 죽었을 때 처리.
		
		break;
	default:
#ifdef _DEBUG
		assert(!"Commander AnimState Error");
#endif
		break;
	}
}

void ACommander::Move(float deltaTime)
{
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vDir *= m_fSpeed * deltaTime;
	m_tInfo.vPosition += m_tInfo.vDir;

	if (true == Offset())
		ViewMgr->MoveScroll(m_tInfo.vDir);
}

void ACommander::SetAnimState()
{
	if (m_ePreAnimState != m_eCurAnimState)
	{
		switch (m_eCurAnimState)
		{
		case ACommander::Idle:
			SetAnimFrame(0.f, 9.f, 1.f);
			break;
		case ACommander::Order:
			SetAnimFrame(10.f, 19.f, 1.f);
			break;
		case ACommander::Build:
			SetAnimFrame(20.f, 21.f, 5.f);
			break;
		case ACommander::Run:
			SetAnimFrame(22.f, 31.f, 1.f);
			break;
		case ACommander::RunOrder:
			SetAnimFrame(32.f, 41.f, 1.f);
			break;
		case ACommander::RunBuild:
			SetAnimFrame(42.f, 46.f, 3.f);
			break;
		case ACommander::ReturnHome:
			SetAnimFrame(47.f, 51.f, 1.f);
			break;
		case ACommander::Dead:
			SetAnimFrame(57.f, 71.f, 1.f);
			break;
		default:
#ifdef _DEBUG
			assert(!"Commander AnimState Error");
#endif
			break;
		}
		m_ePreAnimState = m_eCurAnimState;
	}
}

bool ACommander::Offset()
{
	const Vector3& vScroll = ViewMgr->GetScroll();

	const Vector3& vPos = m_tInfo.vPosition + ViewMgr->GetScroll();

	//if (vPos.x < (WINCX >> 1) && vPos.x >(WINCX >> 1)) return true;
	//if (vPos.y < (WINCY >> 1) && vPos.y >(WINCY >> 1)) return true;

	if (m_tInfo.vDir.x > 0.f && vPos.x > (WINCX >> 1) - 2.f) return true;
	if (m_tInfo.vDir.x < 0.f && vPos.x < (WINCX >> 1) + 2.f) return true;
	if (m_tInfo.vDir.y > 0.f && vPos.y >(WINCY >> 1) - 2.f) return true;
	if (m_tInfo.vDir.y < 0.f && vPos.y < (WINCY >> 1) + 2.f) return true;

	return false;
}
