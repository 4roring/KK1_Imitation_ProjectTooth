#include "stdafx.h"
#include "Stage_3.h"
#include "ACommander.h"
#include "Level.h"
#include "Deco.h"

CStage_3::CStage_3()
{
}


CStage_3::~CStage_3()
{
}

HRESULT CStage_3::Initialize()
{
	GameMgr->Initialize();
	GameMgr->CreateObject(CAbsFactory<ACommander>::Create(), OBJ_PLAYER);
	GameMgr->CreateObject(CAbsFactory<CLevel>::Create(), OBJ_LEVEL);

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

		GameMgr->CreateObject(CAbsFactory<CDeco>::CreateDeco(wstrObjKey, wstrStateKey, iCount, vPos), OBJ_DECO);
	}

	CloseHandle(hFile);
}


