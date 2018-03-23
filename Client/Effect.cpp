#include "stdafx.h"
#include "Effect.h"
#include "DBulletEffectBridge.h"
#include "DExplosionEffectBridge.h"
#include "DDirectlyEffectBridge.h"

CEffect::CEffect()
{
	m_pSprite = Device->GetSprite();
}


CEffect::~CEffect()
{
	Release();
}

HRESULT CEffect::Initialize()
{
	m_eLayer = LAYER_EFFECT;

	if (nullptr == m_pEffectBridge)
		return E_FAIL;
		
	m_pEffectBridge->SetEffect(this);
	m_pEffectBridge->Initialize();

	return S_OK;
}

OBJSTATE CEffect::Update(float deltaTime)
{
	OBJSTATE eEvent = m_pEffectBridge->Update(deltaTime);

	if (true == m_bDestroy)
		return STATE_DESTROY;

	if (eEvent == STATE_DESTROY)
		return STATE_DESTROY;

	return STATE_PLAY;
}

void CEffect::LateUpdate()
{
	m_pEffectBridge->LateUpdate();
}

void CEffect::Render()
{
	m_pEffectBridge->Render();
}

void CEffect::Release()
{
	SafeDelete(m_pEffectBridge);
}
