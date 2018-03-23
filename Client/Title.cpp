#include "stdafx.h"
#include "Title.h"
#include "TitleButton.h"

CTitle::CTitle()
{
}


CTitle::~CTitle()
{
	Release();
}

HRESULT CTitle::Initialize()
{
	for (int i = 0; i < 2; ++i)
	{
		CGameObject* m_pTitleButton = DObjectFactory<CTitleButton>::Create(Vector3(80.f, 350.f + (i* 130.f), 0.f));
		dynamic_cast<CTitleButton*>(m_pTitleButton)->SetButtonOption(i);
		GameMgr->CreateObject(m_pTitleButton, OBJ_UI);
	}

	SoundMgr->PlayBGM(TEXT("Title"));

	return S_OK;
}

void CTitle::Update()
{
	GameMgr->Update(0.f);
}

void CTitle::LateUpdate()
{
	GameMgr->LateUpdate();
}

void CTitle::Render()
{
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	const TEXINFO* pTexInfo = TextureMgr->GetTexture(TEXT("title"));

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	GameMgr->Render();
}

void CTitle::Release()
{
	GameMgr->DestroyObject(OBJ_UI);
	SoundMgr->StopAll();
}
