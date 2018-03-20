#pragma once
#include "DUnitState.h"
class DUnit_3Tear :
	public DUnitState
{
public:
	DUnit_3Tear();
	virtual ~DUnit_3Tear();

public:
	virtual HRESULT Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;

private:
	enum ANIMSTATE { Idle, Move, Attack, Dead, End };
	ANIMSTATE m_eCurState = ANIMSTATE::Idle;
	ANIMSTATE m_ePreState = ANIMSTATE::End;

private:
	void UpdateState(float deltaTime);
	void BadgerPowerUpdate(float deltaTime);
	void SetAnimState();
	HRESULT SetUnitState();

private:
	bool m_bAttack = false;
	float m_fMiniGunTime = 0.f;
};

