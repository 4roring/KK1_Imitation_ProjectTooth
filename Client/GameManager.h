#pragma once
#include "Function.h"

class CAStar;
class DSubject;
class ACommander;
class CLevel;
class CGameManager :
	public CSingleton<CGameManager>
{
private:
	friend CSingleton;
	explicit CGameManager();
	virtual ~CGameManager();
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(CGameManager&) = delete;

public:
	const OBJLIST& GetObjectList(OBJID eObjectID) const { return m_ObjectList[eObjectID]; }
	const D3DCOLOR* GetTeamColor(TEAMID eTeamID) const { return &m_TeamColor[eTeamID]; }
	DSubject* GetSubject(TEAMID eTeamID) const { return m_pSubject[eTeamID]; }
	CAStar* GetAStar() const { return m_pAStar; }
	ACommander* GetCommander(TEAMID eTeamID) const { return m_pCommander[eTeamID]; }
	int GetRandom(int iMin, int iMax) const;

public:
	void CreateObject(CGameObject* pObject, OBJID eID);
	void DestroyObject(int eObjID);
	bool ObjectCulling(const Vector3& vPos);

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
	ACommander* m_pCommander[TEAM_END];

//#ifdef _DEBUG
private:
	void UpdateFPS(float deltaTime);
	void RenderFPS();
private:
	float m_fFPSTime = 0.f;
	int m_iCount = 0;
	int m_iFPS = 0;
//#endif
};

