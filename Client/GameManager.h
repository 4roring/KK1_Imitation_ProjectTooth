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
	const OBJLIST& GetObjectList(OBJID eObjID) { return ObjectList[eObjID]; }
	const D3DCOLOR* GetTeamColor(TEAMID eTeamID) { return &m_TeamColor[eTeamID]; }
	DSubject* GetSubject(TEAMID eTeam) const { return m_pSubject[eTeam]; }
	CAStar* GetAStar() const { return m_pAStar; }

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
	OBJLIST ObjectList[OBJ_END];
	D3DCOLOR m_TeamColor[TEAM_END];
	VECRENDER m_vecRender[LAYER_END];

private:
	DSubject* m_pSubject[TEAM_NEUTRAL];
	CAStar* m_pAStar;
};

