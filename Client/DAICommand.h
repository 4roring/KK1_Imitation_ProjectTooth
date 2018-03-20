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
	int Wait(float fTime = 9999999.f);
	int MoveToEmptyFarm(float fTime = 9999999.f);
	int MoveToHQ(float fTime = 9999999.f);
	int MoveToTeamHQ(float fTime = 999999.f);
	int MoveToTeamArea(float fTime = 999999.f);
	int Build(float fTime = 9999999.f);
	int Build(int iSelect, float fTime = 9999999.f);

private:
	VECCOLLTILE m_vecPath;
	std::vector<CGameObject*> m_vecHQ;
	CLevel* m_pLevel = nullptr;
	float m_fPlayTime = 0.f;
	std::list<std::function<int()>> m_BehaviorList;
};

