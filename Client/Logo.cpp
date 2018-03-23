#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Initialize()
{
	TextureMgr->InsertTexture(TEXT("../Texture/Logo.png"), TEXT("Logo"), TEX_SINGLE);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, this, 0, nullptr);
	if (nullptr == m_hThread)
	{
		MSG_BOX(TEXT("Thread Create Failed!!!"));
		return E_FAIL;
	}

	m_pFont = Device->GetFoodFont();

	return S_OK;
}

void CLogo::Update()
{
	if (true == m_bComplete && GetKey->KeyPress(VK_RETURN))
		SceneMgr->SceneChange(SCENE_TITLE);
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
	const TEXINFO* pTexInfo = TextureMgr->GetTexture(TEXT("Logo"));

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&matTrans, 50.f, 700.f, 0.f);
	m_pSprite->SetTransform(&matTrans);
	m_pFont->DrawTextW(m_pSprite, m_pLoadingMessage, lstrlen(m_pLoadingMessage), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CLogo::Release()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

void CLogo::TextureLoad(TCHAR* FilePath)
{
	std::wifstream LoadFile;
	LoadFile.open(FilePath, std::ios::in, std::ios::binary);

	TCHAR szBuf[128];

	TEXTYPE eType;
	int iCount;
	std::wstring wstrObjKey = TEXT("");
	std::wstring wstrStateKey = TEXT("");
	std::wstring wstrPath = TEXT("");

	while (false == LoadFile.eof())
	{
		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		eType = static_cast<TEXTYPE>(_wtoi(szBuf));

		if (eType == TEX_MULTI)
		{
			LoadFile.getline(szBuf, sizeof(szBuf), '@');
			iCount = _wtoi(szBuf);
			LoadFile.getline(szBuf, sizeof(szBuf), '@');
			wstrStateKey = szBuf;
		}

		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		wstrObjKey = szBuf;
		LoadFile.getline(szBuf, sizeof(szBuf));
		wstrPath = szBuf;

		if (eType == TEX_MULTI)
			TextureMgr->InsertTexture(wstrPath, wstrObjKey, eType
				, wstrStateKey, iCount);
		else
			TextureMgr->InsertTexture(wstrPath, wstrObjKey, eType);
	}

	LoadFile.close();
}

unsigned int CLogo::ThreadFunc(void * pArg)
{
	CLogo* pLogo = static_cast<CLogo*>(pArg);

	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중."));
	pLogo->TextureLoad(TEXT("../Data/MapTexture.dat"));
	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중.."));
	pLogo->TextureLoad(TEXT("../Data/ActorTexture.dat"));
	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중..."));
	pLogo->TextureLoad(TEXT("../Data/StructureTexture.dat"));
	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중."));
	pLogo->TextureLoad(TEXT("../Data/AtlasTexture.dat"));
	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중.."));
	pLogo->TextureLoad(TEXT("../Data/BulletTexture.dat"));
	pLogo->SetLoadingMessage(TEXT("이미지 데이터 로딩중..."));
	pLogo->TextureLoad(TEXT("../Data/UITexture.dat"));

	pLogo->SetLoadingMessage(TEXT("사운드 데이터 로딩중"));
	if (FAILED(SoundMgr->Initialize()))
	{
		MSG_BOX(TEXT("Sound Manager Initialize Failed"));
		return E_FAIL;
	}

	pLogo->SetLoadingMessage(TEXT("로딩 완료"));
	pLogo->m_bComplete = true;

	return 0;
}

