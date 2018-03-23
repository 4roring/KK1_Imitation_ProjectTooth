#include "stdafx.h"
#include "DDirectlyEffectBridge.h"
#include "Effect.h"

DDirectlyEffectBridge::DDirectlyEffectBridge()
{
}


DDirectlyEffectBridge::~DDirectlyEffectBridge()
{
}

HRESULT DDirectlyEffectBridge::Initialize()
{
	m_pTexMain = TextureMgr->GetTexture(TEXT("particles"), TEXT("burst1"));
	m_tRect = *m_pTexMain->pRect;
	m_fMaxScale = 3.f;
	m_fScale = m_fMaxScale;

	m_vImageCenter.x = (m_tRect.right - m_tRect.left) * 0.5f;
	m_vImageCenter.y = (m_tRect.bottom - m_tRect.top) * 0.5f;
	m_vImageCenter.z = 0.f;

	return S_OK;
}

OBJSTATE DDirectlyEffectBridge::Update(float deltaTime)
{	
	m_fScale -= m_fMaxScale * 1.5f * deltaTime;

	if (m_fScale <= 0.3f)
		m_fScale = m_fMaxScale;

	return STATE_PLAY;
}

void DDirectlyEffectBridge::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;

	Vector3 vScroll = ViewMgr->GetScroll();
	Vector3 vPos = m_pEffect->m_tInfo.vPosition + vScroll;

	D3DXMatrixScaling(&matScale, fScreenZoom * m_fScale, fScreenZoom * m_fScale, 1.f);

	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, 0.f);

	m_pEffect->m_tInfo.matWorld = matScale * matTrans;
}

void DDirectlyEffectBridge::Render()
{
	m_pSprite->SetTransform(&m_pEffect->m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &m_vImageCenter
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 0));
}

void DDirectlyEffectBridge::Release()
{
}
