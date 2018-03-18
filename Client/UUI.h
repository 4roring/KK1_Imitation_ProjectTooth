#pragma once

#include "GameObject.h"

class DObserver;
class UUI
	: public CGameObject
{
public:
	UUI();
	virtual ~UUI();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() override;

protected:
	void UpdateMatrix();

protected:
	DObserver* m_pObserver = nullptr;
};

