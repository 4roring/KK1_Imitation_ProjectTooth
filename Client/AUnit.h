#pragma once
#include "Actor.h"

class BUnitFactory;
class DUnitState;
class UHpUI;
class AUnit :
	public AActor
{
public:
	AUnit();
	virtual ~AUnit();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	UNITID GetUnitID() { return m_eUnitID; }

public:
	void SetUnitID(UNITID eUnitID) { m_eUnitID = eUnitID; }
	void SetFactory(BUnitFactory* pFactory) { m_pFactory = pFactory; }

public:
	bool CircleCollision(CGameObject* pUnit);

private:
	UNITID m_eUnitID;
	UNITINFO m_tUnitInfo;
	DUnitState* m_pUnitState;

	friend DUnitState;
	friend class DUnit_1Tear;
	friend class DUnit_2Tear;
	friend class DUnit_3Tear;

private:
	BUnitFactory* m_pFactory = nullptr;
	CGameObject* m_pHpUI = nullptr;
};

