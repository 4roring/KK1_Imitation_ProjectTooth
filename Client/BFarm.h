#pragma once
#include "Building.h"
class ACommander;
class BFarm :
	public BBuilding
{
public:
	BFarm();
	virtual ~BFarm();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetLevel();
	void SetCrop();
	void CreateFinished();
	void DestroyCropRandom();
	void DestroyPig();

private:
	enum FARMSTATE { Grass, OnStream, Farm, FarmEnd, End };
	FARMSTATE m_eCurState = FARMSTATE::Grass;
	FARMSTATE m_ePreState = FARMSTATE::End;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();

private:
	ACommander* m_pCommander = nullptr;
	float m_fFoodUpTime = 0.f;
	int m_iFood = 0;
	CGameObject* m_pCrop[9] = {};
	CGameObject* m_pPig = nullptr;
};

