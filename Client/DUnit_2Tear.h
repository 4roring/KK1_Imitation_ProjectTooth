#pragma once
#include "DUnitState.h"
class DUnit_2Tear :
	public DUnitState
{
public:
	DUnit_2Tear();
	virtual ~DUnit_2Tear();

public:
	virtual HRESULT Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

private:
	enum ANIMSTATE { Idle, Move, Attack, End };
	ANIMSTATE m_eCurState = ANIMSTATE::Idle;
	ANIMSTATE m_ePreState = ANIMSTATE::End;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();
	HRESULT SetUnitState();

private:
	bool m_bAttack = false;
};

