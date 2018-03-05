#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

	// CTexture을(를) 통해 상속됨
	virtual const TEXINFO * GetTexture(const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual HRESULT InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO* m_pTexInfo = nullptr;
};

