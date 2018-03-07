#include "stdafx.h"
#include "Level.h"
#include "ToolView.h"

CLevel::CLevel()
{
}


CLevel::~CLevel()
{
	Release();
}

HRESULT CLevel::Initialize()
{
	m_pSprite = Device->GetSprite();
	m_pFont = Device->GetFont();

	if (FAILED(TextureMgr->InsertTexture(TEXT("../Texture/Map/Map/Map0.png"), TEXT("Map03"), TEX_SINGLE)))
	{
		MSG_BOX(TEXT("Map03 Texture Load Failed"))

			return E_FAIL;
	}

	if (FAILED(TextureMgr->InsertTexture(TEXT("../Texture/Map/Tile/CollisionTile%d.png"), TEXT("TILE"), TEX_MULTI, TEXT("CollisionTile"), 2)))
	{
		MSG_BOX(TEXT("Isometric MultiTexture Load Failed"));

		return E_FAIL;
	}

	m_vecCollTile.reserve(ISOTILEX * ISOTILEY);

	for (int y = 0; y < ISOTILEY; ++y)
	{
		for (int x = 0; x < ISOTILEX; ++x)
		{
			COLLTILE* pIsoTile = new COLLTILE;

			float fX = x * ISOTILECX + (y & 1) * (ISOTILECX * 0.5f);
			float fY = y * (ISOTILECY * 0.5f);

			pIsoTile->vPosition = D3DXVECTOR3(fX, fY, 0.f);
			pIsoTile->byOption = 0;
			pIsoTile->byDrawID = 0;

			m_vecCollTile.push_back(pIsoTile);
		}
	}

	m_byOption = 1;
	m_byDrawID = 1;

	return S_OK;
}

void CLevel::Update()
{
	m_iPickIndex = GetTileIndex(GetMousePos());
	//Picking();
}

void CLevel::Render()
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixScaling(&matScale, fZoom, fZoom, 1.f);

	MapRender(fZoom, vScroll, matScale);

	if (true == ToolMgr->GetCollTileRender())
		CollTileRender(fZoom, vScroll, matScale);

	DecoRender(fZoom, vScroll, matScale);
}

void CLevel::Release()
{
	CollTileRelease();
	DecoRelease();
}

void CLevel::CollTileRelease()
{
	std::for_each(m_vecCollTile.begin(), m_vecCollTile.end(), SafeDelete<COLLTILE*>);
	VECCOLLTILE vecTile;
	m_vecCollTile.swap(vecTile);
}

void CLevel::DecoRelease()
{
	std::for_each(m_vecDeco.begin(), m_vecDeco.end(), SafeDelete<DECO*>);
	VECDECO vecDeco;
	m_vecDeco.swap(vecDeco);
}

void CLevel::MiniMap()
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

bool CLevel::isCulling(const D3DXVECTOR3& vPos)
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

bool CLevel::isScreen(const D3DXVECTOR3 & vPos)
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	if (vPos.x * fZoom < 0.f + vScroll.x) return true;
	if (vPos.y * fZoom < 0.f - vScroll.y) return true;
	if (vPos.x * fZoom > WINCX + vScroll.x) return true;
	if (vPos.y * fZoom > WINCY + vScroll.y) return true;

	return false;
}

