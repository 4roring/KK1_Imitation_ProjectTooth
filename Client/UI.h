#pragma once
#include "GameObject.h"
class CUI :
	public CGameObject
{
public:
	CUI();
	virtual ~CUI();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

};

