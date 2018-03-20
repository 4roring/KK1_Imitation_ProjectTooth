#pragma once
#include "UUI.h"
class UUnitFactoryUI :
	public UUI
{
public:
	UUnitFactoryUI();
	virtual ~UUnitFactoryUI();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetUnitID(UNITID eUnitID) { m_eUnitID = eUnitID; }

private:
	void SetUnitUI();
	void SetFillRatio();
	void UnitIconRender();
	void HpFillRender();

private:
	UNITID m_eUnitID = UNIT_ALL;
	LPRECT m_pTexUnitCircle = nullptr;
	LPRECT m_pTexUnitUI = nullptr;
	LPRECT m_pTexUnitTintUI = nullptr;
	RECT m_tHpFill = {};
	const D3DCOLOR* m_pColor = nullptr;
	int m_iHpFillHeight = 0;
};

