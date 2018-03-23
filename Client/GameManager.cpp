#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"
#include "DSubject.h"
#include "AStar.h"
#include "ACommander.h"
#include "Level.h"

CGameManager::CGameManager()
{

}


CGameManager::~CGameManager()
{
	Release();
}

int CGameManager::GetRandom(int iMin, int iMax) const
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> range(iMin, iMax);

	return range(mt);
}

void CGameManager::CreateObject(CGameObject * pObject, OBJID eObjectID)
{
	pObject->SetObjectID(eObjectID);
	m_ObjectList[eObjectID].push_back(pObject);

	if (eObjectID == OBJ_PLAYER || eObjectID == OBJ_AI)
		m_pCommander[pObject->GetTeamID()] = dynamic_cast<ACommander*>(pObject);
}

void CGameManager::DestroyObject(int eObjectID)
{
	std::for_each(m_ObjectList[eObjectID].begin(), m_ObjectList[eObjectID].end(), SafeDelete<CGameObject*>);
	m_ObjectList[eObjectID].clear();
}

bool CGameManager::ObjectCulling(const Vector3 & vPos)
{
	Vector3 vScrollPos = vPos + ViewMgr->GetScroll();

	if (vScrollPos.x < -100.f) return true;
	if (vScrollPos.y < -100.f) return true;
	if (vScrollPos.x > WINCX + 100.f) return true;
	if (vScrollPos.y > WINCY + 100.f) return true;

	return false;
}

void CGameManager::Initialize()
{
	m_TeamColor[TEAM_RED] = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_TeamColor[TEAM_GREEN] = D3DCOLOR_ARGB(255, 80, 180, 80);
	m_TeamColor[TEAM_BLUE] = D3DCOLOR_ARGB(255, 0, 0, 255);
	m_TeamColor[TEAM_YELLO] = D3DCOLOR_ARGB(255, 255, 255, 0);
	m_TeamColor[TEAM_NEUTRAL] = D3DCOLOR_ARGB(255, 255, 255, 255);

	for (int i = 0; i < TEAM_NEUTRAL; ++i)
		m_pSubject[i] = new DSubject;

	m_pAStar = new CAStar;
}

void CGameManager::Update(float deltaTime)
{
	UpdateFPS(deltaTime);
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
				continue;

			case STATE_DESTROY:
				SafeDelete(*iter);
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
		{
			OBJLAYER eLayer = pObject->GetLayer();

			switch (eLayer)
			{
			case LAYER_OBJ:
			case LAYER_EFFECT:
			case LAYER_WORLDUI:
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

	for (int i = 0; i < LAYER_END; ++i)
	{
		for (auto& pObject : m_vecRender[i])
		{
			if(i == LAYER_OBJ)
				if (true == ObjectCulling(pObject->GetInfo().vPosition))
					continue;

			pObject->Render();
		}
	}

	for (int i = 0; i < LAYER_END; ++i)
		m_vecRender[i].clear();

	RenderFPS();
}

void CGameManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		DestroyObject(i);

	for (auto& pSubject : m_pSubject)
		SafeDelete(pSubject);

	SafeDelete(m_pAStar);
}

//#ifdef _DEBUG
void CGameManager::UpdateFPS(float deltaTime)
{
	m_fFPSTime += deltaTime;
	++m_iCount;
}
void CGameManager::RenderFPS()
{
	if (m_fFPSTime >= 1.f)
	{
		m_fFPSTime = 0.f;
		m_iFPS = m_iCount;
		m_iCount = 0;
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);

	TCHAR szBuf[16] = {};
	swprintf_s(szBuf, TEXT("FPS : %d"), m_iFPS);

	Device->GetSprite()->SetTransform(&matTrans);
	Device->GetFont()->DrawTextW(Device->GetSprite(), szBuf, lstrlen(szBuf)
		, nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}
//#endif