#include "stdafx.h"
#include "DUnit_1Tear.h"
#include "AUnit.h"

DUnit_1Tear::DUnit_1Tear()
{
}


DUnit_1Tear::~DUnit_1Tear()
{
}

HRESULT DUnit_1Tear::Initialize()
{
	switch (m_pUnit->m_eUnitID)
	{
		// 1Æ¼¾î
	case UNIT_SQUIRREL:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT(""));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT(""));
		break;
	case UNIT_LIZARD:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("lizard"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("lizard_tint"));
		break;
	case UNIT_TOAD:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT(""));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT(""));
		break;
	case UNIT_MOLE:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("mole"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("mole_tint"));
		break;
	default:
		MSG_BOX(TEXT("1Tear Unit Initialize Failed!!!"));
		return E_FAIL;
	}
	return S_OK;
}

void DUnit_1Tear::Update(float deltaTime)
{
	m_pUnit->m_tFrame.fFrame;
}

void DUnit_1Tear::LateUpdate()
{
}

void DUnit_1Tear::UpdateState(float deltaTime)
{
}

void DUnit_1Tear::SetAnimState()
{
}
