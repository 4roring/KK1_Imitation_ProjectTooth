#include "stdafx.h"
#include "AtlasTexture.h"


CAtlasTexture::CAtlasTexture()
{
}


CAtlasTexture::~CAtlasTexture()
{
}

const TEXINFO * CAtlasTexture::GetTexture(const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapAtlasTex.find(wstrStateKey);
	if (iter == m_mapAtlasTex.end())
		return nullptr;

	m_pTexInfo->tRect = iter->second;

	return m_pTexInfo;
}

HRESULT CAtlasTexture::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey, const int & iCount)
{
	TCHAR szPath[MAX_PATH] = L"";

	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImageInfo)))
	{
		MSG_BOX(wstrStateKey.c_str());
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(Device->GetDevice()
		, wstrFilePath.c_str()
		, m_pTexInfo->tImageInfo.Width, m_pTexInfo->tImageInfo.Height
		, m_pTexInfo->tImageInfo.MipLevels, 0, m_pTexInfo->tImageInfo.Format
		, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL
		, &m_pTexInfo->tImageInfo, nullptr, &m_pTexInfo->pTexture)))
	{
		MSG_BOX(wstrStateKey.c_str());
		return E_FAIL;
	}

	LoadAtlasInfo(wstrFilePath);

	return S_OK;
}

void CAtlasTexture::Release()
{
	std::for_each(m_mapAtlasTex.begin(), m_mapAtlasTex.end(),
		[](auto& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	});

	SafeRelease(m_pTexInfo->pTexture);
	SafeDelete(m_pTexInfo);

	m_mapAtlasTex.clear();
}

void CAtlasTexture::LoadAtlasInfo(const std::wstring & wstrFilePath)
{
	int iIndex = wstrFilePath.rfind('.');
	std::wstring FilePath = wstrFilePath.substr(0, iIndex);
	FilePath.append(TEXT(".txt"));

	std::wifstream LoadFile;
	LoadFile.open(FilePath, std::ios::in);

	TCHAR szBuf[128] = {};

	while (false == LoadFile.eof())
	{
		std::wstring wstrStateKey;
		LPRECT rc = new RECT;
		int iCX = 0;
		int iCY = 0;

		LoadFile.getline(szBuf, sizeof(szBuf), ' ');
		wstrStateKey = szBuf;

		LoadFile.getline(szBuf, sizeof(szBuf), ' '); // "= " Á¦°Å

		LoadFile.getline(szBuf, sizeof(szBuf), ' ');
		rc->left = _wtoi(szBuf);
		
		LoadFile.getline(szBuf, sizeof(szBuf), ' ');
		rc->top = _wtoi(szBuf);

		LoadFile.getline(szBuf, sizeof(szBuf), ' ');
		iCX = _wtoi(szBuf);

		LoadFile.getline(szBuf, sizeof(szBuf));
		iCY = _wtoi(szBuf);

		rc->right = rc->left + iCX;
		rc->bottom = rc->top + iCY;

		m_mapAtlasTex.insert(ATLASTEXMAP::value_type(wstrStateKey, rc));
	}
}
