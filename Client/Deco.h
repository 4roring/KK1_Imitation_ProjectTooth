#pragma once
#include "GameObject.h"
class CDeco :
	public CGameObject
{
public:
	CDeco();
	virtual ~CDeco();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

