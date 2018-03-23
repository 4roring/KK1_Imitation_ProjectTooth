#pragma once
#include "GameObject.h"

class DEffectBridge;
class CEffect :
	public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetEffectBridge(DEffectBridge* pEffectBridge) { m_pEffectBridge = pEffectBridge; }

private:
	friend class DBulletEffectBridge;
	friend class DExplosionEffectBridge;
	friend class DDirectlyEffectBridge;
	DEffectBridge* m_pEffectBridge;

private:
	float m_fSpeed = 0.f;
};

