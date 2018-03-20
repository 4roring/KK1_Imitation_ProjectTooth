#include "stdafx.h"
#include "DAICommand.h"
#include "ACommander.h"
#include "AStar.h"
#include "Level.h"

DAICommand::DAICommand()
{
}

DAICommand::~DAICommand()
{
}

void DAICommand::Initialize()
{
	// 초기 행동들 집어넣기!
	m_BehaviorList.push_back([&]()->int { return Wait(2.f); });
	m_BehaviorList.push_back([&]()->int { return MoveToEmptyFarm(30.f); });

	m_pACommander->m_fSpeed = 180.f;
}

void DAICommand::Update()
{
	if (nullptr == m_pLevel)
		m_pLevel = m_pACommander->m_pLevel;

	FSM(Time->GetDeltaTime());
}

void DAICommand::FSM(float deltaTime)
{
	m_fPlayTime += deltaTime;
	
	int iEvent = 0;

	if (false == m_BehaviorList.empty())
		iEvent = m_BehaviorList.front()();
	else
		m_BehaviorList.push_back([&]()->int { return Wait(m_fPlayTime + 10.f); });

	if (iEvent == 1)
		m_BehaviorList.pop_front();	

	if (false == m_vecPath.empty())
		MovePath(deltaTime);
}

void DAICommand::MovePath(float deltaTime)
{
	INFO& rInfo = m_pACommander->m_tInfo;
	Vector3 vTarget = Vector3(0.f, 0.f, 0.f);

	vTarget = m_vecPath.back()->vPosition - rInfo.vPosition;
	D3DXVec3Normalize(&rInfo.vDir, &vTarget);

	rInfo.vDir *= m_pACommander->m_fSpeed * deltaTime;
	rInfo.vPosition += rInfo.vDir;

	if (D3DXVec3Length(&vTarget) < 15.f)
		m_vecPath.pop_back();
}

int DAICommand::Wait(float fTime)
{
	m_pACommander->m_tInfo.vDir = Vector3(0.f, 0.f, 0.f);

	if (fTime < m_fPlayTime)
		return 1;

	return 0;
}

int DAICommand::MoveToEmptyFarm(float fTime)
{
	if (true == m_vecPath.empty())
	{
		auto iter_Begin = GameMgr->GetObjectList(OBJ_FARM).begin();
		auto iter_End = GameMgr->GetObjectList(OBJ_FARM).end();

		TEAMID eTeam = m_pACommander->GetTeamID();

		auto iter_find = std::find_if(iter_Begin, iter_End,
			[&eTeam](auto& pFarm)
		{
			return pFarm->GetTeamID() == eTeam && pFarm->GetHp() == 0;
		});

		COLLTILE* pGoal = m_pLevel->GetCollTile((*iter_find)->GetTileIndex());
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);
	
		m_BehaviorList.push_back([&]()->int { return Build(); });
	}
	else
		return 1;


	return 0;
}

int DAICommand::MoveToHQ(float fTime)
{	
	if (true == m_vecHQ.empty())
	{
		auto iter_Begin = GameMgr->GetObjectList(OBJ_HQ).begin();
		auto iter_End = GameMgr->GetObjectList(OBJ_HQ).end();

		m_vecHQ.assign(iter_Begin, iter_End);

		std::random_shuffle(m_vecHQ.begin(), m_vecHQ.end());
	}

	if (true == m_vecPath.empty())
	{
		const COLLTILE* pGoal = m_pLevel->GetCollTile(m_vecHQ.back()->GetTileIndex());
		m_vecHQ.pop_back();
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);
	}
	
	if (m_vecHQ.size() == 1)
	{
		// 집 근처로 가서 현재 상황에 맞는 유닛 ㄱ
		m_BehaviorList.push_back([&]()->int { return MoveToTeamHQ(m_fPlayTime + 15.f); });
		return 1;
	}

	if (fTime < m_fPlayTime)
		return 1;

	return 0;
}

int DAICommand::MoveToTeamHQ(float fTime)
{
	if (true == m_vecPath.empty())
	{
		auto iter_Begin = GameMgr->GetObjectList(OBJ_HQ).begin();
		auto iter_End = GameMgr->GetObjectList(OBJ_HQ).end();

		TEAMID eTeam = m_pACommander->GetTeamID();
		auto iter_find = std::find_if(iter_Begin, iter_End,
			[&eTeam](auto& pHQ)
		{
			return pHQ->GetTeamID() == eTeam;
		});

		const COLLTILE* pGoal = m_pLevel->GetCollTile((*iter_find)->GetTileIndex());
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);
	}
	else
	{
		m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(m_fPlayTime + 2.f); });
		return 1;

	}
	return 0;
}

int DAICommand::MoveToTeamArea(float fTime)
{
	if (true == m_vecPath.empty())
	{
		auto iter_Begin = GameMgr->GetObjectList(OBJ_HQ).begin();
		auto iter_End = GameMgr->GetObjectList(OBJ_HQ).end();

		TEAMID eTeam = m_pACommander->GetTeamID();
		auto iter_find = std::find_if(iter_Begin, iter_End,
			[&eTeam](auto& pHQ)
		{
			return pHQ->GetTeamID() == eTeam;
		});

		int iIndex = 0;
		int iRange = 4;
		while (iIndex == 0)
		{
			int iNum = GameMgr->GetRandom(0, NEIGHBOR_END  - 1);
			iIndex = m_pLevel->GetNeighborTileIndex(iNum, (*iter_find)->GetTileIndex(), iRange);

			if (m_pLevel->GetCollTile(iIndex)->byOption != 0 || m_pLevel->GetTileObject(iIndex) != nullptr)
				iIndex = 0;
		
			++iRange;
		}
		
		const COLLTILE* pGoal = m_pLevel->GetCollTile(iIndex);
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);
	}
	else
	{
		m_BehaviorList.push_back([&]()->int { return Build(GameMgr->GetRandom(0, 1), m_fPlayTime + 10.f); });
		return 1;
	}

	return 0;
}

int DAICommand::Build(float fTime)
{
	if (true == m_vecPath.empty())
	{
		m_pACommander->m_bBuild = true;
		m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(m_fPlayTime + 2.f); });
		//m_BehaviorList.push_back([&]()->int { return MoveToHQ(m_fPlayTime + 30.f); });
		return 1;
	}

	return 0;
}

int DAICommand::Build(int iSelect, float fTime)
{
	if (true == m_vecPath.empty())
	{
		m_pACommander->m_iSelectSlot = iSelect;
		m_pACommander->m_bBuild = true;
		m_BehaviorList.push_back([&]()->int { return Wait(m_fPlayTime + 5.f); });
		return 1;
	}

	return 0;
}


