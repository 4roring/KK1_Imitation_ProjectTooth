#pragma once
#include "Actor.h"

class DUnitState;
class BUnitFactory;
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
	void SetUnitID(UNITID eUnitID) { m_eUnitID = eUnitID; }
	void SetFactory(BUnitFactory* pFactory) { m_pFactory = pFactory; }

private:
	UNITID m_eUnitID;
	UNITINFO m_tUnitInfo;
	DUnitState* m_pUnitState;

	friend DUnitState;
	friend class DUnit_1Tear;

private:
	BUnitFactory* m_pFactory = nullptr;

	// TODO: 플레이어의 선택 넘버 또는 마우스 입력을 감지하는 옵저버 추가.
};

