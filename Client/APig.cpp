#include "stdafx.h"
#include "APig.h"
#include "Level.h"
#include "Effect.h"
#include "DBulletEffectBridge.h"

APig::APig()
{
}


APig::~APig()
{
	Release();
}

HRESULT APig::Initialize()
{
	AActor::Initialize();
	m_pTexMain = TextureMgr->GetTexture(TEXT("pig"));
	m_pTexTint = TextureMgr->GetTexture(TEXT("pig_tint"));

	m_tUnitInfo.iAtk = 1;
	m_tUnitInfo.fAtkTime = 1.f;
	m_tUnitInfo.iRange = 4;
	m_fSpeed = 10.f;
	m_iImageCX = 32;
	m_iImageCY = 32;
	
	m_tFrame.fCenterX = float(m_iImageCX >> 1);
	m_tFrame.fCenterY = float(m_iImageCY * 0.9f);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	return S_OK;
}

OBJSTATE APig::Update(float deltaTime)
{
	if (true == m_bDestroy)
	{
		m_pLevel->SetTileObject(m_iTileIndex, nullptr);
		return STATE_DESTROY;
	}
		

	AActor::Update(deltaTime);
	if (nullptr == m_pLevel)
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

	UpdateState(deltaTime);
	if (true == CheckEnemy(m_tUnitInfo.iRange))
		m_eCurState = APig::Attack;
	return STATE_PLAY;
}

void APig::LateUpdate()
{
	AActor::LateUpdate();
	SetAnimState();
}

void APig::Render()
{
	RenderShadow(60);
	RenderActor();
}

void APig::Release()
{
}

void APig::SetTileIndexArr(int * pTileIndexArr)
{
	m_pTileIndexArr = pTileIndexArr;
}

void APig::UpdateState(float deltaTime)
{
	switch (m_eCurState)
	{
	case APig::Idle:
		m_fIdleTime += deltaTime;
		if (m_fIdleTime >= 0.7f)
		{
			SelectNextTile();
			m_eCurState = APig::Move;
		}
		break;
	case APig::Move:
		m_tInfo.vPosition += m_tInfo.vDir * m_fSpeed * deltaTime;
		if (true == CheckNextDistance())
			m_eCurState = APig::Work;
		break;
	case APig::Work:
		if (m_tFrame.fFrame >= m_tFrame.fMax - 1.f)
			m_eCurState = APig::Idle;
		break;
	case APig::Attack:
		m_fAttackDelay += deltaTime;
		if (m_fAttackDelay >= m_tUnitInfo.fAtkTime)
		{
			ShotBullet();
			m_fAttackDelay = 0.f;
		}

		if (m_fAttackDelay <= 0.7f)
			m_tFrame.fFrame = m_tFrame.fMin;

		if (false == CheckEnemy(m_tUnitInfo.iRange))
			m_eCurState = APig::Idle;
		break;
	case APig::End:
	default:
#ifdef _DEBUG
		assert(!"Pig Anim Update Error!!!");
#endif
		break;
	}
}

void APig::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case APig::Idle:
			SetAnimFrame(0.f, 0.f, 0.f);
			break;
		case APig::Move:
			SetAnimFrame(1.f, 8.f, 1.f);
			break;
		case APig::Work:
			SetAnimFrame(9.f, 24.f, 0.5f);
			break;
		case APig::Attack:
			SetAnimFrame(25.f, 28.f, 1.5f);
			m_fAttackDelay = 0.f;
			break;
		case APig::End:
		default:
#ifdef _DEBUG
			assert(!"Pig Anim Update Error!!!");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void APig::SelectNextTile()
{
	int iPreTile = m_iTileIndex;
	while (iPreTile == m_iTileIndex)
		m_iTileIndex = m_pTileIndexArr[GameMgr->GetRandom(0, 3)];

	Vector3 vNext = m_pLevel->GetCollTile(m_iTileIndex)->vPosition - m_tInfo.vPosition;
	D3DXVec3Normalize(&m_tInfo.vDir, &vNext);
}

bool APig::CheckNextDistance()
{
	Vector3 vNext = m_pLevel->GetCollTile(m_iTileIndex)->vPosition - m_tInfo.vPosition;
	if (D3DXVec3Length(&vNext) < 3.f)
		return true;
	return false;
}

void APig::ShotBullet()
{
	CGameObject* pEffect = pEffect = DObjectFactory<CEffect>::CreateBullet(m_pTarget, BULLET_PISTOL, m_tInfo.vPosition, m_tUnitInfo.iAtk);
	GameMgr->CreateObject(pEffect, OBJ_EFFECT);
}
