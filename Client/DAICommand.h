#pragma once
#include "DCommand.h"
class CLevel;
class DAICommand :
	public DCommand
{
public:
	DAICommand();
	virtual ~DAICommand();

public:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	void FSM(float deltaTime);

private:
	void MovePath(float deltaTime);

private:
	int Wait(float fTime);
	int MoveToEmptyFarm();
	int ReconToHQ();
	int MoveToTeamHQ();
	int MoveToTeamArea();
	int Build();
	int Build(int iSelect);
	int AttackToEnemyTeam(int iTeam);
	int Order();

private:
	VECCOLLTILE m_vecPath;
	std::vector<CGameObject*> m_vecHQ;
	CLevel* m_pLevel = nullptr;
	float m_fEndTime = 0.f;
	float m_fPlayTime = 0.f;
	std::list<std::function<int()>> m_BehaviorList;

private:
	int m_iUnitFactory = 0;
};

