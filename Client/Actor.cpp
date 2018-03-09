#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
{
}


CActor::~CActor()
{
}

HRESULT CActor::Initialize()
{
	m_eLayer = LAYER_OBJ;
	m_eTeam = TEAM_RED;
	m_TeamColor = GameMgr->GetTeamColor(m_eTeam);

	return S_OK;
}

OBJSTATE CActor::Update(float deltaTime)
{
	FrameMove(deltaTime);

	return STATE_PLAY;
}

void CActor::LateUpdate()
{
	// GetTileIndex를 실행하여 현재타일과 이전타일이 다를 경우
	// 갈 수 있는 공간인지 우선 체크하고
	// 이전 타일의 CGameObejct*은 nullptr 현재 타일은 자신을 넘겨준다.
	UpdateRect();
}

void CActor::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}

void CActor::UpdateRect()
{
	int iSceneLeft = m_tScene.iFrame * COMMANDER_CX;
	int iSceneTop = m_tScene.iScene * COMMANDER_CY;
	int iSceneRight = m_tScene.iFrame * COMMANDER_CX + COMMANDER_CX;
	int iSceneBottom = m_tScene.iScene * COMMANDER_CY + COMMANDER_CY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}

void CActor::RenderShadow(BYTE Alpha)
{
	D3DXMATRIX matShadow, matRotZ;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-40.f));

	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;
	if (false == m_bFlipX)
		D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom * 0.7f, 1.f);
	else
		D3DXMatrixScaling(&matScale, -fScreenZoom, fScreenZoom * 0.7f, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x - 10.f
		, m_tInfo.vPosition.y + vScroll.y - 5.f
		, 0.f);

	matShadow = matScale * matRotZ * matTrans;

	m_pSprite->SetTransform(&matShadow);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(Alpha, 0, 0, 0));
}

void CActor::RenderFlyChar()
{

}

void CActor::RenderGroundChar()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;

	if (false == m_bFlipX)
		D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);
	else
		D3DXMatrixScaling(&matScale, -fScreenZoom, fScreenZoom, 1.f);

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

void CActor::SetAnimFrame(float fMin, float fMax, float fFrameSpeed)
{
	m_tFrame.fMin = fMin;
	m_tFrame.fFrame = fMin;
	m_tFrame.fCount = (fMax - fMin) * fFrameSpeed;
	m_tFrame.fMax = fMax;
}

void CActor::UpdateFlipX()
{

	if (m_tInfo.vDir.x > 0.f)
		m_bFlipX = false;
	else if (m_tInfo.vDir.x < 0.f)
		m_bFlipX = true;
	else if(m_tInfo.vDir.y < 0.f)
		m_bFlipX = false;
	else if (m_tInfo.vDir.y > 0.f)
		m_bFlipX = true;
}
