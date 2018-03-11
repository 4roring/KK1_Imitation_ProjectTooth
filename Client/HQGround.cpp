#include "stdafx.h"
#include "HQGround.h"

CHQGround::CHQGround()
{
}


CHQGround::~CHQGround()
{
	Release();
}

HRESULT CHQGround::Initialize()
{
	m_eLayer = LAYER_BACK;
	m_pTexMain = TextureMgr->GetTexture(TEXT("windmill_bib_forest"));

	return S_OK;
}

OBJSTATE CHQGround::Update(float deltaTime)
{
	if (m_bDestroy)
	{

		return STATE_DESTROY;
	}

	return STATE_PLAY;
}

void CHQGround::LateUpdate()
{
}

void CHQGround::Render()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);
	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x
		, m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, nullptr
		, &Vector3(float(m_pTexMain->tImageInfo.Width >> 1), float(m_pTexMain->tImageInfo.Height >> 1), 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CHQGround::Release()
{
}


