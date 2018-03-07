#include "stdafx.h"
#include "ToolManager.h"
#include "Level.h"

CToolManager::CToolManager()
{
}


CToolManager::~CToolManager()
{
	Release();
}

HRESULT CToolManager::Initialize()
{
	m_pLevel = new CLevel;
	if (FAILED(m_pLevel->Initialize()))
	{
		MSG_BOX(TEXT("Isometric Initialize Failed"));
		return E_FAIL;
	}

	m_fZoom = 1.f;
	m_bCollTileRender = false;
	return S_OK;
}

void CToolManager::Release()
{
	SafeDelete(m_pLevel);
}
