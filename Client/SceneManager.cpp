#include "stdafx.h"
#include "SceneManager.h"
#include "Logo.h"
#include "Title.h"
#include "Stage_3.h"
#include "Ending.h"


CSceneManager::CSceneManager()
{
	D3DXMatrixIdentity(&m_matIdentity);
}


CSceneManager::~CSceneManager()
{
	Release();
}

HRESULT CSceneManager::SceneChange(SCENEID eSceneID)
{
	m_bFade = true;
	m_bSceneChange = true;
	m_eSceneID = eSceneID;
	
	return S_OK;
}

void CSceneManager::Update()
{
	if(false == m_bSceneChange)
		m_pScene->Update();
}

void CSceneManager::LateUpdate()
{
	if (false == m_bSceneChange)
		m_pScene->LateUpdate();
}

void CSceneManager::Render()
{
	if (false == m_bSceneChange)
		m_pScene->Render();

	if (true == m_bFade)
		FadeIn();
	else
		FadeOut();
}

void CSceneManager::Release()
{
	SafeDelete(m_pScene);
}

void CSceneManager::FrameEnd()
{
	if (true == m_bSceneChange)
	{
		Release();

		switch (m_eSceneID)
		{
		case SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case SCENE_TITLE:
			m_pScene = new CTitle;
			break;
		case SCENE_STAGE:
			m_pScene = new CStage_3;
			break;
		case SCENE_ENDING:
			m_pScene = new CEnding;
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
			return;
		}

		m_bSceneChange = false;
	}
}

void CSceneManager::FadeIn()
{
	if (nullptr != m_pScene)
		m_pScene->Render();

	m_fAlpha += 200.f * Time->GetDeltaTime();

	const TEXINFO* pTex = TextureMgr->GetTexture(TEXT("BlackScreen"));
	Device->GetSprite()->SetTransform(&m_matIdentity);
	Device->GetSprite()->Draw(pTex->pTexture, nullptr, nullptr, nullptr
		, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));

	if (m_fAlpha >= 250.f)
	{
		m_fAlpha = 255.f;
		m_bFade = false;
	}
}

void CSceneManager::FadeOut()
{
	if (m_fAlpha >= 10.f)
	{
		m_fAlpha -= 200.f * Time->GetDeltaTime();

		const TEXINFO* pTex = TextureMgr->GetTexture(TEXT("BlackScreen"));
		Device->GetSprite()->SetTransform(&m_matIdentity);
		Device->GetSprite()->Draw(pTex->pTexture, nullptr, nullptr, nullptr
			, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));
	}
	FrameEnd();
}
