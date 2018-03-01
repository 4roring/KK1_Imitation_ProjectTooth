#pragma once
#include "Actor.h"
class APlayer :
	public CActor
{
public:
	APlayer();
	virtual ~APlayer();

	// CActor��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	const TEXINFO* m_pTexOverlay;
};

