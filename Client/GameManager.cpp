#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"

CGameManager::CGameManager()
{

}


CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::CreateObject(CGameObject * pObject, OBJID eObjectID)
{
	pObject->SetObjectID(eObjectID);
	ObjectList[eObjectID].push_back(pObject);
}

void CGameManager::DestroyObject(int eObjectID)
{
	std::for_each(ObjectList[eObjectID].begin(), ObjectList[eObjectID].end(), SafeDelete<CGameObject*>);
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
		for (auto iter = ObjectList[i].begin(); iter != ObjectList[i].end(); )
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
				iter = ObjectList[i].erase(iter);
				break;
			}
		}
	}
}

void CGameManager::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : ObjectList[i])
			pObject->LateUpdate();
	}
}

void CGameManager::Render()
{
	for(auto& pObject : ObjectList[OBJ_LEVEL])
		pObject->Render();

	for (int i = 1; i < OBJ_END; ++i)
	{
		for (auto& pObject : ObjectList[i])
		{
			OBJLAYER eLayer = pObject->GetLayer();

			if (eLayer == LAYER_OBJ)
			{
				m_vecRender[eLayer].push_back(pObject);
				continue;
			}
			pObject->Render();
		}
	}

	for (int i = 0; i < LAYER_END; ++i)
	{
		std::sort(m_vecRender[i].begin(), m_vecRender[i].end(),
			[](auto& pObj1, auto& pObj2)->bool
		{
			return pObj1->GetInfo().vPosition.y < pObj2->GetInfo().vPosition.y;
		});
	}

	for (int i = 0; i < LAYER_END; ++i)
	{
		for (auto& pObject : m_vecRender[i])
			pObject->Render();

		m_vecRender[i].clear();
	}
}

void CGameManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		DestroyObject(i);
}