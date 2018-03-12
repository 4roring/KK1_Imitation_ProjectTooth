#pragma once
#include "GameObject.h"
class CUI :
	public CGameObject
{
public:
	CUI();
	virtual ~CUI();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

};

