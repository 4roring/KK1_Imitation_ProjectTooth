#include "stdafx.h"
#include "Stage_3.h"
#include "ACommander.h"
#include "Level.h"
#include "Deco.h"
#include "UI.h"

CStage_3::CStage_3()
{
}


CStage_3::~CStage_3()
{
	Release();
}

HRESULT CStage_3::Initialize()
{
	GameMgr->Initialize();
	Vector3 vPos = Vector3(680.f, 2600.f, 0.f);
	GameMgr->CreateObject(DObjectFactory<ACommander>::Create(vPos, TEAM_RED), OBJ_PLAYER);
	vPos = Vector3(2525.f, 3170.f, 0.f);
	GameMgr->CreateObject(DObjectFactory<ACommander>::Create(vPos, TEAM_BLUE), OBJ_AI);
	GameMgr->CreateObject(DObjectFactory<CLevel>::Create(), OBJ_LEVEL);
	GameMgr->CreateObject(DObjectFactory<CUI>::Create(), OBJ_UI);

	LoadDeco();

	return S_OK;
}

void CStage_3::Update()
{
	GameMgr->Update(Time->GetDeltaTime());
}

void CStage_3::LateUpdate()
{
	GameMgr->LateUpdate();
}

void CStage_3::Render()
{
	GameMgr->Render();
}

void CStage_3::Release()
{
	GameMgr->DestroyObject(OBJ_LEVEL);
	GameMgr->DestroyObject(OBJ_PLAYER);
	GameMgr->DestroyObject(OBJ_AI);
	GameMgr->DestroyObject(OBJ_UNIT);
}

void CStage_3::LoadDeco()
{
	HANDLE hFile = CreateFile(TEXT("../Data/DecoData.dat"), 
		GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	DWORD dwByte = 0;

	TCHAR szBuf[128] = {};
	std::wstring wstrObjKey = {};
	std::wstring wstrStateKey = {};
	Vector3 vPos;
	int iCount = 0;

	while (true)
	{
		ReadFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);
		
		if (dwByte <= 0) break;
		wstrObjKey = szBuf;

		ReadFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);
		wstrStateKey = szBuf;

		ReadFile(hFile, vPos, sizeof(Vector3), &dwByte, nullptr);
		ReadFile(hFile, &iCount, sizeof(int), &dwByte, nullptr);

		GameMgr->CreateObject(DObjectFactory<CDeco>::CreateDeco(wstrObjKey, wstrStateKey, iCount, vPos * fScreenZoom), OBJ_DECO);
	}

	CloseHandle(hFile);
}


