#pragma once
#include "DEffectBridge.h"
class DBulletEffectBridge :
	public DEffectBridge
{
public:
	DBulletEffectBridge();
	virtual ~DBulletEffectBridge();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void SetMainTexture();

private:
	bool CollisionTarget();

private:
	float m_fAngle = 0.f;
	const TEXINFO* m_pTexTracer = nullptr;
};

