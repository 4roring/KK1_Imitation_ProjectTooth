#pragma once
#include "Function.h"
class CGameManager :
	public CSingleton<CGameManager>
{
public:
	CGameManager();
	virtual ~CGameManager();

public:
	void CreateObject(CGameObject* pObject, OBJID eID);

public:
	void Update(float deltaTime);
	void Render();

private:
	OBJLIST m_ObjectList[OBJ_END];
};

