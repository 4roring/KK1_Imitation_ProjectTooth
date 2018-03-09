#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	Device->InitDevice();
	Time->InitTime();
	SceneMgr->SceneChange(SCENE_LOGO);
}

void CMainGame::Update()
{
	Time->SetTime();
	SceneMgr->Update();
}

void CMainGame::LateUpdate()
{
	GetKey->Update();
	SceneMgr->LateUpdate();
}

void CMainGame::Render()
{
	Device->Begin();
	SceneMgr->Render();
	Device->End();
}

void CMainGame::Release()
{
	ViewMgr->DestroyInstance();
	SceneMgr->DestroyInstance();
	GameMgr->DestroyInstance();
	TextureMgr->DestroyInstance();
	Device->DestroyInstance();
	GetKey->DestroyInstance();
	Time->DestroyInstance();
}