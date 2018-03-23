#include "stdafx.h"
#include "UMiniMap.h"


UMiniMap::UMiniMap()
{
}


UMiniMap::~UMiniMap()
{
	Release();
}

HRESULT UMiniMap::Initialize()
{
	m_eLayer = LAYER_UI;

	m_pTexMain = TextureMgr->GetTexture(TEXT("Map"), TEXT("Map"), 1);
	m_pTexMini = TextureMgr->GetTexture(TEXT("Map"), TEXT("Map"), 2);
	m_tInfo.vPosition = { 0.f , 580.f, 0.f };

	return S_OK;
}

OBJSTATE UMiniMap::Update(float deltaTime)
{
	return STATE_PLAY;
}

void UMiniMap::LateUpdate()
{
	// TODO: 미니맵 정보 업데이트.
	UpdateMiniMap();
}

void UMiniMap::Render()
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, 0.8f, 0.8f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPosition.x, m_tInfo.vPosition.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture, nullptr, nullptr, nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->Draw(m_pTexMini->pTexture, nullptr, nullptr, nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void UMiniMap::Release()
{
}

void UMiniMap::UpdateMiniMap()
{
	D3DLOCKED_RECT LockRect;

	m_pTexMini->pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits;

	for (int y = 0; y < MINIMAP_CXY; ++y)
	{
		for (int x = 0; x < MINIMAP_CXY; ++x)
		{
			int iIndex = y * MINIMAP_CXY + x;
			D3DXCOLOR color = pColor[iIndex];
			if (color.a > 0.f)
			{
				color.a = 0.f;
				pColor[iIndex] = color;
			}
		}
	}
		
	MiniRender(OBJ_HQ, pColor, 5);
	MiniRender(OBJ_PLAYER, pColor, 3);
	MiniRender(OBJ_AI, pColor, 3);
	MiniRender(OBJ_UNITFACTORY, pColor, 2);
	MiniRender(OBJ_UNIT, pColor, 1);

	m_pTexMini->pTexture->UnlockRect(0);
}

void UMiniMap::MiniRender(OBJID eObject, DWORD * pColor, int iSize)
{
	for (auto& pObject : GameMgr->GetObjectList(eObject))
	{
		int iX = int(pObject->GetInfo().vPosition.x * 0.05f);
		int iY = int(pObject->GetInfo().vPosition.y * 0.05f);

		int iStart = iY * MINIMAP_CXY + iX;

		for (int y = -iSize; y < iSize; ++y)
		{
			for (int x = -iSize; x < iSize; ++x)
			{
				int iIndex = y * MINIMAP_CXY + x + iStart;
				D3DXCOLOR color;
				switch (pObject->GetTeamID())
				{
				case TEAM_RED:
					color.a = 1.f;
					color.r = 1.f;
					color.g = 0.f;
					color.b = 0.f;
					break;
				case TEAM_BLUE:
					color.a = 1.f;
					color.r = 0.f;
					color.g = 0.f;
					color.b = 1.f;
					break;
				case TEAM_GREEN:
					color.a = 1.f;
					color.r = 0.f;
					color.g = 1.f;
					color.b = 0.f;
					break;
				case TEAM_YELLO:
					color.a = 1.f;
					color.r = 1.f;
					color.g = 1.f;
					color.b = 0.f;
					break;
				case TEAM_NEUTRAL:
					color.a = 1.f;
					color.r = 0.8f;
					color.g = 0.8f;
					color.b = 0.8f;
					break;
				}

				if(0 <= iIndex && iIndex < MINIMAP_CXY * MINIMAP_CXY)
					pColor[iIndex] = color;
			}
		}
	}
}

