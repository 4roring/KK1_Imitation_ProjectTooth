#pragma once
#include "Texture.h"
class CAtlasTexture :
	public CTexture
{
public:
	CAtlasTexture();
	virtual ~CAtlasTexture();

	// CTexture��(��) ���� ��ӵ�
	virtual const TEXINFO * GetTexture(const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual HRESULT InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	void LoadAtlasInfo(const std::wstring & wstrFilePath);

private:
	ATLASTEXMAP m_mapAtlasTex;
	TEXINFO* m_pTexInfo = nullptr;
};

