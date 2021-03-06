#include "stdafx.h"
#include "ACommander.h"
#include "DPlayerCommand.h"
#include "Level.h"
#include "BUnitFactory.h"
#include "DSubject.h"
#include "DAICommand.h"
#include "AStar.h"
#include "AUnit.h"
#include "DDirectlyEffectBridge.h"
#include "Effect.h"

ACommander::ACommander()
{
}


ACommander::~ACommander()
{
	Release();
}

HRESULT ACommander::Initialize()
{
	if (FAILED(AActor::Initialize())) return E_FAIL;

	InitCommander();

	m_fSpeed = 110.f * fScreenZoom;
	m_iMaxHp = 0;
	m_iHp = 0;

	m_iSelectSlot = 0;

	m_eUnit[0] = UNIT_SQUIRREL;
	m_eUnit[1] = UNIT_LIZARD;
	m_eUnit[2] = UNIT_MOLE;

	if(m_eTeam == TEAM_RED || m_eTeam == TEAM_BLUE)
		m_eUnit[3] = UNIT_SKUNK;
	else
		m_eUnit[3] = UNIT_SNAKE;

	m_eUnit[4] = UNIT_BADGER;
	m_eUnit[5] = UNIT_FOX;

	m_iFood = 0;

	return S_OK;
}


OBJSTATE ACommander::Update(float deltaTime)
{
	if (nullptr == m_pCommand)
		SetCommand();

	AActor::Update(deltaTime);

	m_pCommand->Update();
	UpdateState(deltaTime);
	OrderEffect();

	return STATE_PLAY;
}

void ACommander::LateUpdate()
{
	AActor::LateUpdate();
	CheckTileObject();
	SetAnimState();

	if (m_eTeam == TEAM_RED)
		GameMgr->GetSubject(m_eTeam)->Notify(m_iFood);
}

void ACommander::Render()
{
	RenderShadow(80);
	RenderActor();
}

void ACommander::Release()
{
	SafeDelete(m_pCommand);
}

void ACommander::AddFood(int iFood)
{
	m_iFood += iFood;
}

void ACommander::SetFarmReserve(bool bReserve)
{
	m_bFarmReserve = bReserve;
}

const int ACommander::GetFood() const
{
	return m_iFood;
}

