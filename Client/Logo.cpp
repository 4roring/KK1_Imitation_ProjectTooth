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

	TextureLoad(TEXT("../Data/MapTexture.dat"));
	TextureLoad(TEXT("../Data/ActorTexture.dat"));
	TextureLoad(TEXT("../Data/StructureTexture.dat"));

	return S_OK;
}

void CLogo::Update()
{
	if (GetKey->KeyDown(VK_RETURN))
		SceneMgr->SceneChange(SCENE_STAGE_3);
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);

	const TEXINFO* pTexInfo = TextureMgr->GetTexture(TEXT("Logo"));

	m_pSprite->SetTransform(&matIdentity);
	m_pSprite->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLogo::Release()
{
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

