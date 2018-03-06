#include "stdafx.h"
#include "ToolManager.h"
#include "CollisionTile.h"

CToolManager::CToolManager()
{
}


CToolManager::~CToolManager()
{
	Release();
}

HRESULT CToolManager::Initialize()
{
	m_pCollTile = new CCollisionTile;
	if (FAILED(m_pCollTile->Initialize()))
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
	SafeDelete(m_pCollTile);
}
