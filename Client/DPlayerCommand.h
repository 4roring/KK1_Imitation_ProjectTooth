#pragma once
#include "DCommand.h"
class DPlayerCommand :
	public DCommand
{
public:
	DPlayerCommand();
	virtual ~DPlayerCommand();

public:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	void Input();
};

