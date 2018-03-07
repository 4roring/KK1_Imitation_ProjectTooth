#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"

CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}

void CGameManager::CreateObject(CGameObject * pObject, OBJID eID)
{
	m_ObjectList[eID].push_back(pObject);
}

void CGameManager::Initialize()
{
	m_TeamColor[TEAM_RED] = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_TeamColor[TEAM_GREEN] = D3DCOLOR_ARGB(255, 0, 255, 0);
	m_TeamColor[TEAM_BLUE] = D3DCOLOR_ARGB(255, 0, 0, 255);
	m_TeamColor[TEAM_YELLO] = D3DCOLOR_ARGB(255, 255, 255, 0);
}

void CGameManager::Update(float deltaTime)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end(); )
		{
			OBJSTATE eState = (*iter)->Update(deltaTime);

			switch (eState)
			{
			case STATE_PLAY:
				++iter;
				break;

			case STATE_WAIT:
				break;

			case STATE_DESTROY:
				iter = m_ObjectList[i].erase(iter);
				break;
			}
		}
	}

}

void CGameManager::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}
}

void CGameManager::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->Render();
	}
}