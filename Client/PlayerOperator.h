#pragma once
#include "Operator.h"
class CPlayerOperator :
	public COperator
{
public:
	CPlayerOperator();
	virtual ~CPlayerOperator();

	// COperator��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	void Input();
};

