#include "stdafx.h"
#include "NeutralHQ.h"
#include "Level.h"
#include "BHQ.h"

CNeutralHQ::CNeutralHQ()
{
}


CNeutralHQ::~CNeutralHQ()
{
	Release();
}

HRESULT CNeutralHQ::Initialize()
{
	m_eTeam = TEAM_NEUTRAL;
	m_eLayer = LAYER_OBJ;
	m_pTexMain = TextureMgr->GetTexture(TEXT("hq"));

	return S_OK;
}

OBJSTATE CNeutralHQ::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
	{
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

		for (int iTileNum : m_iTileIndexArr)
		{
			(*m_pLevel->GetVecCollTile())[iTileNum]->pGameObject = this;
			(*m_pLevel->GetVecCollTile())[iTileNum]->byDrawID = 1;
			(*m_pLevel->GetVecCollTile())[iTileNum]->byOption = 1;
		}
	}

	if (m_bDestroy)
	{
		// TODO: BHQ를 자신의 위치에 생성하고 자신을 파괴
		CGameObject* pObject = DObjectFactory<BHQ>::CreateBuilding(m_iTileIndexArr[0], m_eTeam);
		GameMgr->CreateObject(pObject, OBJ_HQ);

		return STATE_DESTROY;
	}

	return STATE_PLAY;
}

void CNeutralHQ::LateUpdate()
{
}

void CNeutralHQ::Render()
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
		, nullptr
		, &Vector3(float(m_pTexMain->tImageInfo.Width >> 1), m_pTexMain->tImageInfo.Height * 0.9f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CNeutralHQ::Release()
{
}

void CNeutralHQ::SetTileIndexArray(int iStart)
{
	m_iTileIndexArr[0] = iStart;
	m_iTileIndexArr[1] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_LEFTUP, iStart);
	m_iTileIndexArr[2] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_RIGHTUP, iStart);
	m_iTileIndexArr[3] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_UP, iStart);
}