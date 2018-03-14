#include "stdafx.h"
#include "BUnitFactory.h"
#include "Level.h"
#include "AUnit.h"

BUnitFactory::BUnitFactory()
{
}


BUnitFactory::~BUnitFactory()
{
	Release();
}

HRESULT BUnitFactory::Initialize()
{
	if (FAILED(BBuilding::Initialize())) return E_FAIL;
	if (FAILED(SetUnit())) return E_FAIL;

	return S_OK;
}

OBJSTATE BUnitFactory::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
	{
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

		for (int iTileNum : m_iTileIndexArr)
			m_pLevel->GetCollTile(iTileNum)->pGameObject = this;

		Vector3 vPos = m_pLevel->GetCollTile(m_iTileIndexArr[0])->vPosition;
		m_tInfo.vPosition = Vector3(vPos.x, vPos.y - UNITFACTORY_CY[m_iTear], 0.f);
	}

	if (false == m_bBuildEnd)
	{
		BBuilding::Update(deltaTime);
		AnimUpdate();
		m_fBuildTime -= deltaTime;
	}
	else if(m_iUnitCount < m_iUnitCountMax)   
		CreateUnit(deltaTime);
	
		
	return STATE_PLAY;
}

void BUnitFactory::LateUpdate()
{
	BBuilding::LateUpdate();
}

void BUnitFactory::Render()
{
	BBuilding::Render();
}

void BUnitFactory::Release()
{
}

void BUnitFactory::AnimUpdate()
{
	switch (m_iTear)
	{
	case 0:
		if (m_fBuildTime > 2.f && m_tFrame.fFrame > 3.5f)
			m_tFrame.fFrame = 3.f;
		else if (m_tFrame.fFrame >= m_tFrame.fMax - 0.5f)
			m_tFrame.fFrame = m_tFrame.fMax - 0.5f;
		break;
	case 1:
		if (m_fBuildTime > 3.f && m_tFrame.fFrame > 3.5f)
			m_tFrame.fFrame = 3.f;
		else if (m_tFrame.fFrame >= m_tFrame.fMax - 0.5f)
			m_tFrame.fFrame = m_tFrame.fMax - 0.5f;
		break;
	case 2:
		if (m_fBuildTime > 4.f && m_tFrame.fFrame > 3.5f)
			m_tFrame.fFrame = 3.f;
		else if (m_tFrame.fFrame >= m_tFrame.fMax - 0.5f)
			m_tFrame.fFrame = m_tFrame.fMax - 0.5f;
		break;
	default:
#ifdef _DEBUG
		assert(!"UnitFactory Anim Update Error!!!");
#endif
	}

	if (m_fBuildTime < 0.f)
	{
		m_bBuildEnd = true;
		m_fBuildTime = 0.f;
	}
}

HRESULT BUnitFactory::SetUnit()
{
	switch (m_eUnitID)
	{
	case UNIT_SQUIRREL:
	case UNIT_LIZARD:
	case UNIT_TOAD:
	case UNIT_PIGEON:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens1"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens1_tint"));
		m_iTear = 0;
		m_fBuildTime = PRODUCTIONTIME[m_iTear];
		m_fProductionTime = PRODUCTIONTIME[m_iTear];
		m_iMaxHp = UNITFACTORY_MAXHP[m_iTear];
		m_iUnitCountMax = 3;
		break;

		// 두더지 건물은 따로 만들어야할뜻.
	//case UNIT_MOLE:
	//	m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens1"));
	//	m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens1_tint"));
	//	m_iTear = 0;
	//	m_fBuildTime = PRODUCTIONTIME[m_iTear];
	//	m_fProductionTime = PRODUCTIONTIME[m_iTear];
	//	m_iMaxHp = UNITFACTORY_MAXHP[m_iTear];
	//	break;

	case UNIT_FERRET:
	case UNIT_CHAMELEON:
	case UNIT_FALCON:
	case UNIT_SKUNK:
	case UNIT_SNAKE:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens2"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens2_tint"));
		m_iTear = 1;
		m_fBuildTime = PRODUCTIONTIME[m_iTear];
		m_fProductionTime = PRODUCTIONTIME[m_iTear];
		m_iMaxHp = UNITFACTORY_MAXHP[m_iTear];
		m_iUnitCountMax = 2;
		break;

	case UNIT_BADGER:
	case UNIT_BOAR:
	case UNIT_FOX:
	case UNIT_OWL:
	case UNIT_WOLF:
		m_pTexMain = TextureMgr->GetTexture(TEXT("structure_warrens3"));
		m_pTexTint = TextureMgr->GetTexture(TEXT("structure_warrens3_tint"));
		m_iTear = 2;
		m_fBuildTime = PRODUCTIONTIME[m_iTear];
		m_fProductionTime = PRODUCTIONTIME[m_iTear];
		m_iMaxHp = UNITFACTORY_MAXHP[m_iTear];
		m_iUnitCountMax = 1;
		break;

	default:
		MSG_BOX(TEXT("Unit Factory Create Error"));
		return E_FAIL;
	}
	m_iHp = m_iMaxHp;
	SetFactory();

	if (nullptr == m_pTexMain || nullptr == m_pTexTint)
		return E_FAIL;
	   
	return S_OK;
}

void BUnitFactory::SetFactory()
{
	m_iImageCX = UNITFACTORY_CX[m_iTear];
	m_iImageCY = UNITFACTORY_CY[m_iTear];

	m_tFrame.fCenterX = (float)(m_iImageCX >> 1);
	m_tFrame.fCenterY = (float)(m_iImageCY >> 1);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	switch (m_iTear)
	{
	case 0: SetAnimFrame(0.f, 12.f, 0.7f);
		break;
	case 1: SetAnimFrame(0.f, 21.f, 0.6f);
		break;
	case 2: SetAnimFrame(0.f, 37.f, 0.3f);
		break;
	}	
}

void BUnitFactory::CreateUnit(float deltaTime)
{
	if(m_iUnitCount < m_iUnitCountMax)
		m_fBuildTime += deltaTime;
	if (m_fBuildTime >= m_fProductionTime)
	{
		// 유닛 생성!
		CGameObject* pObject = DObjectFactory<AUnit>::CreateUnit(m_iTileIndexArr[0], m_eUnitID, m_eTeam);
		GameMgr->CreateObject(pObject, OBJ_UNIT);

		++m_iUnitCount;
		m_fBuildTime = 0.f;
	}
}
