#include "stdafx.h"
#include "Deco.h"


CDeco::CDeco()
{
}


CDeco::~CDeco()
{
}

HRESULT CDeco::Initialize()
{
	m_eLayer = LAYER_OBJ;

	m_tInfo.vPosition *= fScreenZoom;

	return S_OK;
}

OBJSTATE CDeco::Update(float deltaTime)
{
	return STATE_PLAY;
}

void CDeco::LateUpdate()
{
	
}

void CDeco::Render()
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
		, &Vector3(float(m_pTexMain->tImageInfo.Width >> 1), m_pTexMain->tImageInfo.Height * 0.9f, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDeco::Release()
{
}
