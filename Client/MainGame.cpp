#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	if (FAILED(Device->InitDevice()))
		return E_FAIL;

	Time->InitTime();
	if (FAILED(TextureMgr->InsertTexture(TEXT("../Texture/BlackScreen.png"), TEXT("BlackScreen"), TEX_SINGLE)))
		return E_FAIL;

	if (SceneMgr->SceneChange(SCENE_LOGO))
		return E_FAIL;

	return S_OK;
}

void CMainGame::Update()
{
	Time->SetTime();
	SceneMgr->Update();
}

void CMainGame::LateUpdate()
{
	SceneMgr->LateUpdate();
	KeyMgr->Update();
	SoundMgr->Update();
}

void CMainGame::Render()
{
	Device->Begin();
	SceneMgr->Render();
	Device->End();
}

void CMainGame::Release()
{
	SoundMgr->DestroyInstance();
	ViewMgr->DestroyInstance();
	SceneMgr->DestroyInstance();
	GameMgr->DestroyInstance();
	TextureMgr->DestroyInstance();
	KeyMgr->DestroyInstance();
	Time->DestroyInstance();
	Device->DestroyInstance();
}

