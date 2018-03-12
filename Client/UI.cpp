#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
}


CUI::~CUI()
{
}

HRESULT CUI::Initialize()
{
	m_eLayer = LAYER_UI;
	m_pTexMain = TextureMgr->GetTexture(TEXT("ui"), TEXT("foodmap_woodbg"));
	m_tInfo.vPosition = Vector3(0.f, 674.f, 0.f);

	return S_OK;
}

OBJSTATE CUI::Update(float deltaTime)
{
	return OBJSTATE();
}

void CUI::LateUpdate()
{
}

void CUI::Render()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x 
		, m_tInfo.vPosition.y 
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pTexMain->tRect
		, nullptr
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI::Release()
{
}
