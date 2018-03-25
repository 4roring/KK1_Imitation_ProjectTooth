#include "stdafx.h"
#include "TitleButton.h"


CTitleButton::CTitleButton()
{
}


CTitleButton::~CTitleButton()
{
	Release();
}

HRESULT CTitleButton::Initialize()
{
	m_eLayer = LAYER_UI;

	m_pTexMain = TextureMgr->GetTexture(TEXT("buttonbg1_small"));
	m_TexOverlay = TextureMgr->GetTexture(TEXT("buttonbg1_small_overlay"));
	m_TexTabOn = TextureMgr->GetTexture(TEXT("buttontab1_on"));
	m_TexTabOff = TextureMgr->GetTexture(TEXT("buttontab1_off"));

	m_pFont = Device->GetTitleFont();

	return S_OK;
}

OBJSTATE CTitleButton::Update(float deltaTime)
{
	m_bOnMouse = (true == CheckMousePos()) ? true : false;

	if (true == m_bOnMouse)
	{
		if (false == m_bOnMouseSound)
		{
			SoundMgr->PlaySound(TEXT("Menu_OnMouse"), SoundMgr->FAR_EFFECT);
			m_bOnMouseSound = true;
		}

		if (KeyMgr->KeyDown(VK_LBUTTON))
		{
			SoundMgr->PlaySound(TEXT("Menu_Select"), SoundMgr->FAR_EFFECT);
			if (m_iOption == 0)
				SceneMgr->SceneChange(SCENE_STAGE);
			else
				DestroyWindow(g_hMain);
		}
	}
	else
		m_bOnMouseSound = false;

	return STATE_PLAY;
}

void CTitleButton::LateUpdate()
{
}

void CTitleButton::Render()
{
	ButtonRender();
	TextRender();

}

void CTitleButton::Release()
{
}

void CTitleButton::FrameEnd()
{
	
}

bool CTitleButton::CheckMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (pt.x < m_tInfo.vPosition.x || pt.x > m_tInfo.vPosition.x + m_pTexMain->tImageInfo.Width) return false;
	if (pt.y < m_tInfo.vPosition.y || pt.y > m_tInfo.vPosition.y + m_pTexMain->tImageInfo.Height) return false;

	return true;
}

void CTitleButton::ButtonRender()
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPosition.x, m_tInfo.vPosition.y, 0.f);

	if (m_iOption == 1)
	{
		D3DXMatrixScaling(&matScale, 0.8f, 0.8f, 1.f);
		matScale *= matTrans;
		m_pSprite->SetTransform(&matScale);
	}
	else
		m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(m_pTexMain->pTexture, nullptr, nullptr,
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (true == m_bOnMouse)
		m_pSprite->Draw(m_TexTabOn->pTexture, nullptr, nullptr
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
		m_pSprite->Draw(m_TexTabOff->pTexture, nullptr, nullptr
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTitleButton::TextRender()
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixIdentity(&matScale);
	TCHAR szBuf[32] = {};

	if (m_iOption == 1)
	{
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPosition.x + 75.f, m_tInfo.vPosition.y + 20.f, 0.f);
		D3DXMatrixScaling(&matScale, 0.8f, 0.8f, 1.f);
		matScale *= matTrans;
		m_pSprite->SetTransform(&matScale);
		lstrcpy(szBuf, TEXT("종료"));
	}
	else
	{
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPosition.x + 43.f, m_tInfo.vPosition.y + 25.f, 0.f);
		lstrcpy(szBuf, TEXT("게임 시작"));
		m_pSprite->SetTransform(&matTrans);
	}
	m_pFont->DrawTextW(m_pSprite, szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 184, 164, 126));
}
