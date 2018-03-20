#pragma once
#include "UUI.h"
class UHpUI :
	public UUI
{
public:
	UHpUI();
	virtual ~UHpUI();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	
	void SetFillRatio();
	void HpBackgroundRender();
	void HpFillRender();

private:
	
	LPRECT m_pHpBg = nullptr;
	RECT m_tHpFill = {};
	int m_iHpFillHeight = 0;
};

