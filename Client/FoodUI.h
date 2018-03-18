#pragma once
#include "UUI.h"
class UFoodUI :
	public UUI
{
public:
	UFoodUI();
	virtual ~UFoodUI();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	LPD3DXFONT m_pFoodFont = nullptr;
	LPRECT m_tRect = {};
	int m_iFood = 0;
};

