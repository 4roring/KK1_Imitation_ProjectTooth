#include "stdafx.h"
#include "AUnit.h"
#include "DUnit_1Tear.h"

AUnit::AUnit()
{
}


AUnit::~AUnit()
{
	Release();
}

HRESULT AUnit::Initialize()
{
	switch (m_eUnitID)
	{
		// 1Ƽ��
	case UNIT_SQUIRREL:
	case UNIT_LIZARD:
	case UNIT_TOAD:
	case UNIT_MOLE:
		m_pUnitState = new DUnit_1Tear;
		break;
	
		// 2Ƽ��
	case UNIT_FERRET:
	case UNIT_CHAMELEON:
	case UNIT_SKUNK:
	case UNIT_SNAKE:
		break;

		// 3Ƽ��
	case UNIT_BADGER:
	case UNIT_BOAR:
	case UNIT_FOX:
	case UNIT_WOLF:
		break;

		// ����
	case UNIT_PIGEON:
	case UNIT_FALCON:
	case UNIT_OWL:
		break;

		// �ǹ���
	case UNIT_BARBEDWIRE:
	case UNIT_LANDMINE:
	case UNIT_BALLON:
	case UNIT_TURRET:
	case UNIT_ARTILLERY:
		break;

	default:
		break;
	}

	return S_OK;
}

OBJSTATE AUnit::Update(float deltaTime)
{
	

	return STATE_PLAY;
}

void AUnit::LateUpdate()
{
	
}

void AUnit::Render()
{
	
}

void AUnit::Release()
{
	SafeDelete(m_pUnitState);
}