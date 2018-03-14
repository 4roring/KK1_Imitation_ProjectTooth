#pragma once
class CTextureManager
	: public CSingleton<CTextureManager>
{
private:
	friend CSingleton;
	explicit CTextureManager();
	virtual ~CTextureManager();
	CTextureManager(const CTextureManager&) = delete;
	CTextureManager& operator=(CTextureManager&) = delete;

public:
	const TEXINFO* GetTexture(const std::wstring& wstrObjKey
		, const std::wstring wstrStateKey = L""
		, const int& iCount = 0);

public:
	HRESULT InsertTexture(const std::wstring& wstrFilePath
		, const std::wstring& wstrObjKey
		, TEXTYPE eTexturetype
		, const std::wstring& wstrStateKey = L""
		, const int& iCount = 0);

private:
	void Release();

private:
	TEXTUREMAP m_mapTexture;
};

