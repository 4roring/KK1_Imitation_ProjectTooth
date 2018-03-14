#pragma once
#include "Actor.h"

class DUnitState;
class AUnit :
	public CActor
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

private:
	UNITID m_eUnitID;
	UNITINFO m_tUnitInfo;
	DUnitState* m_pUnitState;
	friend class DUnit_1Tear;

	// TODO: �÷��̾��� ���� �ѹ� �Ǵ� ���콺 �Է��� �����ϴ� ������ �߰�.
};

