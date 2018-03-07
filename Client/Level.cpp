#include "stdafx.h"
#include "Level.h"

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

	return S_OK;
}

OBJSTATE CLevel::Update(float deltaTime)
{

	return STATE_PLAY;
}

void CLevel::LateUpdate()
{
}

void CLevel::Render()
{
	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale);
	

	// 스크롤을 적용하는 맵 랜더

	// 조건에 따라 타일 랜더
}

void CLevel::Release()
{
	std::for_each(m_vecCollTile.begin(), m_vecCollTile.end(), SafeDelete<COLLTILE*>);
	VECCOLLTILE vecTile;
	m_vecCollTile.swap(vecTile);
}

bool CLevel::isCulling(const D3DXVECTOR3& vPos)
{
	/*if (vPos.x < 0.f + (vScroll.x + 50.f)) return true;
	if (vPos.y < 0.f + (vScroll.y + 50.f)) return true;
	if (vPos.x > WINCX + (vScroll.x - 50.f)) return true;
	if (vPos.y > WINCY + (vScroll.y - 50.f)) return true;*/

	return false;
}

void CLevel::MapRender(D3DXVECTOR3& vScroll)
{
	D3DXMATRIX matTrans;
	const TEXINFO* pTexture = TextureMgr->GetTexture(TEXT("Map03"));

	D3DXMatrixTranslation(&matTrans
		, 0.f - vScroll.x
		, 0.f - vScroll.y
		, 0.f);

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexture->pTexture
		, nullptr, nullptr, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLevel::CollTileRender(D3DXVECTOR3& vScroll)
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

			//D3DXMatrixTranslation(&matTrans
			//	, m_vecCollTile[iIndex]->vPosition.x * fZoom
			//	, m_vecCollTile[iIndex]->vPosition.y * fZoom
			//	, 0.f);

			//matWorld = matScale * matTrans;

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
	
}