void CLevel::MapRender(float& fZoom, D3DXVECTOR3& vScroll, D3DXMATRIX& matScale)
{
	D3DXMATRIX matTrans;
	const TEXINFO* pTexture = TextureMgr->GetTexture(TEXT("Map03"));

	D3DXMatrixTranslation(&matTrans
		, 0.f - vScroll.x
		, 0.f - vScroll.y
		, 0.f);

	matScale *= matTrans;

	m_pSprite->SetTransform(&matScale);
	m_pSprite->Draw(pTexture->pTexture
		, nullptr, nullptr, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLevel::CollTileRender(float& fZoom, D3DXVECTOR3& vScroll, D3DXMATRIX& matScale)
{
	D3DXMATRIX matWorld, matTrans;
	const TEXINFO* pTexture = nullptr;
	TCHAR szBuf[128] = L"";

	for (int y = 0; y < ISOTILEY; ++y)
	{
		for (int x = 0; x < ISOTILEX; ++x)
		{
			int iIndex = y * ISOTILEX + x;

			if (isCulling(m_vecCollTile[iIndex]->vPosition))
				continue;

			pTexture = TextureMgr->GetInstance()->GetTexture(
				TEXT("TILE"), TEXT("CollisionTile"), m_vecCollTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, m_vecCollTile[iIndex]->vPosition.x * fZoom
				, m_vecCollTile[iIndex]->vPosition.y * fZoom
				, 0.f);

			matWorld = matScale * matTrans;

			m_pSprite->SetTransform(&matWorld);

			D3DCOLOR color = (iIndex == m_iPickIndex) ?
				D3DCOLOR_ARGB(255, 255, 0, 0) : D3DCOLOR_ARGB(255, 255, 255, 255);

			m_pSprite->Draw(pTexture->pTexture
				, nullptr
				, &D3DXVECTOR3(ISOTILECX * 0.5f, ISOTILECY * 0.5f, 0.f)
				, nullptr
				, color);

			// 폰트 그리기
			/*D3DXMatrixTranslation(&matTrans
				, m_vecCollTile[iIndex]->vPosition.x * fZoom - 30.f
				, m_vecCollTile[iIndex]->vPosition.y * fZoom - 20.f
				, 0.f);

			matWorld = matScale * matTrans;

			m_pSprite->SetTransform(&matWorld);

			swprintf_s(szBuf, TEXT("%d"), iIndex);
			m_pFont->DrawTextW(m_pSprite, szBuf, lstrlen(szBuf)
				, nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/
		}
	}
}

void CLevel::DecoRender(float& fZoom, D3DXVECTOR3& vScroll, D3DXMATRIX& matScale)
{
	D3DXMATRIX matWorld, matTrans;
	const TEXINFO* pTexture = nullptr;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans
		, GetMousePos().x * fZoom
		, GetMousePos().y * fZoom
		, 0.f);

	matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&matWorld);
	if (false == m_bTileMode && nullptr != m_pItem)
	{
		pTexture = TextureMgr->GetTexture(m_pItem->wstrObjKey, m_pItem->wstrStateKey, m_pItem->iCount);

		m_pSprite->Draw(pTexture->pTexture
			, nullptr
			, &D3DXVECTOR3(float(pTexture->tImageInfo.Width >> 1), float(pTexture->tImageInfo.Height* 0.9f), 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	for (auto& pDeco : m_vecDeco)
	{
		D3DXMatrixTranslation(&matTrans
			, pDeco->vPosition.x * fZoom
			, pDeco->vPosition.y * fZoom
			, 0.f);

		matWorld = matScale * matTrans;

		pTexture = TextureMgr->GetTexture(pDeco->wstrObjKey, pDeco->wstrStateKey, pDeco->iCount);

		m_pSprite->SetTransform(&matWorld);

		m_pSprite->Draw(pTexture->pTexture
			, nullptr
			, &D3DXVECTOR3(float(pTexture->tImageInfo.Width >> 1), float(pTexture->tImageInfo.Height * 0.9f), 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

D3DXVECTOR3 CLevel::GetMousePos()
{
	float fZoom = ToolMgr->GetZoom();
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();

	POINT tPos = {};
	GetCursorPos(&tPos);
	ScreenToClient(g_hWnd, &tPos);

	float fX = (float)tPos.x;
	float fY = (float)tPos.y;
	
	D3DXVECTOR3 vPos = D3DXVECTOR3(fX, fY, 0.f);

	return (vPos + vScroll) / fZoom;
}

int CLevel::GetTileIndex(D3DXVECTOR3 vPos)
{
	int iPickIdx = (int)(vPos.x / ISOTILECX) + ISOTILEX + (ISOTILEX * 2) * (int)(vPos.y / ISOTILECY);

	if (iPickIdx < 0 || iPickIdx >= ISOTILEX * ISOTILEY - 1)
		return -1;

	D3DXVECTOR3 vTemp = m_vecCollTile[iPickIdx]->vPosition;

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

		fB[i] = (i & 1) ? -fGradient : fGradient;
		fB[i] = fB[i] * vPoint[i].x + vPoint[i].y;
	}

	if (vPos.y + fGradient * vPos.x - fB[0] <= 0.f) return iPickIdx - ISOTILEX;
	if (vPos.y - fGradient * vPos.x - fB[1] < 0.f) return iPickIdx - (ISOTILEX - 1);
	if (vPos.y + fGradient * vPos.x - fB[2] > 0.f) return iPickIdx + (ISOTILEX + 1);
	if (vPos.y - fGradient * vPos.x - fB[3] > 0.f) return iPickIdx + ISOTILEX;

	return iPickIdx;
}

void CLevel::Picking()
{
	if (true == m_bFileMode) return;
	if (true == isScreen(GetMousePos())) return;
	
	if (GetKey->KeyPress(VK_LBUTTON))
	{
		if (m_iPickIndex < 0 || m_iPickIndex >= ISOTILEX * ISOTILEY - 1)
			return;

		if (m_bTileMode)
			TileChange();
		else if(nullptr != m_pItem && GetKey->KeyDown(VK_LBUTTON))
			InsertDeco();
	}

	if (nullptr != m_pItem && false == m_vecDeco.empty() && GetKey->KeyDown('X'))
	{
		SafeDelete(m_vecDeco.back());
		m_vecDeco.pop_back();
	}
}

void CLevel::TileChange()
{
	m_vecCollTile[m_iPickIndex]->byDrawID = m_byDrawID;
	m_vecCollTile[m_iPickIndex]->byOption = m_byOption;
}

void CLevel::InsertDeco()
{
	D3DXVECTOR3 vScroll = ToolMgr->GetScroll();
	float fZoom = ToolMgr->GetZoom();

	DECO* pDeco = new DECO;
	pDeco->wstrObjKey = m_pItem->wstrObjKey;
	pDeco->wstrStateKey = m_pItem->wstrStateKey;
	pDeco->iCount = m_pItem->iCount;
	pDeco->vPosition = GetMousePos();

	m_vecDeco.push_back(pDeco);
}
