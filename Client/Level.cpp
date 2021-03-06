#include "stdafx.h"
#include "Level.h"
#include "NeutralHQ.h"
#include "HQGround.h"
#include "BFarm.h"
#include "BHQ.h"

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

	m_pTexMain = TextureMgr->GetTexture(TEXT("Map"), TEXT("Map"), 0);

	ViewMgr->SetMaxScroll(Vector3(
		m_pTexMain->tImageInfo.Width * fScreenZoom - WINCX
		, m_pTexMain->tImageInfo.Height* fScreenZoom - WINCY
		, 0.f));

	m_vecCollTile.reserve(COLLTILEX * COLLTILEY);
	
	LoadCollTile();
	CreateBuilding();
	return S_OK;
}

OBJSTATE CLevel::Update(float deltaTime)
{
	if (KeyMgr->KeyDown('Z'))
		m_bTileRender = !m_bTileRender;

	return STATE_PLAY;
}

void CLevel::LateUpdate()
{
}

void CLevel::Render()
{
	const Vector3& vScroll = ViewMgr->GetScroll();
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);
	
	MapRender(vScroll, matScale);
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

void CLevel::MapRender(const Vector3& vScroll, const D3DXMATRIX& matScale)
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans
		, 0.f + vScroll.x 
		, 0.f + vScroll.y 
		, 0.f);
	
	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLevel::CollTileRender(const Vector3& vScroll, const D3DXMATRIX& matScale)
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
			D3DCOLOR color = (nullptr != m_vecCollTile[iIndex]->pGameObject) ?
				D3DCOLOR_ARGB(255, 0, 255, 0) : D3DCOLOR_ARGB(255, 255, 255, 255);

			m_pSprite->SetTransform(&matWorld);
			m_pSprite->Draw(pTexture->pTexture
				, nullptr
				, &Vector3(COLLTILECX * 0.5f, COLLTILECY * 0.5f, 0.f)
				, nullptr
				, color);
			m_pSprite->SetTransform(&matTrans);

			swprintf_s(szBuf, TEXT("%d"), iIndex);
			m_pFont->DrawTextW(m_pSprite, szBuf, lstrlen(szBuf)
				, nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

int CLevel::GetTileIndex(const Vector3& vPos)
{
	constexpr float fCX = COLLTILECX * fScreenZoom;
	constexpr float fCY = COLLTILECY * fScreenZoom;

	const int iPickIdx = (int)(vPos.x / fCX) + COLLTILEX + (COLLTILEX * 2) * (int)(vPos.y / fCY);

	if (iPickIdx < 0 || iPickIdx >= COLLTILEX * COLLTILEY - 1)
		return -1;

	const Vector3& vTemp = m_vecCollTile[iPickIdx]->vPosition;

	const Vector3 vPoint[4] =
	{
		{ vTemp.x - fCX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x, vTemp.y - fCY * 0.5f, 0.f },
		{ vTemp.x + fCX * 0.5f, vTemp.y, 0.f },
		{ vTemp.x , vTemp.y + fCY * 0.5f, 0.f }
	};

	constexpr float fGradient = 1;

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

// 이웃한 8개의 타일 범위
void CLevel::GetRange(VECCOLLTILE & rVecRange, int iStart)
{
	rVecRange.clear();

	for (int i = 0; i < NEIGHBOR_END; ++i)
	{
		const int iTemp = GetNeighborTileIndex(i, iStart);
		if (iTemp < 0 || iTemp >= COLLTILEX * COLLTILEY - 1)
			continue;
		rVecRange.emplace_back(m_vecCollTile[iTemp]);
	}
}

// 규칙성이 있는 타일 범위
void CLevel::GetRange(VECCOLLTILE & rVecRange, int iStart, int iRange)
{
	rVecRange.clear();

	// 체크를 시작하는 타일
	int iRangeStart = iStart;

	iRangeStart = GetNeighborTileIndex(NEIGHBOR_LEFTUP, iRangeStart, iRange);

	for (int y = 0; y <= iRange * 2; ++y)
	{
		for (int x = 0; x <= iRange; ++x)
		{
			int iIndex = y * COLLTILEX + (x + iRangeStart);
			int iException = (iRange & 1) ? iRange : 0;

			if ((y & 1) && x == iException) continue;
				
			if (iIndex < 0 || iIndex >= COLLTILEX * COLLTILEY - 1)
				continue;

			rVecRange.emplace_back(m_vecCollTile[iIndex]);
		}
	}
}

// iNeighbor Index
// 0. Left, 1. Left Up 2. Left Down
// 3. Right, 4. Right Up, 5. Right Down
// 6. Up, 7. Down
int CLevel::GetNeighborTileIndex(int iNeighbor, int iStart)
{
	int iOddEven = 0;

	switch (iNeighbor)
	{
	case NEIGHBOR_LEFT: 
		return iStart - 1;
	case NEIGHBOR_LEFTUP:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 0 : 1;
		return iStart -= (COLLTILEX + iOddEven);
	case NEIGHBOR_LEFTDOWN:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 0 : 1;
		return iStart += (COLLTILEX - iOddEven);
	
	case NEIGHBOR_RIGHT: 
		return  iStart + 1;
	case NEIGHBOR_RIGHTUP:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 1 : 0;
		return iStart -= (COLLTILEX - iOddEven);
	case NEIGHBOR_RIGHTDOWN:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 1 : 0;
		return iStart += (COLLTILEX + iOddEven);

	case NEIGHBOR_UP: 
		return iStart - (COLLTILEX * 2);
	case NEIGHBOR_DOWN: 
		return iStart + (COLLTILEX * 2);
	}

	return -1;
}

int CLevel::GetNeighborTileIndex(int iNeighbor, int iStart, int iDepth)
{
	if (iDepth == 0)
		return iStart;

	int iOddEven = 0;
	int iTemp = 0;

	switch (iNeighbor)
	{
	case NEIGHBOR_LEFT: 
		return iStart - (1 * iDepth);
	case NEIGHBOR_LEFTUP:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 0 : 1;
		iTemp = iStart -= (COLLTILEX + iOddEven);
		return GetNeighborTileIndex(iNeighbor, iTemp, --iDepth);
	case NEIGHBOR_LEFTDOWN:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 0 : 1;
		iTemp = iStart += (COLLTILEX - iOddEven);
		return GetNeighborTileIndex(iNeighbor, iTemp, --iDepth);

	case NEIGHBOR_RIGHT: 
		return  iStart + (1 * iDepth);
	case NEIGHBOR_RIGHTUP:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 1 : 0;
		iTemp = iStart -= (COLLTILEX - iOddEven);
		return GetNeighborTileIndex(iNeighbor, iTemp, --iDepth);
	case NEIGHBOR_RIGHTDOWN:
		iOddEven = ((iStart / COLLTILEX) & 1) ? 1 : 0;
		iTemp = iStart += (COLLTILEX + iOddEven);
		return GetNeighborTileIndex(iNeighbor, iTemp, --iDepth);

	case NEIGHBOR_UP: 
		return iStart - (COLLTILEX * 2) * iDepth;
	case NEIGHBOR_DOWN: 
		return iStart + (COLLTILEX * 2) * iDepth;
	}

	return -1;
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
		pCollTile->pGameObject = nullptr;
		m_vecCollTile.emplace_back(pCollTile);
	}

	CloseHandle(hFile);
}

void CLevel::CreateBuilding()
{
	Vector3 GroundPos;
	CGameObject* pObject = nullptr;

	for (size_t i = 0; i < m_vecCollTile.size(); ++i)
	{
		switch (m_vecCollTile[i]->byOption)
		{
		case 2: // 중립 HQ 생성
			pObject = DObjectFactory<CNeutralHQ>::Create(m_vecCollTile[i]->vPosition);
			static_cast<CNeutralHQ*>(pObject)->SetTileIndexArray(i);
			GameMgr->CreateObject(pObject, OBJ_HQ);

			CreateNeutralFarm(i);

			GroundPos = Vector3(m_vecCollTile[i]->vPosition.x, m_vecCollTile[i]->vPosition.y - COLLTILECY, 0.f);
			GameMgr->CreateObject(DObjectFactory<CHQGround>::Create(GroundPos), OBJ_BACK);
			break;

		case 3: // Red팀 HQ 생성
			GroundPos = Vector3(m_vecCollTile[i]->vPosition.x, m_vecCollTile[i]->vPosition.y - COLLTILECY, 0.f);
			GameMgr->CreateObject(DObjectFactory<CHQGround>::Create(GroundPos), OBJ_BACK);
			CreateTeamHQ(GetTileIndex(m_vecCollTile[i]->vPosition), TEAM_RED);
			break;

		case 4: // Blue팀 HQ 생성
			GroundPos = Vector3(m_vecCollTile[i]->vPosition.x, m_vecCollTile[i]->vPosition.y - COLLTILECY, 0.f);
			GameMgr->CreateObject(DObjectFactory<CHQGround>::Create(GroundPos), OBJ_BACK);
			CreateTeamHQ(GetTileIndex(m_vecCollTile[i]->vPosition), TEAM_BLUE);
			break;

		case 5: // Green팀 HQ 생성
			GroundPos = Vector3(m_vecCollTile[i]->vPosition.x, m_vecCollTile[i]->vPosition.y - COLLTILECY, 0.f);
			GameMgr->CreateObject(DObjectFactory<CHQGround>::Create(GroundPos), OBJ_BACK);
			CreateTeamHQ(GetTileIndex(m_vecCollTile[i]->vPosition), TEAM_GREEN);
			break;

		case 6: // Yello팀 HQ 생성
			GroundPos = Vector3(m_vecCollTile[i]->vPosition.x, m_vecCollTile[i]->vPosition.y - COLLTILECY, 0.f);
			GameMgr->CreateObject(DObjectFactory<CHQGround>::Create(GroundPos), OBJ_BACK);
			CreateTeamHQ(GetTileIndex(m_vecCollTile[i]->vPosition), TEAM_YELLO);
			break;
		}
	}
}

void CLevel::CreateFarm(int iTileIndex, TEAMID eTeamID)
{
	CGameObject* pObject = DObjectFactory<BFarm>::CreateBuilding(iTileIndex, eTeamID);
	GameMgr->CreateObject(pObject, OBJ_FARM);
}

void CLevel::CreateFinishedFarm(int iTileIndex, TEAMID eTeamID)
{
	CGameObject* pObject = DObjectFactory<BFarm>::CreateBuilding(iTileIndex, eTeamID);
	dynamic_cast<BFarm*>(pObject)->SetFarmState(2);
	GameMgr->CreateObject(pObject, OBJ_FARM);
}

void CLevel::CreateNeutralFarm(int iTileIndex)
{
	for (int i = 0; i < NEIGHBOR_END; ++i)
		CreateFarm(GetNeighborTileIndex(i, iTileIndex, 2), TEAM_NEUTRAL);
}

void CLevel::CreateTeamStartFarm(int iTileIndex, TEAMID eTeamID)
{
	for (int i = 0; i <= NEIGHBOR_UP; ++i) 
		CreateFinishedFarm(GetNeighborTileIndex(i, iTileIndex, 2), eTeamID);

	for (int i = NEIGHBOR_UP + 1; i < NEIGHBOR_END; ++i)
		CreateFarm(GetNeighborTileIndex(i, iTileIndex, 2), eTeamID);
}

void CLevel::CreateTeamHQ(int iTileIndex, TEAMID eTeamID)
{
	CGameObject* pObject = DObjectFactory<BHQ>::CreateBuilding(iTileIndex, eTeamID);
	dynamic_cast<BHQ*>(pObject)->SetHQState(1);
	GameMgr->CreateObject(pObject, OBJ_HQ);

	CreateTeamStartFarm(iTileIndex, eTeamID);
}
