#include "stdafx.h"
#include "Crop.h"


CCrop::CCrop()
{
}


CCrop::~CCrop()
{
	Release();
}

HRESULT CCrop::Initialize()
{
	m_eLayer = LAYER_OBJ;

	m_pTexMain = TextureMgr->GetTexture(TEXT("windmill_field_crop_sheet"));

	m_iImageCX = 24;
	m_iImageCY = 22;

	m_iFrame = GameMgr->GetRandom(0, 3);

	return S_OK;
}

OBJSTATE CCrop::Update(float deltaTime)
{
	if (true == m_bDestroy)
		return STATE_DESTROY;

	return STATE_PLAY;
}

void CCrop::LateUpdate()
{
	UpdateRect();
}

void CCrop::Render()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x
		, m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(float(m_iImageCX >> 1), float(m_iImageCY >> 1), 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCrop::Release()
{
}

void CCrop::UpdateRect()
{
	int iSceneLeft = m_iFrame * m_iImageCX;
	int iSceneTop = 0;
	int iSceneRight = m_iFrame * m_iImageCX + m_iImageCX;
	int iSceneBottom = m_iImageCY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}
