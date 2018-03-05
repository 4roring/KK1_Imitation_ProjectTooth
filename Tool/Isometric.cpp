#include "stdafx.h"
#include "Isometric.h"
#include "ToolView.h"

CIsometric::CIsometric()
{
}


CIsometric::~CIsometric()
{
	Release();
}

HRESULT CIsometric::Initialize()
{
	m_pSprite = Device->GetSprite();
	m_pFont = Device->GetFont();

	if (FAILED(TextureMgr->InsertTexture(TEXT("../Texture/Map/Map03.png"), TEXT("Map03"), TEX_SINGLE)))
	{
		MSG_BOX(TEXT("Map03 Texture Load Failed"))

		return E_FAIL;
	}
		
	if (FAILED(TextureMgr->InsertTexture(TEXT("../Texture/Tile/Isometric%d.png"), TEXT("TILE"), TEX_MULTI, TEXT("Isometric"), 2)))
	{
		MSG_BOX(TEXT("Isometric MultiTexture Load Failed"));

		return E_FAIL;
	}

	m_vecIsoTile.reserve(ISOTILEX * ISOTILEY);

	for (int y = 0; y < ISOTILEY; ++y)
	{
		for (int x = 0; x < ISOTILEX; ++x)
		{
			ISOTILE* pIsoTile = new ISOTILE;

			float fX = x * ISOTILECX + (y & 1) * (ISOTILECX * 0.5f);
			float fY = y * (ISOTILECY * 0.5f);

			pIsoTile->vPosition = D3DXVECTOR3(fX, fY, 0.f);
			pIsoTile->byOption = 0;
			pIsoTile->byDrawID = 0;

			m_vecIsoTile.push_back(pIsoTile);
		}
	}

	m_byOption = 1;
	m_byDrawID = 1;

	return S_OK;
}

void CIsometric::Update()
{
	m_iPickIndex = GetTileIndex(GetMousePos());
	Picking();
}

void CIsometric::Render()
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	D3DXMATRIX matWorld, matScale, matTrans;
	D3DXMatrixIdentity(&matTrans);

	const TEXINFO* pTexture = TextureMgr->GetTexture(TEXT("Map03"));

	D3DXMatrixScaling(&matScale, fZoom, fZoom, 1.f);

	D3DXMatrixTranslation(&matTrans
		, 0.f - vScroll.x
		, 0.f - vScroll.y
		, 0.f);

	matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(pTexture->pTexture
		, nullptr, nullptr, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR szBuf[128] = L"";

	if (false == ToolMgr->GetIsoRender()) 
		return;

	for (int y = 0; y < ISOTILEY; ++y)
	{
		for (int x = 0; x < ISOTILEX; ++x)
		{
			int iIndex = y * ISOTILEX + x;

			if (isCulling(m_vecIsoTile[iIndex]->vPosition))
				continue;

			pTexture = TextureMgr->GetInstance()->GetTexture(
				TEXT("TILE"), TEXT("Isometric"), m_vecIsoTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, m_vecIsoTile[iIndex]->vPosition.x * fZoom - vScroll.x
				, m_vecIsoTile[iIndex]->vPosition.y * fZoom - vScroll.y
				, 0.f);


			matWorld = matScale * matTrans;

			m_pSprite->SetTransform(&matWorld);

			D3DCOLOR color = (iIndex == m_iPickIndex) ?
				D3DCOLOR_ARGB(255, 255, 0, 0) : D3DCOLOR_ARGB(255, 255, 255, 255);
			
			if (iIndex == m_iPickIndex)
				int a = 1;
		
			m_pSprite->Draw(pTexture->pTexture
				, nullptr
				, &D3DXVECTOR3(ISOTILECX * 0.5f, ISOTILECY * 0.5f, 0.f)
				, nullptr
				, color);

			/*if (iIndex & 1)
			{
				m_pSprite->SetTransform(&matTrans);

				swprintf_s(szBuf, TEXT("%d"), iIndex);
				m_pFont->DrawTextW(m_pSprite, szBuf, lstrlen(szBuf)
					, nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
			}	*/	
		}
	}
}

