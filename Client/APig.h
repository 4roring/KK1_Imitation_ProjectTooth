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
};

