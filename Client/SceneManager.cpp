#include "stdafx.h"
#include "SceneManager.h"
#include "Logo.h"
#include "Stage_3.h"


CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::SceneChange(SCENEID eSceneID)
{
	Release();

	switch (eSceneID)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;
	case SCENE_TITLE:
		break;
	case SCENE_STAGE_3:
		m_pScene = new CStage_3;
		break;
	default:
#ifdef _DEBUG
		assert(!"SceneID Error");
#endif
		break;
	}

	if (FAILED(m_pScene->Initialize()))
	{
		MSG_BOX(TEXT("Scene Initialize Failed!!!"));
		return E_FAIL;
	}

	return S_OK;
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneManager::Render()
{
	m_pScene->Render();
}

void CSceneManager::Release()
{
	SafeDelete(m_pScene);
}
