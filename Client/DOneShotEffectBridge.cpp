#include "stdafx.h"
#include "DOneShotEffectBridge.h"


DOneShotEffectBridge::DOneShotEffectBridge()
{
}


DOneShotEffectBridge::~DOneShotEffectBridge()
{
}

HRESULT DOneShotEffectBridge::Initialize()
{
	return S_OK;
}

OBJSTATE DOneShotEffectBridge::Update(float deltaTime)
{

	return STATE_PLAY;
}

void DOneShotEffectBridge::LateUpdate()
{
}

void DOneShotEffectBridge::Render()
{
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
	int iSceneLeft = m_tScene.iFrame * m_iImageX;
	int iSceneTop = m_tScene.iScene * m_iImageY;
	int iSceneRight = m_tScene.iFrame * m_iImageX + m_iImageX;
	int iSceneBottom = m_tScene.iScene * m_iImageY + m_iImageY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}
