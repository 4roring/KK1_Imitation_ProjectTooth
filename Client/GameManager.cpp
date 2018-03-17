#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"
#include "DSubject.h"
#include "AStar.h"

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
	m_TeamColor[TEAM_NEUTRAL] = D3DCOLOR_ARGB(255, 255, 255, 255);

	for (int i = 0; i < TEAM_NEUTRAL;++i)
		m_pSubject[i] = new DSubject;

	m_pAStar = new CAStar;
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
				SafeDelete(*iter);
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
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObject : ObjectList[i])
		{
			OBJLAYER eLayer = pObject->GetLayer();

			switch (eLayer)
			{
			case LAYER_OBJ:
				m_vecRender[eLayer].push_back(pObject);
				continue;
			case LAYER_EFFECT:
				m_vecRender[eLayer].push_back(pObject);
				continue;
			case LAYER_UI:
				m_vecRender[eLayer].push_back(pObject);
				continue;
			default:
				break;
			}
			pObject->Render();
		}
	}

	std::sort(m_vecRender[LAYER_OBJ].begin(), m_vecRender[LAYER_OBJ].end(),
		[](auto& pObj1, auto& pObj2)->bool
	{
		return pObj1->GetInfo().vPosition.y < pObj2->GetInfo().vPosition.y;
	});

	for (auto& pObject : m_vecRender[LAYER_OBJ])
		pObject->Render();

	for (auto& pObject : m_vecRender[LAYER_EFFECT])
		pObject->Render();

	for (auto& pObject : m_vecRender[LAYER_UI])
		pObject->Render();

	for (int i = 0; i < LAYER_END; ++i)
		m_vecRender[i].clear();
}

void CGameManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		DestroyObject(i);

	for (auto& pSubject : m_pSubject)
		SafeDelete(pSubject);

	SafeDelete(m_pAStar);
}