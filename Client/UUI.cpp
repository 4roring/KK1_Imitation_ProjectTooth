#include "stdafx.h"
#include "UUI.h"
#include "DObserver.h"
#include "DSubject.h"

UUI::UUI()
{
}


UUI::~UUI()
{
	Release();
}

HRESULT UUI::Initialize()
{
	m_eLayer = LAYER_UI;
	m_eTeam = TEAM_RED;
	m_pTexMain = TextureMgr->GetTexture(TEXT("ui"), TEXT("unitbar_woodbg"));

	if (nullptr == m_pTexMain) return E_FAIL;

	m_pObserver = new DObserver;
	GameMgr->GetSubject(m_eTeam)->Subscribe(m_pObserver);

	return S_OK;
}

OBJSTATE UUI::Update(float deltaTime)
{
	return STATE_PLAY;
}

void UUI::LateUpdate()
{
}

void UUI::Render()
{
}

void UUI::Release()
{
	if (nullptr != m_pObserver)
		GameMgr->GetSubject(m_eTeam)->UnSubscribe(m_pObserver);
	SafeDelete(m_pObserver);
}

void UUI::UpdateMatrixScreenUI()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x
		, m_tInfo.vPosition.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;
}

void UUI::UpdateMatrixWorldUI(float fDiameter)
{
	Vector3 vScroll = ViewMgr->GetScroll();
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, fDiameter, fDiameter, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x
		, m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;
}

