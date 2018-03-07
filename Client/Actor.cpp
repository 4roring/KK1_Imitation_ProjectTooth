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
	m_eTeam = TEAM_YELLO;
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
	
}

void CActor::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}
