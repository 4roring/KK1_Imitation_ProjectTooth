#pragma once
#include "Function.h"

class CAStar;
class DSubject;
class CGameManager :
	public CSingleton<CGameManager>
{
private :
	friend CSingleton;
	explicit CGameManager();
	virtual ~CGameManager();
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(CGameManager&) = delete;

public:
	CGameObject* GetTeamCommander(TEAMID eTeam) const;
	const OBJLIST& GetObjectList(OBJID eObjID) const { return m_ObjectList[eObjID]; }
	const D3DCOLOR* GetTeamColor(TEAMID eTeamID) const { return &m_TeamColor[eTeamID]; }
	DSubject* GetSubject(TEAMID eTeam) const { return m_pSubject[eTeam]; }
	CAStar* GetAStar() const { return m_pAStar; }
	int GetRandom(int iMin, int iMax);

public:
	void CreateObject(CGameObject* pObject, OBJID eID);

public:
	void DestroyObject(int eObjID);

public:
	void Initialize();
	void Update(float deltaTime);
	void LateUpdate();
	void Render();
	void Release();

private:
	OBJLIST m_ObjectList[OBJ_END];
	D3DCOLOR m_TeamColor[TEAM_END];
	VECRENDER m_vecRender[LAYER_END];

private:
	DSubject* m_pSubject[TEAM_NEUTRAL];
	CAStar* m_pAStar;
};

