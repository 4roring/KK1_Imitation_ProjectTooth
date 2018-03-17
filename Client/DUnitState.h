#pragma once
#include "DState.h"

class AUnit;
class DObserver;
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
	void Release();

public:
	void SetUnit(AUnit* pUnit) { m_pUnit = pUnit; }
	void SetUnitInfo(UNITINFO& rUnitInfo, int iMaxHp, int iAtk, float fAtkTime, int iRange, int iSight);

protected:
	CGameObject* GetTileIndexObject();
	const Vector3& GetTilePos(int iIndex);
	bool CheckTileEmpty();
	bool IsOrder();
	bool CheckAroundBlockTile();
	bool CheckSight();
	bool CheckRange();

protected:
	void ShotBullet(BULLETID eBulletID);

protected:
	COLLTILE* GetAroundEmptyTile();
	void GetPath(const VECCOLLTILE vecPath);

protected:
	AUnit* m_pUnit = nullptr;
	DObserver* m_pObserver = nullptr;
	VECCOLLTILE m_vecPath;
	COLLTILE* m_pPreTile = nullptr;
	float m_fAttackDelay = 0.f;

protected:
	void MovePath(float deltaTime);
};

