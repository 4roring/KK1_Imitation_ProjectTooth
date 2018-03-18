#include "stdafx.h"
#include "BFarm.h"
#include "Level.h"
#include "ACommander.h"
#include "Crop.h"

BFarm::BFarm()
{
}


BFarm::~BFarm()
{
	Release();
}

HRESULT BFarm::Initialize()
{
	m_eLayer = LAYER_BACK;

	m_pTexMain = TextureMgr->GetTexture(TEXT("farmland"));

	m_iImageCX = FARM_CX;
	m_iImageCY = FARM_CY;

	m_tFrame.fCenterX = (float)(m_iImageCX >> 1);
	m_tFrame.fCenterY = (float)(m_iImageCY >> 1);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_iMaxHp = 10;
	m_iHp = m_iMaxHp;

	m_iFood = 300;

	return S_OK;
}

OBJSTATE BFarm::Update(float deltaTime)
{
	if (nullptr == m_pCommander && m_eTeam != TEAM_NEUTRAL)
		m_pCommander = dynamic_cast<ACommander*>(GameMgr->GetTeamCommander(m_eTeam));

	if (nullptr == m_pLevel)
		SetLevel();

	BBuilding::Update(deltaTime);
	UpdateState(deltaTime);

	return STATE_PLAY;
}

void BFarm::LateUpdate()
{
	BBuilding::LateUpdate();
	SetAnimState();

	if (m_iHp <= 0)
	{
		// TODO: 돼지 쥬금
		
	}
}

void BFarm::Render()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x
		, m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void BFarm::Release()
{
}

void BFarm::UpdateState(float deltaTime)
{
	switch (m_eCurState)
	{
	case BFarm::Grass:
		if (true == m_bDestroy)
		{
			// TODO: 이펙트 펑!
			m_fBuildTime = 100.f;
			m_bDestroy = false;
			m_eCurState = BFarm::OnStream;
			if (nullptr == m_pCommander)
				m_pCommander = dynamic_cast<ACommander*>(GameMgr->GetTeamCommander(m_eTeam));
			m_pCommander->SetFarmReserve(true);
		}
		break;
	case BFarm::OnStream:
		if (m_fBuildTime == 100.f)
		{
			if (m_pCommander->GetFood() >= 60)
			{
				m_pCommander->AddFood(-60);
				m_fBuildTime = 30.f;
				m_pCommander->SetFarmReserve(false);
			}
		}

		if (m_fBuildTime <= 30.f)
			m_fBuildTime -= deltaTime;

		if (m_fBuildTime < 0)
		{
			CreateFinished();
		}
		if (true == m_bDestroy)
		{
			m_pCommander->AddFood(60);
			m_eCurState = BFarm::Grass;
			m_bDestroy = false;
		}
		break;
	case BFarm::Farm:
		m_fFoodUpTime += deltaTime;
		if (m_fFoodUpTime >= 1.f)
		{
			m_pCommander->AddFood(1);
			--m_iFood;
			m_fFoodUpTime = 0.f;
		}

		if(m_iFood <= 0)
			m_eCurState = BFarm::FarmEnd;
		break;
	case BFarm::FarmEnd:
		// 물은 물이요 산은 산이도다.
		break;
	case BFarm::End:
	default:
#ifdef _DEBUG
		assert(!"Farm AnimState Error(defalut or End");
#endif
		break;
	}
}

void BFarm::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BFarm::Grass: SetAnimFrame(12.f, 28.f, 1.f);
			break;
		case BFarm::OnStream: SetAnimFrame(2.f, 7.f, 1.3f);
			break;
		case BFarm::Farm: SetAnimFrame(0.f, 0.f, 0.f);
			break;
		case BFarm::FarmEnd: SetAnimFrame(11.f, 11.f, 0.f);
			break;
		case BFarm::End:
		default:
#ifdef _DEBUG
			assert(!"Farm AnimState Error(defalut or End)");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void BFarm::SetLevel()
{
	m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());
	for (int iTileNum : m_iTileIndexArr)
	{
		m_pLevel->SetTileObject(iTileNum, this);
		m_pLevel->GetCollTile(iTileNum)->byDrawID = 0;
		m_pLevel->GetCollTile(iTileNum)->byOption = 0;
	}

	Vector3 vPos = m_pLevel->GetCollTile(m_iTileIndexArr[0])->vPosition;
	m_tInfo.vPosition = Vector3(vPos.x, vPos.y - COLLTILECY, 0.f);

	if (m_eCurState == BFarm::Farm)
		CreateFinished();
}

void BFarm::SetCrop()
{
	// 중간
	float fX = m_tInfo.vPosition.x;
	float fY = m_tInfo.vPosition.y - 15.f;
	Vector3 vPos = Vector3(fX, fY, 0.f);
	CGameObject* pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[0] = pCrop;

	// 상
	fX = m_tInfo.vPosition.x;
	fY = m_tInfo.vPosition.y - 15.f - float(m_iImageCY * 0.6666f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[1] = pCrop;

	// 하
	fX = m_tInfo.vPosition.x;
	fY = m_tInfo.vPosition.y - 15.f + float(m_iImageCY * 0.6666f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[2] = pCrop;

	// 좌
	fX = m_tInfo.vPosition.x - float(m_iImageCX * 0.6666f);
	fY = m_tInfo.vPosition.y - 15.f;
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[3] = pCrop;

	// 우
	fX = m_tInfo.vPosition.x + float(m_iImageCX * 0.6666f);
	fY = m_tInfo.vPosition.y - 15.f;
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[4] = pCrop;

	// 좌상
	fX = m_tInfo.vPosition.x - float(m_iImageCX * 0.3333f);
	fY = m_tInfo.vPosition.y - 15.f - float(m_iImageCY * 0.3333f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[5] = pCrop;

	// 우상
	fX = m_tInfo.vPosition.x + float(m_iImageCX * 0.3333f);
	fY = m_tInfo.vPosition.y - 15.f - float(m_iImageCY * 0.3333f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[6] = pCrop;

	// 좌하
	fX = m_tInfo.vPosition.x - float(m_iImageCX * 0.3333f);
	fY = m_tInfo.vPosition.y - 15.f + float(m_iImageCY * 0.3333f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[7] = pCrop;

	// 우하
	fX = m_tInfo.vPosition.x + float(m_iImageCX * 0.3333f);
	fY = m_tInfo.vPosition.y - 15.f + float(m_iImageCY * 0.3333f);
	vPos = Vector3(fX, fY, 0.f);
	pCrop = DObjectFactory<CCrop>::Create(vPos);
	GameMgr->CreateObject(pCrop, OBJ_FARM);
	m_pCrop[8] = pCrop;
}

void BFarm::CreateFinished()
{
	// TODO: 이펙트 펑! && 돼지 등장! && 농작물도 등장
	// 초반 농장 4개를 위해 함수로 작성.
	m_eCurState = BFarm::Farm; // 이 친구도 묶어서.
	SetCrop();
}
