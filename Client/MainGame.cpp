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
	TextureMgr->InsertTexture(TEXT("../Texture/BlackScreen.png"), TEXT("BlackScreen"), TEX_SINGLE);
	SceneMgr->SceneChange(SCENE_LOGO);
}

void CMainGame::Update()
{
	Time->SetTime();
	SceneMgr->Update();
}

void CMainGame::LateUpdate()
{
	SceneMgr->LateUpdate();
	GetKey->Update();
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
	GetKey->DestroyInstance();
	Time->DestroyInstance();
	Device->DestroyInstance();
}

