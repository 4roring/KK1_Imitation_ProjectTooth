#pragma once
#include "DEffectBridge.h"
class DExplosionEffectBridge :
	public DEffectBridge
{
public:
	DExplosionEffectBridge();
	virtual ~DExplosionEffectBridge();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void FrameMove(float deltaTime);
	void UpdateRect();

private:
	ANIMFRAME m_tFrame = {};
	ANIMSCENE m_tScene = {};
	RECT m_tRect = {};
	int m_iImageCX = 0;
	int m_iImageCY = 0;
};

