#include "stdafx.h"
#include "APlayer.h"


APlayer::APlayer()
{
}


APlayer::~APlayer()
{
	Release();
}

HRESULT APlayer::Initialize()
{
	CActor::Initialize();

	m_tInfo.vPosition = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	ZeroMemory(m_tInfo.matWorld, sizeof(D3DXMATRIX));

	TextureMgr->InsertTexture(TEXT("../Texture/Actors/commander_commoners.png"), TEXT("Red_Player"), TEX_SINGLE);
	m_pTexMain = TextureMgr->GetTexture(TEXT("Red_Player"));

	TextureMgr->InsertTexture(TEXT("../Texture/Actors/commander_commoners_tint.png"), TEXT("Red_Player_Tint"), TEX_SINGLE);
	m_pTexTint = TextureMgr->GetTexture(TEXT("Red_Player_Tint"));

	m_tFrame.fMin = 0.f;
	m_tFrame.fFrame = 0.f;
	m_tFrame.fCount = 12.f;
	m_tFrame.fMax = 63.f;

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_fSpeed = 100.f;

	return S_OK;
}

OBJSTATE APlayer::Update(float deltaTime)
{
	// �÷��̾� �۾� �켱.
	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.vPosition.x -= m_fSpeed * deltaTime;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.vPosition.x += m_fSpeed * deltaTime;

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 2.f, 2.f, 2.f);
	D3DXMatrixRotationZ(&matRotZ, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPosition.x, m_tInfo.vPosition.y, m_tInfo.vPosition.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// Actor ���� �۾� ȣ��.
	CActor::Update(deltaTime);

	return STATE_PLAY;
}

void APlayer::LateUpdate()
{
}

void APlayer::Render()
{
	int iSceneLeft = m_tScene.iFrame * COMMANDER_CX;
	int iSceneTop = m_tScene.iScene * COMMANDER_CY;
	int iSceneRight = m_tScene.iFrame * COMMANDER_CX + COMMANDER_CX;
	int iSceneBottom = m_tScene.iScene * COMMANDER_CY + COMMANDER_CY;

	RECT rc = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom};

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(m_pTexMain->pTexture
		, &rc
		, &Vector3(float(COMMANDER_CY >> 1), float(COMMANDER_CX >> 1), 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDevice::GetInstance()->GetSprite()->Draw(m_pTexTint->pTexture
		, &rc
		, &Vector3(float(COMMANDER_CY >> 1), float(COMMANDER_CX >> 1), 0.f)
		, nullptr, *m_TeamColor);
}

void APlayer::Release()
{

}
