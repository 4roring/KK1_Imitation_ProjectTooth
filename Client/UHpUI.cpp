#include "stdafx.h"
#include "UHpUI.h"


UHpUI::UHpUI()
{
}


UHpUI::~UHpUI()
{
	Release();
}

HRESULT UHpUI::Initialize()
{
	m_eLayer = LAYER_WORLDUI;

	m_pTexMain = TextureMgr->GetTexture(TEXT("ui"), TEXT("healthgauge_factory_bg"));
	m_pHpBg = m_pTexMain->pRect;
	m_tHpFill = *TextureMgr->GetTexture(TEXT("ui"), TEXT("healthgauge_factory_fill"))->pRect;

	m_iHpFillHeight = m_tHpFill.bottom - m_tHpFill.top;

	return S_OK;
}

OBJSTATE UHpUI::Update(float deltaTime)
{
	if (m_bDestroy)
		return STATE_DESTROY;

	m_tInfo.vPosition = m_pTarget->GetInfo().vPosition + Vector3(0.f, -1.f, 0.f) * 50.f;

	return STATE_PLAY;
}

void UHpUI::LateUpdate()
{
	SetFillRatio();
	UpdateMatrixWorldUI(0.5f);
}

void UHpUI::Render()
{
	if (m_pTarget->GetHpRatio() < 1.f)
	{
		HpBackgroundRender();
		HpFillRender();
	}
}

void UHpUI::Release()
{
}

void UHpUI::SetFillRatio()
{
	float fRatio = m_iHpFillHeight * m_pTarget->GetHpRatio();
	m_tHpFill.top = m_tHpFill.bottom - (LONG)fRatio;
}

void UHpUI::HpBackgroundRender()
{
	const int iWidth = m_pHpBg->right - m_pHpBg->left;
	const int iHeight = m_pHpBg->bottom - m_pHpBg->top;
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pHpBg
		, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void UHpUI::HpFillRender()
{
	const int iWidth = m_tHpFill.right - m_tHpFill.left;
	const int iHeight = m_tHpFill.bottom - m_tHpFill.top;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tHpFill
		, &Vector3(float(iWidth >> 1), float(iHeight - (m_iHpFillHeight >> 1)), 0.f)
		, nullptr
		, D3DCOLOR_ARGB(200, 255, 0, 0));
}
