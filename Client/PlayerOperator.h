#pragma once
#include "Operator.h"
class CPlayerOperator :
	public COperator
{
public:
	CPlayerOperator();
	virtual ~CPlayerOperator();

	// COperator을(를) 통해 상속됨
	virtual void Update() override;

private:
	void Input();
};

