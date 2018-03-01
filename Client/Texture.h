#pragma once
class CTexture abstract
{
public:
	CTexture();
	virtual ~CTexture();

public:
	virtual const TEXINFO* GetTexture(const std::wstring& wstrStateKey = L""
		, const int& iCount = 0) PURE;

	virtual HRESULT InsertTexture(const std::wstring& wstrFilePath
		, const std::wstring& wstrStateKey = L""
		, const int& iCount = 0) PURE;

	virtual void Release() PURE;
};

