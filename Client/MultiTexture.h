#pragma once
#include "Texture.h"
class CMultiTexture :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();

	// CTexture��(��) ���� ��ӵ�
	virtual const TEXINFO * GetTexture(const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual HRESULT InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	MULTITEXMAP m_mapMultiTex;
};

