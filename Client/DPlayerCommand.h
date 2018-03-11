#pragma once
#include "DCommand.h"
class DPlayerCommand :
	public DCommand
{
public:
	DPlayerCommand();
	virtual ~DPlayerCommand();

	// COperator을(를) 통해 상속됨
	virtual void Update() override;

private:
	void Input();
};

