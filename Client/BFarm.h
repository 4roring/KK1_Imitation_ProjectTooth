#pragma once
#include "Building.h"
class BFarm :
	public CBuilding
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

private:
	enum FARMSTATE { Grass, OnStream, Farm, FarmEnd, End };
	FARMSTATE m_eCurState = FARMSTATE::Grass;
	FARMSTATE m_ePreState = FARMSTATE::End;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();
};

