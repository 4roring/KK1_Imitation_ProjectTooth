#pragma once
#include "GameObject.h"
class CNeutralHQ :
	public CGameObject
{
public:
	CNeutralHQ();
	virtual ~CNeutralHQ();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetTileIndexArray(int iStart);

private:
	int m_iTileIndexArr[4] = {};
};