void ACommander::InitCommander()
{
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	switch (m_eTeam)
	{
	case TEAM_RED:
		m_pTexMain = TextureMgr->GetTexture(TEXT("commander_commoners"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("commander_commoners_tint"));
		break;
	case TEAM_BLUE:
		m_pTexMain = TextureMgr->GetTexture(TEXT("commander_capitalists"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("commander_capitalists_tint"));
		break;
	case TEAM_GREEN:
		m_pTexMain = TextureMgr->GetTexture(TEXT("commander_military"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("commander_military_tint"));
		break;
	case TEAM_YELLO:
		m_pTexMain = TextureMgr->GetTexture(TEXT("commander_clergy"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("commander_clergy_tint"));
		break;
	case TEAM_NEUTRAL:
	case TEAM_END:
	default:
		break;
	}

	m_iImageCX = COMMANDER_CX;
	m_iImageCY = COMMANDER_CY;

	m_tFrame.fCenterX = float(m_iImageCX >> 1);
	m_tFrame.fCenterY = float(m_iImageCY * 0.9f);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;
}

void ACommander::SetCommand()
{
	if (m_eTeam == TEAM_RED)
	{
		for (int i = 0; i < SLOT_MAX; ++i)
			GameMgr->GetSubject(m_eTeam)->Notify(m_eUnit[i], i);
	}

	if (m_eObjectID == OBJ_PLAYER)
	{
		Vector3 vInitScroll((WINCX >> 1) - m_tInfo.vPosition.x, (WINCY >> 1) - m_tInfo.vPosition.y, 0.f);
		ViewMgr->SetScroll(vInitScroll);

		m_pCommand = new DPlayerCommand;
		m_pCommand->SetCommander(this);
	}
	else if (m_eObjectID == OBJ_AI)
	{
		m_pCommand = new DAICommand;
		m_pCommand->SetCommander(this);
	}
	m_pCommand->Initialize();
}

void ACommander::UpdateState(float deltaTime)
{
	switch (m_eCurAnimState)
	{
	case ANIMSTATE::Idle:
		if (m_fOrder > 0.f)
			m_eCurAnimState = ANIMSTATE::Order;

		if (true == m_bBuild)
			m_eCurAnimState = ANIMSTATE::Build;

		if (m_tInfo.vDir.x != 0.f || m_tInfo.vDir.y != 0.f)
			m_eCurAnimState = ANIMSTATE::Run;

		if (true == m_bDead)
			m_eCurAnimState = ANIMSTATE::Dead;
		break;
	case ANIMSTATE::Order:
		OrderToUnit();
		if (nullptr == m_pBurstEffect)
		{
			m_pBurstEffect = DObjectFactory<CEffect>::CreateDirectlyEffect(PARTICLE_BURST, m_tInfo.vPosition);
			GameMgr->CreateObject(m_pBurstEffect, OBJ_EFFECT);
		}
		else
			m_pBurstEffect->SetPos(m_tInfo.vPosition);

		if (m_tInfo.vDir.x != 0.f || m_tInfo.vDir.y != 0.f)
			m_eCurAnimState = ANIMSTATE::RunOrder;

		if (m_fOrder == 0.f)
			m_eCurAnimState = ANIMSTATE::Idle;
		break;
	case ANIMSTATE::Build:
		if (m_tFrame.fFrame >= m_tFrame.fMax - 0.1f)
		{
			m_bBuild = false;
			m_eCurAnimState = ANIMSTATE::Idle;
		}
		break;
	case ANIMSTATE::Run:
		Move(deltaTime);
		if (m_fOrder > 0.f)
			m_eCurAnimState = ANIMSTATE::RunOrder;

		if (true == m_bBuild)
			m_eCurAnimState = ANIMSTATE::RunBuild;

		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ANIMSTATE::Idle;
		break;
	case ANIMSTATE::RunOrder:
		Move(deltaTime);
		OrderToUnit();
		if (m_fOrder == 0.f)
			m_eCurAnimState = ANIMSTATE::Run;

		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ANIMSTATE::Idle;
		break;
	case ANIMSTATE::RunBuild:
		Move(deltaTime);
		if (m_tFrame.fFrame >= m_tFrame.fMax - 0.5f)
		{
			m_bBuild = false;
			m_eCurAnimState = ANIMSTATE::Run;
		}
		if (m_tInfo.vDir.x == 0.f && m_tInfo.vDir.y == 0.f)
			m_eCurAnimState = ANIMSTATE::Idle;
		break;
	case ACommander::Dead:
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

	if (m_eTeam == m_eViewToTeam)
	{
		if (true == OffsetX())
			ViewMgr->MoveScrollX(m_tInfo.vDir.x);

		if (true == OffsetY())
			ViewMgr->MoveScrollY(m_tInfo.vDir.y);
	}
}

void ACommander::SetAnimState()
{
	if (m_ePreAnimState != m_eCurAnimState)
	{
		switch (m_eCurAnimState)
		{
		case ANIMSTATE::Idle: SetAnimFrame(0.f, 9.f, 1.3f);
			break;
		case ANIMSTATE::Order: SetAnimFrame(10.f, 19.f, 1.3f);
			break;
		case ANIMSTATE::Build:	SetAnimFrame(20.f, 21.f, 5.f);
			break;
		case ANIMSTATE::Run: SetAnimFrame(22.f, 31.f, 1.3f);
			break;
		case ANIMSTATE::RunOrder: SetAnimFrame(32.f, 41.f, 1.3f);
			break;
		case ANIMSTATE::RunBuild: SetAnimFrame(42.f, 46.f, 3.f);
			break;
		case ANIMSTATE::Dead: SetAnimFrame(57.f, 71.f, 1.3f);
			break;
		case ANIMSTATE::End:
		default:
#ifdef _DEBUG
			assert(!"Commander AnimState Error(defalut or End");
#endif
			break;
		}
		m_ePreAnimState = m_eCurAnimState;
	}
}

void ACommander::OrderToUnit()
{
	const OBJLIST& objUnitList = GameMgr->GetObjectList(OBJ_UNIT);
	auto iter = std::find_if(objUnitList.begin(), objUnitList.end(),
		[&](auto& pUnit)->bool
	{
		if (true == m_bAllOrder)
			return (pUnit->GetTeamID() == m_eTeam);
		else
			return (pUnit->GetTeamID() == m_eTeam
				&& static_cast<AUnit*>(pUnit)->GetUnitID() == m_eUnit[m_iSelectSlot]);
	});

	if (iter == objUnitList.end()) return;

	if (nullptr != m_pTarget && m_fOrder < 1.f)
		GameMgr->GetAStar()->AStarStart((*iter)->GetTileIndex(), m_pTarget, m_vecPath);
	else
		GameMgr->GetAStar()->AStarStart((*iter)->GetTileIndex(), m_pLevel->GetCollTile(m_iTileIndex), m_vecPath);

	if (true == m_bAllOrder)
		GameMgr->GetSubject(m_eTeam)->Notify(m_fOrder, UNIT_ALL, m_vecPath);
	else
		GameMgr->GetSubject(m_eTeam)->Notify(m_fOrder, m_eUnit[m_iSelectSlot], m_vecPath);
}

void ACommander::OrderEffect()
{
	if (m_fOrder > 0.f)
	{
		if (nullptr == m_pBurstEffect)
		{
			m_pBurstEffect = DObjectFactory<CEffect>::CreateDirectlyEffect(PARTICLE_BURST, m_tInfo.vPosition);
			GameMgr->CreateObject(m_pBurstEffect, OBJ_EFFECT);
		}
		else
			m_pBurstEffect->SetPos(m_tInfo.vPosition);
	}
	else
	{
		if (nullptr != m_pBurstEffect)
		{
			m_pBurstEffect->Destroy();
			m_pBurstEffect = nullptr;
		}
	}
}

void ACommander::CheckTileObject()
{
	CheckHQ();
	CheckFarm();
	CheckSlotUnit();
	CheckEnemy(5);
}

void ACommander::CheckHQ()
{
	VECCOLLTILE VecRange;
	m_pLevel->GetRange(VecRange, m_iTileIndex, 2);

	for (auto& pTile : VecRange)
	{
		if (pTile->pGameObject == nullptr)
			continue;

		if (CheckObjectNetual(pTile->pGameObject, OBJ_HQ))
		{
			if (true == m_bBuild && m_iFood >= 60)
			{
				SoundMgr->PlayEffectSound(TEXT("Build_HQ"), m_tInfo.vPosition);
				pTile->pGameObject->Destroy();
				pTile->pGameObject->SetTeam(m_eTeam);
				m_iFood -= 60;
			}
		}
	}
}

void ACommander::CheckFarm()
{
	CGameObject* pObject = m_pLevel->GetCollTile(m_iTileIndex)->pGameObject;

	if (CheckObjectID(pObject, OBJ_FARM))
	{
		if (true == m_bBuild && CheckObjectTeam(pObject, m_eTeam) && false == m_bFarmReserve)
		{
			pObject->Destroy();
			m_bBuild = false;
		}
	}
}

void ACommander::CheckSlotUnit()
{
	if (true == m_bBuild)
	{
		if (m_pLevel->GetTileObject(m_iTileIndex) != this) return;

		VECCOLLTILE VecRange;
		m_pLevel->GetRange(VecRange, m_iTileIndex);

		if (true == CheckTile4x4(VecRange, 0))
			CreateSlotUnitFactory(m_pLevel->GetNeighborTileIndex(NEIGHBOR_LEFTDOWN, m_iTileIndex));
		else if (true == CheckTile4x4(VecRange, 1))
			CreateSlotUnitFactory(m_iTileIndex);
		else if (true == CheckTile4x4(VecRange, 2))
			CreateSlotUnitFactory(m_pLevel->GetNeighborTileIndex(NEIGHBOR_RIGHTDOWN, m_iTileIndex));
		else if (true == CheckTile4x4(VecRange, 3))
			CreateSlotUnitFactory(m_pLevel->GetNeighborTileIndex(NEIGHBOR_DOWN, m_iTileIndex));

		m_bBuild = false;
	}
}

// 0. Left, 1. Up, 2, Right, 3. Down
bool ACommander::CheckTile4x4(VECCOLLTILE & vecRange, int iDir)
{
	switch (iDir)
	{
	case 0:
		for (int i = 0; i <= 2; ++i)
			if (false == CheckTileEmpty(vecRange[i]))
				return false;
		break;
	case 1:
		for (int i = 2; i <= 4; ++i)
			if (false == CheckTileEmpty(vecRange[i]))
				return false;
		break;
	case 2:
		for (int i = 4; i <= 6; ++i)
			if (false == CheckTileEmpty(vecRange[i]))
				return false;
		break;
	case 3:
		for (int i = 6; i < 8; ++i)
			if (false == CheckTileEmpty(vecRange[i]))
				return false;
		if (false == CheckTileEmpty(vecRange[0]))
			return false;
		break;
	default:
		return false;
	}
	return true;
}

void ACommander::CreateSlotUnitFactory(int iStart)
{
	if (false == CheckUnitFactoryPay())
		return;

	SoundMgr->PlayEffectSound(TEXT("Build_UnitFactory"), m_tInfo.vPosition);
	CGameObject* pObject = DObjectFactory<BUnitFactory>::CreateUnitFactory(iStart, m_eUnit[m_iSelectSlot], m_eTeam);
	GameMgr->CreateObject(pObject, OBJ_UNITFACTORY);
}

bool ACommander::CheckUnitFactoryPay()
{
	switch (m_eUnit[m_iSelectSlot])
	{
		// 60 Food
	case UNIT_SQUIRREL:
	case UNIT_LIZARD:
	case UNIT_TOAD:
	case UNIT_PIGEON:
	case UNIT_MOLE:
		if (m_iFood >= 60)
		{
			m_iFood -= 60;
			return true;
		}
		break;

		// 120 Food
	case UNIT_FERRET:
	case UNIT_CHAMELEON:
	case UNIT_SKUNK:
	case UNIT_FALCON:
	case UNIT_SNAKE:
		if (m_iFood >= 120)
		{
			m_iFood -= 120;
			return true;
		}
		break;

		// 180 Food
	case UNIT_BADGER:
	case UNIT_BOAR:
	case UNIT_FOX:
	case UNIT_WOLF:
	case UNIT_OWL:
		if (m_iFood >= 180)
		{
			m_iFood -= 180;
			return true;
		}
		break;

		// 유닛 생성에서는 Failed
	case UNIT_BARBEDWIRE:
	case UNIT_LANDMINE:
	case UNIT_BALLON:
	case UNIT_TURRET:
	case UNIT_ARTILLERY:
		return false;
	default:
		return false;
	}
	return false;
}

bool ACommander::CheckTileEmpty(COLLTILE * pTile)
{
	if (nullptr != pTile->pGameObject) return false;
	if (pTile->byOption != 0) return false;

	return true;
}

bool ACommander::CheckObjectID(CGameObject * pObject, OBJID eObjectID)
{
	if (pObject->GetObjectID() == eObjectID) return true;

	return false;
}

bool ACommander::CheckObjectTeam(CGameObject * pObject, TEAMID eTeamID)
{
	if (pObject->GetTeamID() == eTeamID) return true;

	return false;
}

bool ACommander::CheckObjectNetual(CGameObject * pObject, OBJID eObjectID)
{
	if (false == CheckObjectID(pObject, eObjectID)) return false;
	if (false == CheckObjectTeam(pObject, TEAM_NEUTRAL)) return false;

	return true;
}

bool ACommander::OffsetX()
{
	const Vector3& vScroll = ViewMgr->GetScroll();
	const Vector3& vPos = m_tInfo.vPosition + ViewMgr->GetScroll();

	if (m_tInfo.vDir.x > 0.f && vPos.x > (WINCX >> 1) - 2.f) return true;
	if (m_tInfo.vDir.x < 0.f && vPos.x < (WINCX >> 1) + 2.f) return true;

	return false;
}

bool ACommander::OffsetY()
{
	const Vector3& vScroll = ViewMgr->GetScroll();
	const Vector3& vPos = m_tInfo.vPosition + ViewMgr->GetScroll();

	if (m_tInfo.vDir.y > 0.f && vPos.y > (WINCY >> 1) - 2.f) return true;
	if (m_tInfo.vDir.y < 0.f && vPos.y < (WINCY >> 1) + 2.f) return true;

	return false;
}