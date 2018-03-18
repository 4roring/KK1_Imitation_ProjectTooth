#pragma once
#include "Actor.h"
class APig :
	public AActor
{
public:
	APig();
	virtual ~APig();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetTileIndexArr(int* pTileIndexArr);

private:
	enum ANIMSTATE { Idle, Move, Work, Attack, End };
	ANIMSTATE m_eCurState = ANIMSTATE::Idle;
	ANIMSTATE m_ePreState = ANIMSTATE::End;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();
	void SelectNextTile();
	bool CheckNextDistance();
	void ShotBullet();

private:
	UNITINFO m_tUnitInfo = {};
	int* m_pTileIndexArr = nullptr;
	float m_fIdleTime = 0.f;
	float m_fAttackDelay = 0.f;
};

