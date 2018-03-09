#include "stdafx.h"
#include "PlayerOperator.h"
#include "ACommander.h"

CPlayerOperator::CPlayerOperator()
{
}


CPlayerOperator::~CPlayerOperator()
{
}

void CPlayerOperator::Update()
{
	Input();
}

void CPlayerOperator::Input()
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
	else
		m_pACommander->m_fOrder = 0.f;

	if (GetKey->KeyDown(VK_SPACE))
		m_pACommander->m_bBuild = true;
}
