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
	void PlayOrderSound();

private:
	bool m_bOrderSound = false;
};

