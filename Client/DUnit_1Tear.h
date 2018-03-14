#pragma once
#include "DUnitState.h"
class DUnit_1Tear :
	public DUnitState
{
public:
	DUnit_1Tear();
	virtual ~DUnit_1Tear();

public:
	virtual HRESULT Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

private:
	enum ANIMSTATE { Idle, Move, Attack };
	ANIMSTATE m_eCurState;
	ANIMSTATE m_ePreState;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();
};

