#include "stdafx.h"
#include "FoodUI.h"
#include "DObserver.h"

UFoodUI::UFoodUI()
{
}


UFoodUI::~UFoodUI()
{
}

HRESULT UFoodUI::Initialize()
{
	UUI::Initialize();
	m_tRect = TextureMgr->GetTexture(TEXT("ui"), TEXT("foodmap_woodbg"))->pRect;
	m_tInfo.vPosition = Vector3(0.f, 674.f, 0.f);
	m_pFoodFont = Device->GetFoodFont();

	return S_OK;
}

OBJSTATE UFoodUI::Update(float deltaTime)
{
	return STATE_PLAY;
}

void UFoodUI::LateUpdate()
{
	UpdateMatrix();
	m_iFood = m_pObserver->GetFood();
}

void UFoodUI::Render()
{
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_tRect
		, nullptr
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMATRIX matTrans;

	TCHAR szBuf[16] = {};
	swprintf_s(szBuf, TEXT("%d"), m_iFood);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + 195.f
		, m_tInfo.vPosition.y + 45.f
		, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pFoodFont->DrawTextW(m_pSprite, szBuf, lstrlen(szBuf), nullptr, 0,
		D3DCOLOR_ARGB(255, 189, 169, 130));
}

void UFoodUI::Release()
{
}
