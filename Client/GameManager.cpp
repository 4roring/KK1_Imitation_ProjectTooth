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

void CGameManager::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_ObjectList[i])
			pObject->Render();
	}
}