#pragma once
#include "Building.h"
class BUnitFactory :
	public BBuilding
{
public:
	BUnitFactory();
	virtual ~BUnitFactory();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetUnitID(UNITID eUnitID) { m_eUnitID = eUnitID; }
	void UnitCountSub() { --m_iUnitCount; }

private:
	void AnimUpdate();

private:
	HRESULT SetUnit();
	void SetFactory();
	void CreateUnit(float deltaTime);

private:
	UNITID m_eUnitID;
	bool m_bBuildEnd = false;
	int m_iTear = 0;
	float m_fProductionTime = 0.f;

private:
	int m_iUnitCountMax = 0;
	int m_iUnitCount = 0;
};


