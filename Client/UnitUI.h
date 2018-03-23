#pragma once
#include "UUI.h"
class UUnitUI :
	public UUI
{
public:
	UUnitUI();
	virtual ~UUnitUI();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void SetUnitUI();

private:
	void UnitSelectUIRender();

protected:
	void UnitInfoUIRender();

private:
	LPD3DXFONT m_pUnitCountFont;

private:
	LPRECT m_pTexUnitCircle = nullptr;
	LPRECT m_pTexUnitUI[6] = {};
	LPRECT m_pTexUnitTintUI[6] = {};
	LPRECT m_pTexPogarrows = nullptr;
	LPRECT m_pMidBar = nullptr;
	LPRECT m_pInfoBar = nullptr;
	UNITID m_eUnitSlot[SLOT_MAX] = {};
	const D3DCOLOR* m_pColor = nullptr;
	int m_iSelectSlot = 0;
};

