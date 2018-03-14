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

protected:
	AUnit* m_pUnit;
};

