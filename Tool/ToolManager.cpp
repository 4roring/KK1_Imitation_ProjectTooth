#include "stdafx.h"
#include "ToolManager.h"
#include "Isometric.h"

CToolManager::CToolManager()
{
}


CToolManager::~CToolManager()
{
	Release();
}

HRESULT CToolManager::Initialize()
{
	m_pIsometric = new CIsometric;
	if (FAILED(m_pIsometric->Initialize()))
	{
		MSG_BOX(TEXT("Isometric Initialize Failed"));
		return E_FAIL;
	}

	m_fZoom = 1.f;
	m_bIsoRender = false;
	return S_OK;
}

void CToolManager::Release()
{
	SafeDelete(m_pIsometric);
}
