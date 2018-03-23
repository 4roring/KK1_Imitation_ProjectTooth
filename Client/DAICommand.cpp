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
	m_BehaviorList.push_back([&]()->int { return MoveToEmptyFarm(); });

	m_iFarm = 4;
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
	m_pACommander->m_fOrder -= deltaTime;

	if (false == m_BehaviorList.empty())
		iEvent = m_BehaviorList.front()();
	else
	{
		m_fEndTime = m_fPlayTime + 5.f;
		m_BehaviorList.push_back([&]()->int { return Wait(m_fEndTime); });
	}

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

	if (D3DXVec3Length(&vTarget) < 15.f)
		m_vecPath.pop_back();
}

int DAICommand::Wait(float fTime)
{
	m_pACommander->m_fOrder = 0.0f;
	m_pACommander->m_tInfo.vDir = Vector3(0.f, 0.f, 0.f);

	if (fTime < m_fPlayTime)
	{
		if (m_iUnitFactory > 0)
			m_BehaviorList.push_back([&]()->int { return AttackToEnemyTeam(0); });

		int iNum = GameMgr->GetRandom(0, 100);

		if (iNum > 50)
			m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(); });

		return 1;
	}

	return 0;
}

int DAICommand::MoveToEmptyFarm()
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

		auto iter = m_BehaviorList.begin();
		m_BehaviorList.insert(++iter, [&]()->int { return Build(); });

		return 1;
	}

	return 0;
}

int DAICommand::ReconToHQ()
{
	if (m_iFarm > 7)
	{
		m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(); });
		return 1;
	}

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

	if (m_vecHQ.size() == 1) // 정찰 적당히 완료
	{
		// 집 근처로 가서 현재 상황에 맞는 유닛 ㄱ
		m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(); });
		return 1;
	}

	return 0;
}

int DAICommand::MoveToTeamHQ()
{
	m_pACommander->m_fOrder = 0.f;

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

		if (m_iFarm < 9)
		{
			m_BehaviorList.push_back([&]()->int { return MoveToEmptyFarm(); });
			return 1;
		}

		m_fEndTime = m_fPlayTime + 10.f;
		m_BehaviorList.push_back([&]()->int { return Wait(m_fEndTime); });

		return 1;
	}

	return 0;
}

int DAICommand::MoveToTeamArea()
{
	m_pACommander->m_fOrder = 0.f;

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
			int iNum = GameMgr->GetRandom(0, NEIGHBOR_END - 1);
			iIndex = m_pLevel->GetNeighborTileIndex(iNum, (*iter_find)->GetTileIndex(), iRange);

			if (iIndex < 0 || iIndex > COLLTILEX * COLLTILEY - 1)
				return 1;

			if (m_pLevel->GetCollTile(iIndex)->byOption != 0 || m_pLevel->GetTileObject(iIndex) != nullptr)
				iIndex = 0;

			++iRange;
		}

		const COLLTILE* pGoal = m_pLevel->GetCollTile(iIndex);
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);

		auto iter = m_BehaviorList.begin();
		m_BehaviorList.insert(++iter, [&]()->int { return Build(GameMgr->GetRandom(0, 5)); });
		return 1;
	}

	return 0;
}

int DAICommand::Build()
{
	if (true == m_vecPath.empty())
	{
		m_pACommander->m_bBuild = true;
		m_BehaviorList.push_back([&]()->int { return ReconToHQ(); });
		++m_iFarm;
		return 1;
	}

	return 0;
}

int DAICommand::Build(int iSelect)
{
	if (true == m_vecPath.empty())
	{
		m_pACommander->m_iSelectSlot = iSelect;
		m_pACommander->m_bBuild = true;

		if (m_iUnitFactory != GameMgr->GetObjectList(OBJ_UNITFACTORY).size())
		{
			m_iUnitFactory = GameMgr->GetObjectList(OBJ_UNITFACTORY).size();
			m_BehaviorList.push_back([&]()->int { return MoveToTeamHQ(); });
			return 1;
		}
		else
		{
			m_BehaviorList.push_back([&]()->int { return MoveToTeamArea(); });
			return 1;
		}
	}

	return 0;
}

int DAICommand::AttackToEnemyTeam(int iTeam)
{
	if (true == m_vecPath.empty())
	{
		auto iter_Begin = GameMgr->GetObjectList(OBJ_HQ).begin();
		auto iter_End = GameMgr->GetObjectList(OBJ_HQ).end();

		auto iter_find = std::find_if(iter_Begin, iter_End,
			[&iTeam](auto& pHQ)
		{
			return pHQ->GetTeamID() == iTeam;
		});

		const COLLTILE* pGoal = m_pLevel->GetCollTile((*iter_find)->GetTileIndex());
		GameMgr->GetAStar()->AStarStart(m_pACommander->m_iTileIndex, pGoal, m_vecPath);
		auto iter = m_BehaviorList.begin();
		m_BehaviorList.insert(++iter, [&]()->int { return Order(); });
		return 1;
	}

	return 0;
}

int DAICommand::Order()
{
	m_pACommander->m_fOrder = 0.0f;
	if (m_vecPath.size() % 4 == 0)
	{
		m_pACommander->m_bAllOrder = true;
		m_pACommander->m_fOrder = 0.5f;
	}

	if (m_vecPath.empty())
	{
		m_pACommander->m_bAllOrder = true;
		m_pACommander->m_fOrder = 0.5f;
		m_BehaviorList.push_back([&]()->int { return MoveToTeamHQ(); });
		return 1;
	}

	return 0;
}