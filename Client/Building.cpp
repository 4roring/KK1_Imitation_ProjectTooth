#include "stdafx.h"
#include "Building.h"
#include "Level.h"

CBuilding::CBuilding()
{
}


CBuilding::~CBuilding()
{
}

HRESULT CBuilding::Initialize()
{
	m_eLayer = LAYER_OBJ;
	m_TeamColor = GameMgr->GetTeamColor(m_eTeam);

	return S_OK;
}

OBJSTATE CBuilding::Update(float deltaTime)
{
	FrameMove(deltaTime);

	return STATE_PLAY;
}

void CBuilding::LateUpdate()
{
	UpdateRect();
}

void CBuilding::Render()
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

	m_pSprite->Draw(m_pTexTint->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, *m_TeamColor);
}

void CBuilding::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}

void CBuilding::SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed)
{
	m_tFrame.fMin = fFrameMin;
	m_tFrame.fFrame = fFrameMin;
	m_tFrame.fCount = (fFrameMax - fFrameMin) * fFrameSpeed;
	m_tFrame.fMax = fFrameMax;
}

void CBuilding::UpdateRect()
{
	int iSceneLeft = m_tScene.iFrame * iImageCX;
	int iSceneTop = m_tScene.iScene * iImageCY;
	int iSceneRight = m_tScene.iFrame * iImageCX + iImageCX;
	int iSceneBottom = m_tScene.iScene * iImageCY + iImageCY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}

void CBuilding::SetTileIndexArray(int iStart)
{
	m_iTileIndexArr[0] = iStart;
	m_iTileIndexArr[1] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_LEFTUP, iStart);
	m_iTileIndexArr[2] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_RIGHTUP, iStart);
	m_iTileIndexArr[3] = m_pLevel->GetNeighborTileIndex(NEIGHBOR_UP, iStart);
}