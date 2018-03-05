#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEXINFO * CSingleTexture::GetTexture(const std::wstring & wstrStateKey, const int & iCoun)
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey, const int & iCount)
{
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

	return S_OK;
}

void CSingleTexture::Release()
{
	SafeRelease(m_pTexInfo->pTexture);
	SafeDelete(m_pTexInfo);
}
