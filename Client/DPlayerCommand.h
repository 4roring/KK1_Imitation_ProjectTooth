#pragma once
#include "DCommand.h"
class DPlayerCommand :
	public DCommand
{
public:
	DPlayerCommand();
	virtual ~DPlayerCommand();

	// COperator��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	void Input();
};

