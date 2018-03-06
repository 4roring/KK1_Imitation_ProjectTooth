#include "stdafx.h"
#include "MainGame.h"
#include "APlayer.h"


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
	GameMgr->Initialize();
	GameMgr->CreateObject(CAbsFactory<APlayer>::Create(), OBJ_PLAYER);
	Time->InitTime();
}

void CMainGame::Update()
{
	Time->SetTime();
	GameMgr->Update(Time->GetTime());
	GetKey->Update();
}

void CMainGame::Render()
{
	Device->Begin();
	GameMgr->Render();
	Device->End();
}

void CMainGame::Release()
{
	GameMgr->DestroyInstance();
	TextureMgr->DestroyInstance();
	Device->DestroyInstance();
	GetKey->DestroyInstance();
	Time->DestroyInstance();
}