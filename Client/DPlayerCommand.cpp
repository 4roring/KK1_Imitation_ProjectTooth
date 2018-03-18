#include "stdafx.h"
#include "DPlayerCommand.h"
#include "ACommander.h"
#include "DSubject.h"
#include "DSubject.h"

DPlayerCommand::DPlayerCommand()
{
}


DPlayerCommand::~DPlayerCommand()
{
}

void DPlayerCommand::Update()
{
	Input();
}

void DPlayerCommand::Input()
{
	if (GetKey->KeyPress('A'))
		m_pACommander->m_tInfo.vDir.x = -1.f;
	else if (GetKey->KeyPress('D'))
		m_pACommander->m_tInfo.vDir.x = 1.f;
	else
		m_pACommander->m_tInfo.vDir.x = 0.f;

	if (GetKey->KeyPress('W'))
		m_pACommander->m_tInfo.vDir.y = -1.f;
	else if (GetKey->KeyPress('S'))
		m_pACommander->m_tInfo.vDir.y = 1.f;
	else
		m_pACommander->m_tInfo.vDir.y = 0.f;

	if (GetKey->KeyPress(VK_LBUTTON))
		m_pACommander->m_fOrder += Time->GetDeltaTime();
	else if (GetKey->KeyPress(VK_RBUTTON))
	{
		m_pACommander->m_fOrder += Time->GetDeltaTime();
		m_pACommander->m_bAllOrder = true;
	}
	else
	{
		m_pACommander->m_fOrder = 0.f;
		m_pACommander->m_bAllOrder = false;
	}

	if (GetKey->KeyDown(VK_SPACE))
		m_pACommander->m_bBuild = true;

	if (GetKey->KeyDown('Q'))
	{
		if (--m_pACommander->m_iSelectSlot < 0)
			m_pACommander->m_iSelectSlot = SLOT_MAX - 1;

		GameMgr->GetSubject(m_pACommander->m_eTeam)->NotifySlotNum(m_pACommander->m_iSelectSlot);
	}

	if (GetKey->KeyDown('E'))
	{
		if (++m_pACommander->m_iSelectSlot >= SLOT_MAX)
			m_pACommander->m_iSelectSlot = 0;

		GameMgr->GetSubject(m_pACommander->m_eTeam)->NotifySlotNum(m_pACommander->m_iSelectSlot);
	}	
}
