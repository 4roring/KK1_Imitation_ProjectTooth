#include "stdafx.h"
#include "AUnit.h"
#include "DUnit_1Tear.h"
#include "BUnitFactory.h"
#include "Level.h"

AUnit::AUnit()
{
}


AUnit::~AUnit()
{
	Release();
}

HRESULT AUnit::Initialize()
{
	AActor::Initialize();

	switch (m_eUnitID)
	{
		// 1티어
	case UNIT_SQUIRREL:
	case UNIT_LIZARD:
	case UNIT_TOAD:
	case UNIT_MOLE:
		m_pUnitState = new DUnit_1Tear;
		break;
	
		// 2티어
	case UNIT_FERRET:
	case UNIT_CHAMELEON:
	case UNIT_SKUNK:
	case UNIT_SNAKE:
		break;

		// 3티어
	case UNIT_BADGER:
	case UNIT_BOAR:
	case UNIT_FOX:
	case UNIT_WOLF:
		break;

		// 공중
	case UNIT_PIGEON:
	case UNIT_FALCON:
	case UNIT_OWL:
		break;

		// 건물형
	case UNIT_BARBEDWIRE:
	case UNIT_LANDMINE:
	case UNIT_BALLON:
	case UNIT_TURRET:
	case UNIT_ARTILLERY:
		break;

	default:
		break;
	}

	if (nullptr == m_pUnitState)
		return E_FAIL;

	m_pUnitState->SetUnit(this);
	m_pUnitState->Initialize();

	return S_OK;
}

OBJSTATE AUnit::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
	{
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());
		Vector3 vPos = m_pLevel->GetCollTile(m_iTileIndex)->vPosition;
		m_tInfo.vPosition = vPos;
	}

	if (true == m_bDead)
	{
		m_pFactory->UnitCountSub();
		return STATE_DESTROY;
	}

	AActor::Update(deltaTime);
	m_pUnitState->Update(deltaTime);
	return STATE_PLAY;
}

void AUnit::LateUpdate()
{
	AActor::LateUpdate();
	m_pUnitState->LateUpdate();
}

void AUnit::Render()
{
	RenderGroundChar();
	RenderShadow(60);
}

void AUnit::Release()
{
	SafeDelete(m_pUnitState);
}