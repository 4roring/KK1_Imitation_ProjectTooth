#include "stdafx.h"
#include "DPlayerCommand.h"
#include "ACommander.h"
#include "DSubject.h"
#include "AUnit.h"

DPlayerCommand::DPlayerCommand()
{
}


DPlayerCommand::~DPlayerCommand()
{
}

void DPlayerCommand::Initialize()
{
}

void DPlayerCommand::Update()
{
	Input();
}

void DPlayerCommand::Input()
{
	if (KeyMgr->KeyPress('A'))
		m_pACommander->m_tInfo.vDir.x = -1.f;
	else if (KeyMgr->KeyPress('D'))
		m_pACommander->m_tInfo.vDir.x = 1.f;
	else
		m_pACommander->m_tInfo.vDir.x = 0.f;

	if (KeyMgr->KeyPress('W'))
		m_pACommander->m_tInfo.vDir.y = -1.f;
	else if (KeyMgr->KeyPress('S'))
		m_pACommander->m_tInfo.vDir.y = 1.f;
	else
		m_pACommander->m_tInfo.vDir.y = 0.f;

	if (KeyMgr->KeyPress(VK_LBUTTON))
	{
		m_pACommander->m_fOrder += Time->GetDeltaTime();
		m_pACommander->m_bAllOrder = false;
		PlayOrderSound();
	}
	else if (KeyMgr->KeyPress(VK_RBUTTON))
	{
		m_pACommander->m_fOrder += Time->GetDeltaTime();
		m_pACommander->m_bAllOrder = true;
		PlayOrderSound();
	}
	else
	{
		m_pACommander->m_fOrder = 0.f;
		m_bOrderSound = false;
	}
		

	if (KeyMgr->KeyDown(VK_SPACE))
		m_pACommander->m_bBuild = true;

	if (KeyMgr->KeyDown('Q'))
	{
		if (--m_pACommander->m_iSelectSlot < 0)
			m_pACommander->m_iSelectSlot = SLOT_MAX - 1;

		GameMgr->GetSubject(m_pACommander->m_eTeam)->NotifySlotNum(m_pACommander->m_iSelectSlot);
	}

	if (KeyMgr->KeyDown('E'))
	{
		if (++m_pACommander->m_iSelectSlot >= SLOT_MAX)
			m_pACommander->m_iSelectSlot = 0;

		GameMgr->GetSubject(m_pACommander->m_eTeam)->NotifySlotNum(m_pACommander->m_iSelectSlot);
	}	

	if (KeyMgr->KeyDown('1'))
	{
		ACommander* pCommander = nullptr;
		for (int i = 0; i < TEAM_NEUTRAL; ++i)
		{
			pCommander = GameMgr->GetCommander((TEAMID)i);
			pCommander->ViewTeamSelect(TEAM_RED);
			if (i == TEAM_RED)
			{
				Vector3 vInitScroll((WINCX >> 1) - pCommander->m_tInfo.vPosition.x, (WINCY >> 1) - pCommander->m_tInfo.vPosition.y, 0.f);
				ViewMgr->SetScroll(vInitScroll);
			}
		}
	}
		
	if (KeyMgr->KeyDown('2'))
	{
		ACommander* pCommander = nullptr;
		for (int i = 0; i < TEAM_NEUTRAL; ++i)
		{
			pCommander = GameMgr->GetCommander((TEAMID)i);
			pCommander->ViewTeamSelect(TEAM_BLUE);
			if (i == TEAM_BLUE)
			{
				Vector3 vInitScroll((WINCX >> 1) - pCommander->m_tInfo.vPosition.x, (WINCY >> 1) - pCommander->m_tInfo.vPosition.y, 0.f);
				ViewMgr->SetScroll(vInitScroll);
			}
		}
	}

	if (KeyMgr->KeyDown('3'))
	{
		ACommander* pCommander = nullptr;
		for (int i = 0; i < TEAM_NEUTRAL; ++i)
		{
			pCommander = GameMgr->GetCommander((TEAMID)i);
			pCommander->ViewTeamSelect(TEAM_GREEN);
			if (i == TEAM_GREEN)
			{
				Vector3 vInitScroll((WINCX >> 1) - pCommander->m_tInfo.vPosition.x, (WINCY >> 1) - pCommander->m_tInfo.vPosition.y, 0.f);
				ViewMgr->SetScroll(vInitScroll);
			}
		}
	}

	if (KeyMgr->KeyDown('4'))
	{
		ACommander* pCommander = nullptr;
		for (int i = 0; i < TEAM_NEUTRAL; ++i)
		{
			pCommander = GameMgr->GetCommander((TEAMID)i);
			pCommander->ViewTeamSelect(TEAM_YELLO);
			if (i == TEAM_YELLO)
			{
				Vector3 vInitScroll((WINCX >> 1) - pCommander->m_tInfo.vPosition.x, (WINCY >> 1) - pCommander->m_tInfo.vPosition.y, 0.f);
				ViewMgr->SetScroll(vInitScroll);
			}
		}
	}

	if (KeyMgr->KeyDown('R'))
		m_pACommander->m_iFood += 100;
}

void DPlayerCommand::PlayOrderSound()
{
	if (false == m_bOrderSound)
	{
		Vector3 vPos = m_pACommander->m_tInfo.vPosition;

		if (true == m_pACommander->m_bAllOrder)
		{
			SoundMgr->PlayEffectSound(TEXT("Order"), vPos);
			m_bOrderSound = true;
			return;
		}

		UNITID eUnit = m_pACommander->m_eUnit[m_pACommander->m_iSelectSlot];

		switch (eUnit)
		{
		case UNIT_SQUIRREL:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Squirrel"), vPos);
					break;
				}
			}
			break;
		case UNIT_LIZARD:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Lizard"), vPos);
					break;
				}
			}
			break;
		case UNIT_TOAD:
			break;
		case UNIT_PIGEON:
			break;
		case UNIT_MOLE:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Mole"), vPos);
					break;
				}
			}
			break;
		case UNIT_FERRET:
			break;
		case UNIT_CHAMELEON:
			break;
		case UNIT_FALCON:
			break;
		case UNIT_SKUNK:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Skunk"), vPos);
					break;
				}
			}
			break;
		case UNIT_SNAKE:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Snake"), vPos);
					break;
				}
			}
			break;
		case UNIT_BADGER:
			for (const auto& pUnit : GameMgr->GetObjectList(OBJ_UNIT))
			{
				if (pUnit->GetTeamID() == m_pACommander->m_eTeam
					&& static_cast<AUnit*>(pUnit)->GetUnitID() == eUnit)
				{
					SoundMgr->PlayEffectSound(TEXT("Unit_Badger"), vPos);
					break;
				}
			}
			break;
		case UNIT_BOAR:
			break;
		case UNIT_FOX:
			break;
		case UNIT_OWL:
			break;
		case UNIT_WOLF:
			break;
		default:
			break;
		}

		m_bOrderSound = true;
	}
}
