#include "stdafx.h"
#include "DAICommand.h"
#include "ACommander.h"
#include "AStar.h"

DAICommand::DAICommand()
{
}


DAICommand::~DAICommand()
{
}

void DAICommand::Update()
{
	FSM();
}

void DAICommand::FSM()
{
	m_pACommander->m_bBuild = true;
}
