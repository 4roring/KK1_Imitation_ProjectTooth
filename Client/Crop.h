#pragma once
#include "GameObject.h"
class CCrop :
	public CGameObject
{
public:
	CCrop();
	virtual ~CCrop();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateRect();

private:
	RECT m_tRect = {};
	int m_iFrame = 0;
	int m_iImageCX = 0;
	int m_iImageCY = 0;
};

