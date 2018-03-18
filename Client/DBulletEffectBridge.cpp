#include "stdafx.h"
#include "DBulletEffectBridge.h"
#include "Effect.h"

DBulletEffectBridge::DBulletEffectBridge()
{
}


DBulletEffectBridge::~DBulletEffectBridge()
{
}

HRESULT DBulletEffectBridge::Initialize()
{
	SetMainTexture();

	if (nullptr == m_pEffect)
		return E_FAIL;

	if (nullptr == m_pTarget)
		return E_FAIL;

	Vector3 vDir;
	
	vDir = m_pTarget->vPosition - m_pEffect->m_tInfo.vPosition;
	
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&m_pEffect->m_tInfo.vLook, &m_pEffect->m_tInfo.vLook);

	float fCos = D3DXVec3Dot(&m_pEffect->m_tInfo.vLook, &vDir);
	
	m_fAngle = acosf(fCos);

	if (m_pTarget->vPosition.y < m_pEffect->m_tInfo.vPosition.y)
		m_fAngle *= -1.f;

	m_pEffect->m_tInfo.vDir = vDir;
	m_pEffect->m_fSpeed = 500.f;
	
	return S_OK;
}

OBJSTATE DBulletEffectBridge::Update(float deltaTime)
{
	if (D3DXVec3Length(&(m_pEffect->m_tInfo.vPosition - m_pTarget->vPosition)) <= 5.f)
		return STATE_DESTROY;

	m_pEffect->m_tInfo.vPosition += m_pEffect->m_tInfo.vDir * m_pEffect->m_fSpeed * deltaTime;

	return STATE_PLAY;
}

void DBulletEffectBridge::LateUpdate()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	Vector3 vScroll = ViewMgr->GetScroll();
	Vector3 vPos = m_pEffect->m_tInfo.vPosition + vScroll;

	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, 0.f);

	m_pEffect->m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

void DBulletEffectBridge::Render()
{
	const D3DXIMAGE_INFO& tTexMainInfo = m_pEffect->m_pTexMain->tImageInfo;

	m_pSprite->SetTransform(&m_pEffect->m_tInfo.matWorld);
	m_pSprite->Draw(m_pEffect->m_pTexMain->pTexture
		, nullptr
		, &Vector3(float(tTexMainInfo.Width >> 1), float(tTexMainInfo.Height >> 1), 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (nullptr != m_pTexTracer)
	{
		m_pSprite->Draw(m_pTexTracer->pTexture
			, nullptr
			, &Vector3(float(m_pTexTracer->tImageInfo.Width * 0.9f), float(m_pTexTracer->tImageInfo.Height >> 1), 0.f)
			, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void DBulletEffectBridge::Release()
{
}

void DBulletEffectBridge::SetMainTexture()
{
	switch (m_eBulletID)
	{
	case BULLET_ARTILLERY:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_artillery"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_artillery"));
		break;
	case BULLET_GRENADE:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_artillery"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_artillery"));
		break;
	case BULLET_MEDKIT:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_artillery"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_artillery"));
		break;
	case BULLET_PISTOL:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_pistol"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_pistol"));
		break;
	case BULLET_SNIPER:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_artillery"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_artillery"));
		break;
	case BULLET_VENOM:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("bullet_artillery"));
		m_pTexTracer = TextureMgr->GetTexture(TEXT("tracer_artillery"));
		break;
	case BULLET_SPEAR:
		m_pEffect->m_pTexMain = TextureMgr->GetTexture(TEXT("thrownspear"));
		m_pTexTracer = nullptr;
		break;
	case BULLET_END:
	default:
#ifdef _DEBUG
		assert(!"Bullet Effect Initialize Error (END or default)");
#endif
		break;
	}
}
