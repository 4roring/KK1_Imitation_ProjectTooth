#pragma once
#include "DEffectBridge.h"
class DTimerEffectBridge :
	public DEffectBridge
{
public:
	DTimerEffectBridge();
	virtual ~DTimerEffectBridge();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	LPRECT m_pFrameArr[3];
};

