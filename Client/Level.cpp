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
	
	m_pTexMain = TextureMgr->GetTexture(TEXT("Map"), TEXT("Map"), 0);

	ViewMgr->SetMaxScroll(Vector3(
		m_pTexMain->tImageInfo.Width * fScreenZoom - WINCX
		, m_pTexMain->tImageInfo.Height* fScreenZoom - WINCY
		, 0.f));

	m_vecCollTile.reserve(COLLTILEX * COLLTILEY);

	LoadCollTile();

	return S_OK;
}

OBJSTATE CLevel::Update(float deltaTime)
{
	if (GetKey->KeyDown('Z'))
		m_bTileRender = !m_bTileRender;

	return STATE_PLAY;
}

void CLevel::LateUpdate()
{
}

void CLevel::Render()
{
	Vector3 vScroll = ViewMgr->GetScroll();
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);

	// 스크롤을 적용하는 맵 랜더
	MapRender(vScroll, matScale);

	// 조건에 따라 타일 랜더
	if (true == m_bTileRender)
		CollTileRender(vScroll, matScale);
}

void CLevel::Release()
{
	std::for_each(m_vecCollTile.begin(), m_vecCollTile.end(), SafeDelete<COLLTILE*>);
	VECCOLLTILE vecTile;
	m_vecCollTile.swap(vecTile);
}

bool CLevel::isCulling(const Vector3& vPos)
{
	if (vPos.x < 50.f) return true;
	if (vPos.y < 50.f) return true;
	if (vPos.x > WINCX - 50.f) return true;
	if (vPos.y > WINCY - 50.f) return true;

	return false;
}

void CLevel::MapRender(Vector3& vScroll, D3DXMATRIX& matScale)
{
	D3DXMATRIX matTrans;
	const TEXINFO* pTexture = TextureMgr->GetTexture(TEXT("Map03"));

	D3DXMatrixTranslation(&matTrans
		, 0.f + vScroll.x 
		, 0.f + vScroll.y 
		, 0.f);
	
	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);

	m_pSprite->Draw(m_pTexMain->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLevel::CollTileRender(Vector3& vScroll, D3DXMATRIX& matScale)
{
	D3DXMATRIX matWorld, matTrans;
	const TEXINFO* pTexture = nullptr;
	TCHAR szBuf[128] = L"";

	for (int y = 0; y < COLLTILEY; ++y)
	{
		for (int x = 0; x < COLLTILEX; ++x)
		{
			int iIndex = y * COLLTILEX + x;

			Vector3 vTempTilePos = m_vecCollTile[iIndex]->vPosition + vScroll;

			if (isCulling(vTempTilePos))
				continue;

			pTexture = TextureMgr->GetInstance()->GetTexture(
				TEXT("Map"), TEXT("Tile"), m_vecCollTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, vTempTilePos.x
				, vTempTilePos.y 
				, 0.f);

			matWorld = matScale * matTrans;

			m_pSprite->SetTransform(&matWorld);

			D3DCOLOR color = (iIndex == m_iPickIndex) ?
				D3DCOLOR_ARGB(255, 255, 0, 0) : D3DCOLOR_ARGB(255, 255, 255, 255);

			color = (m_vecCollTile[iIndex]->pObj != nullptr) ?
				D3DCOLOR_ARGB(255, 0, 255, 0) : D3DCOLOR_ARGB(255, 255, 255, 255);

			m_pSprite->Draw(pTexture->pTexture
				, nullptr
				, &Vector3(COLLTILECX * 0.5f, COLLTILECY * 0.5f, 0.f)
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

int CLevel::GetTileIndex(Vector3 vPos)
{
	float CX = COLLTILECX * fScreenZoom;
	float CY = COLLTILECY * fScreenZoom;

	int iPickIdx = (int)(vPos.x / CX) + COLLTILEX + (COLLTILEX * 2) * (int)(vPos.y / CY);

	if (iPickIdx < 0 || iPickIdx >= COLLTILEX * COLLTILEY - 1)
		return -1;

	Vector3 vTemp = m_vecCollTile[iPickIdx]->vPosition * fScreenZoom;

	Vector3 vPoint[4] =
	{
		{ vTemp.x - CX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x, vTemp.y - CY * 0.5f, 0.f },
		{ vTemp.x + CX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x , vTemp.y + CY * 0.5f, 0.f }
	};

	float fGradient = (CY * 0.5f) / (CX * 0.5f);

	float fB[4];

	for (int i = 0; i < 4; ++i)
	{

		fB[i] = (i & 1) ? -fGradient : fGradient;
		fB[i] = fB[i] * vPoint[i].x + vPoint[i].y;
	}

	if (vPos.y + fGradient * vPos.x - fB[0] <= 0.f) return iPickIdx - COLLTILEX;
	if (vPos.y - fGradient * vPos.x - fB[1] < 0.f) return iPickIdx - (COLLTILEX - 1);
	if (vPos.y + fGradient * vPos.x - fB[2] > 0.f) return iPickIdx + (COLLTILEX + 1);
	if (vPos.y - fGradient * vPos.x - fB[3] > 0.f) return iPickIdx + COLLTILEX;

	return iPickIdx;
}

void CLevel::Picking()
{
	
}

void CLevel::LoadCollTile()
{
	HANDLE hFile = CreateFile(TEXT("../Data/CollTileData.dat"),
		GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	while (true)
	{
		COLLTILE* pCollTile = new COLLTILE;
		ReadFile(hFile, pCollTile, sizeof(COLLTILE), &dwByte, nullptr);

		if (dwByte <= 0)
		{
			SafeDelete(pCollTile);
			break;
		}
		pCollTile->vPosition *= fScreenZoom;
		pCollTile->pObj = nullptr;
		m_vecCollTile.push_back(pCollTile);
	}
	
	CloseHandle(hFile);
}