void CIsometric::Release()
{
	std::for_each(m_vecIsoTile.begin(), m_vecIsoTile.end(), SafeDelete<ISOTILE*>);
	VECISOTILE vec;
	m_vecIsoTile.swap(vec);
}

void CIsometric::MiniMap()
{
	const TEXINFO* pTexture = TextureMgr->GetTexture(TEXT("Map03"));

	D3DXMATRIX matScale, matTrans;
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 1.f);
	D3DXMatrixTranslation(&matTrans, 100.f, 0.f, 0.f);

	matScale *= matTrans;

	m_pSprite->SetTransform(&matScale);

	Device->GetSprite()->Draw(pTexture->pTexture
		, nullptr, nullptr, &D3DXVECTOR3(0.f, 0.f, 0.f)
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

bool CIsometric::isCulling(const D3DXVECTOR3& vPos)
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	if (vPos.x * fZoom < 0.f + (vScroll.x + 50.f)) return true;
	if (vPos.y * fZoom < 0.f + (vScroll.y + 50.f)) return true;
	if (vPos.x * fZoom > WINCX + (vScroll.x - 50.f)) return true;
	if (vPos.y * fZoom > WINCY + (vScroll.y - 50.f)) return true;

	//if (vPos.x * fZoom < 0.f + (vScroll.x - 50.f)) return true;
	//if (vPos.y * fZoom < 0.f + (vScroll.y - 50.f)) return true;
	//if (vPos.x * fZoom > WINCX + (vScroll.x + 50.f)) return true;
	//if (vPos.y * fZoom > WINCY + (vScroll.y + 50.f)) return true;

	return false;
}

D3DXVECTOR3 CIsometric::GetMousePos()
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	POINT tPos = {};
	GetCursorPos(&tPos);
	ScreenToClient(g_hWnd, &tPos);

	float fX = (float)tPos.x;
	float fY = (float)tPos.y;



	return (D3DXVECTOR3(fX, fY, 0.f) + vScroll) / fZoom;
}

int CIsometric::GetTileIndex(D3DXVECTOR3 vPos)
{
	int iPickIdx = (int)(vPos.x / ISOTILECX) + ISOTILEX + (ISOTILEX * 2) * (int)(vPos.y / ISOTILECY);
	
	if (iPickIdx < 0 || iPickIdx >= ISOTILEX * ISOTILEY - 1)
		return -1;

	D3DXVECTOR3 vTemp = m_vecIsoTile[iPickIdx]->vPosition;

	D3DXVECTOR3 vPoint[4] =
	{
		{ vTemp.x - ISOTILECX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x, vTemp.y - ISOTILECY * 0.5f, 0.f },
		{ vTemp.x + ISOTILECX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x , vTemp.y + ISOTILECY * 0.5f, 0.f }
	};

	float fGradient = (ISOTILECY * 0.5f) / (ISOTILECX * 0.5f);

	float fB[4];

	for (int i = 0; i < 4; ++i)
	{

		fB[i] = (i & 1) ? -fGradient : fGradient ;
		fB[i] = fB[i] * vPoint[i].x + vPoint[i].y;
	}

	if (vPos.y + fGradient * vPos.x - fB[0] <= 0.f) return iPickIdx - ISOTILEX;
	if (vPos.y - fGradient * vPos.x - fB[1] < 0.f) return iPickIdx - (ISOTILEX - 1);
	if (vPos.y + fGradient * vPos.x - fB[2] > 0.f) return iPickIdx + (ISOTILEX + 1);
	if (vPos.y - fGradient * vPos.x - fB[3] > 0.f) return iPickIdx + ISOTILEX ;

	return iPickIdx;
}

void CIsometric::Picking()
{
	if (GetKey->KeyPress(VK_LBUTTON))
	{
		if (m_iPickIndex < 0 || m_iPickIndex >= ISOTILEX * ISOTILEY - 1)
			return;
	}
}

void CIsometric::TileChange()
{
}
