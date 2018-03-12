#include "stdafx.h"
#include "BUnitFactory.h"


BUnitFactory::BUnitFactory()
{
}


BUnitFactory::~BUnitFactory()
{
	Release();
}

HRESULT BUnitFactory::Initialize()
{
	if (FAILED(CBuilding::Initialize())) return E_FAIL;
	if (FAILED(SetTexture())) return E_FAIL;

	return S_OK;
}

OBJSTATE BUnitFactory::Update(float deltaTime)
{
	CBuilding::Update(deltaTime);

	return STATE_PLAY;
}

void BUnitFactory::LateUpdate()
{
	CBuilding::LateUpdate();
}

void BUnitFactory::Render()
{
	CBuilding::Render();
}

void BUnitFactory::Release()
{
}

HRESULT BUnitFactory::SetTexture()
{
	switch (m_eUnitID)
	{
	case UNIT_SQUIRREL:
	case UNIT_LIZARD:
	case UNIT_TOAD:
	case UNIT_PIGEON:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens1"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens1_tint"));
		break;
	case UNIT_MOLE:
		break;

	case UNIT_FERRET:
	case UNIT_CHAMELEON:
	case UNIT_FALCON:
	case UNIT_SKUNK:
	case UNIT_SNAKE:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens2"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens2_tint"));
		break;

	case UNIT_BADGER:
	case UNIT_BOAR:
	case UNIT_FOX:
	case UNIT_OWL:
	case UNIT_WOLF:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens3"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens3_tint"));
		break;

	default:
		MSG_BOX(TEXT("Unit Factory Create Error"));
		return E_FAIL;
	}

	return S_OK;
}
