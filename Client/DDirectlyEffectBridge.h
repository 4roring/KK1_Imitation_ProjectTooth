#pragma once
#include "DEffectBridge.h"
class DDirectlyEffectBridge :
	public DEffectBridge
{
public:
	DDirectlyEffectBridge();
	virtual ~DDirectlyEffectBridge();

	// DEffectBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fScale = 0.f;
	float m_fMaxScale = 0.f;
	Vector3 m_vImageCenter;
	RECT m_tRect;
};

