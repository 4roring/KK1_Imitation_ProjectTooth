#include "stdafx.h"
#include "TextureManager.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
#include "AtlasTexture.h"


CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
	Release();
}

const TEXINFO * CTextureManager::GetTexture(const std::wstring & wstrObjKey, const std::wstring wstrStateKey, const int & iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second->GetTexture(wstrStateKey, iCount);
}

HRESULT CTextureManager::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrObjKey, TEXTYPE eTexturetype, const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);
	if (iter == m_mapTexture.end())
	{
		CTexture* pTexture = nullptr;
		switch (eTexturetype)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		case TEX_ATLAS:
			pTexture = new CAtlasTexture;
			break;
		default:
#ifdef _DEBUG
			assert(!"Insert Texture Failed!! Not Texture Type.");
#endif
			break;
		}

		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCount)))
		{
			MSG_BOX(wstrObjKey.c_str());
			return E_FAIL;
		}

		m_mapTexture.emplace(TEXTUREMAP::value_type(wstrObjKey, pTexture));
	}
	else
	{
		if (eTexturetype == TEX_MULTI)
		{
			if (FAILED(iter->second->InsertTexture(wstrFilePath, wstrStateKey, iCount)))
			{
				MSG_BOX(wstrStateKey.c_str());
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

void CTextureManager::Release()
{
	std::for_each(m_mapTexture.begin(), m_mapTexture.end(), 
		[](auto& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	});
}
