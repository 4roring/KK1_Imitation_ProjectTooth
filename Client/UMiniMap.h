#pragma once
#include "UUI.h"
class UMiniMap :
	public UUI
{
public:
	UMiniMap();
	virtual ~UMiniMap();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateMiniMap();
	void MiniRender(OBJID eObject, DWORD* pColor, int iSize);

private:
	const TEXINFO* m_pTexMini = nullptr;
};

