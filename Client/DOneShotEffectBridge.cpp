#include "stdafx.h"
#include "DOneShotEffectBridge.h"
#include "Effect.h"


DOneShotEffectBridge::DOneShotEffectBridge()
{
}


DOneShotEffectBridge::~DOneShotEffectBridge()
{
}

HRESULT DOneShotEffectBridge::Initialize()
{
	m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("particles"), TEXT("explosion01"));
	m_tRect = *(m_pEffect->m_pTexMain->pRect);

	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = 39.f * 0.5f;
	m_tFrame.fMin = 0.f;
	m_tFrame.fMax = 39.f;

	m_iImageCX = 120;
	m_iImageCY = 170;

	m_tFrame.fCenterX = float(m_iImageCX >> 1);
	m_tFrame.fCenterY = float(m_iImageCY * 0.9f);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	return S_OK;
}

OBJSTATE DOneShotEffectBridge::Update(float deltaTime)
{
	FrameMove(deltaTime);

	if (m_tFrame.fFrame >= m_tFrame.fMax - 0.5f)
		return STATE_DESTROY;

	return STATE_PLAY;
}

void DOneShotEffectBridge::LateUpdate()
{
	UpdateRect();
}

void DOneShotEffectBridge::Render()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_pEffect->m_tInfo.vPosition.x + vScroll.x
		, m_pEffect->m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_pEffect->m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_pEffect->m_tInfo.matWorld);
	m_pSprite->Draw(m_pEffect->m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void DOneShotEffectBridge::Release()
{
}

void DOneShotEffectBridge::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}

void DOneShotEffectBridge::UpdateRect()
{
	int iSceneLeft = m_tScene.iFrame * m_iImageCX;
	int iSceneTop = m_tScene.iScene * m_iImageCY;
	int iSceneRight = m_tScene.iFrame * m_iImageCX + m_iImageCX;
	int iSceneBottom = m_tScene.iScene * m_iImageCY + m_iImageCY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}
