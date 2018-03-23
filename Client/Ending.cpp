#include "stdafx.h"
#include "Ending.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

HRESULT CEnding::Initialize()
{
	TextureMgr->InsertTexture(TEXT("../Texture/Ending.png"), TEXT("Ending"), TEX_SINGLE);
	SoundMgr->PlaySound(TEXT("Victory"), SoundMgr->PLAYER);
	return S_OK;
}

void CEnding::Update()
{
}

void CEnding::LateUpdate()
{
}

void CEnding::Render()
{
	const TEXINFO* pTexInfo = TextureMgr->GetTexture(TEXT("Ending"));

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}


void CEnding::Release()
{
}
