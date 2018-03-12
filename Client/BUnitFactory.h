#pragma once
#include "Building.h"
class BUnitFactory :
	public CBuilding
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

private:
	HRESULT SetTexture();

private:
	UNITID m_eUnitID;
};

