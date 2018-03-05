#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::GetTexture(const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapMultiTex.find(wstrStateKey);
	if(iter == m_mapMultiTex.end())
		return nullptr;

	return iter->second[iCount];
}

HRESULT CMultiTexture::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey, const int & iCount)
{
	TCHAR szPath[MAX_PATH] = L"";
	std::vector<TEXINFO*> vecTexture;

	for (int i = 0; i < iCount; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImageInfo)))
		{
			MSG_BOX(szPath);
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(Device->GetDevice()
			, szPath
			, pTexInfo->tImageInfo.Width, pTexInfo->tImageInfo.Height
			, pTexInfo->tImageInfo.MipLevels, 0, pTexInfo->tImageInfo.Format
			, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT
			, NULL, &pTexInfo->tImageInfo, nullptr, &pTexInfo->pTexture)))
		{
			MSG_BOX(szPath);
			return E_FAIL;
		}
		vecTexture.push_back(pTexInfo);
	}

	m_mapMultiTex.insert(MULTITEXMAP::value_type(wstrStateKey, vecTexture));

	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& pair : m_mapMultiTex)
	{
		for (auto& pTexInfo : pair.second)
		{
			SafeRelease(pTexInfo->pTexture);
			SafeDelete(pTexInfo);
			pTexInfo = nullptr;
		}
	}
	m_mapMultiTex.clear();
}
