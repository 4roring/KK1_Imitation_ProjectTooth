#pragma once
#include "DCommand.h"
class DAICommand :
	public DCommand
{
public:
	DAICommand();
	virtual ~DAICommand();

public:
	virtual void Update() override;

private:
	void FSM();
};

