#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
{
}


CActor::~CActor()
{
}

void CActor::Initialize()
{
	m_eTeam = TEAM_RED;
	m_TeamColor = GameMgr->GetTeamColor(m_eTeam);
}

OBJSTATE CActor::Update(float deltaTime)
{
	FrameMove(deltaTime);

	return STATE_PLAY;
}

void CActor::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}
