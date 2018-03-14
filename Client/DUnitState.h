#pragma once
#include "DState.h"

class AUnit;
class DUnitState :
	public DState
{
public:
	DUnitState();
	virtual ~DUnitState();

public:
	virtual HRESULT Initialize() PURE;
	virtual void Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;

public:
	void SetUnit(AUnit* pUnit) { m_pUnit = pUnit; }
	void SetUnitInfo(UNITINFO& rUnitInfo, int iMaxHp, int iAtk, float fAtkTime, int iRange, int iSight);

protected:
	CGameObject* GetTileIndexObject();
	const Vector3& GetTilePos(int iIndex);
	bool CheckTileEmpty();

protected:
	COLLTILE* GetAroundEmptyTile();

protected:
	AUnit* m_pUnit;
	VECCOLLTILE m_vecPath;

protected:
	void SetPath(decltype(m_vecPath)& vecPath);

protected:
	void MovePath(float deltaTime);
};

