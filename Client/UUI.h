#pragma once

#include "GameObject.h"

class DObserver;
class UUI
	: public CGameObject
{
public:
	UUI();
	virtual ~UUI();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() override;

public:
	void SetTarget(CGameObject* pTarget) { m_pTarget = pTarget; }

protected:
	void UpdateMatrixScreenUI();
	void UpdateMatrixWorldUI(float fDiameter);
protected:
	DObserver* m_pObserver = nullptr;
	CGameObject* m_pTarget = nullptr;
};

