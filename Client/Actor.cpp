#include "stdafx.h"
#include "Actor.h"
#include "Level.h"

AActor::AActor()
{
}


AActor::~AActor()
{
}

HRESULT AActor::Initialize()
{
	m_eLayer = LAYER_OBJ;
	m_TeamColor = GameMgr->GetTeamColor(m_eTeam);

	return S_OK;
}

OBJSTATE AActor::Update(float deltaTime)
{
	FrameMove(deltaTime);
	UpdateFlipX();
	return STATE_PLAY;
}

void AActor::LateUpdate()
{
	// GetTileIndex를 실행하여 현재타일과 이전타일이 다를 경우
	// 갈 수 있는 공간인지 우선 체크하고
	// 이전 타일의 CGameObejct*은 nullptr 현재 타일은 자신을 넘겨준다.
	UpdateRect();
	CheckCollTile();
}

void AActor::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}

void AActor::SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed)
{
	m_tFrame.fMin = fFrameMin;
	m_tFrame.fFrame = fFrameMin;
	m_tFrame.fCount = (fFrameMax - fFrameMin) * fFrameSpeed;
	m_tFrame.fMax = fFrameMax;
}

void AActor::UpdateRect()
{
	int iSceneLeft = m_tScene.iFrame * m_iImageX;
	int iSceneTop = m_tScene.iScene * m_iImageY;
	int iSceneRight = m_tScene.iFrame * m_iImageX + m_iImageX;
	int iSceneBottom = m_tScene.iScene * m_iImageY + m_iImageY;

	m_tRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}

void AActor::RenderShadow(BYTE Alpha)
{
	D3DXMATRIX matShadow, matRotZ;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-40.f));

	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;
	if (false == m_bFlipX)
		D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom * 0.7f, 1.f);
	else
		D3DXMatrixScaling(&matScale, -fScreenZoom, fScreenZoom * 0.7f, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x - 10.f
		, m_tInfo.vPosition.y + vScroll.y - 5.f
		, 0.f);

	matShadow = matScale * matRotZ * matTrans;

	m_pSprite->SetTransform(&matShadow);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(Alpha, 0, 0, 0));
}

void AActor::RenderFlyChar()
{

}

void AActor::RenderGroundChar()
{
	Vector3 vScroll = ViewMgr->GetScroll();

	D3DXMATRIX matScale, matTrans;

	if (false == m_bFlipX)
		D3DXMatrixScaling(&matScale, fScreenZoom, fScreenZoom, 1.f);
	else
		D3DXMatrixScaling(&matScale, -fScreenZoom, fScreenZoom, 1.f);

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPosition.x + vScroll.x
		, m_tInfo.vPosition.y + vScroll.y
		, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_pTexTint->pTexture
		, &m_tRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, *m_TeamColor);
}

void AActor::UpdateFlipX()
{
	if (m_tInfo.vDir.x > 0.f)
		m_bFlipX = false;
	else if (m_tInfo.vDir.x < 0.f)
		m_bFlipX = true;
	else if(m_tInfo.vDir.y < 0.f)
		m_bFlipX = false;
	else if (m_tInfo.vDir.y > 0.f)
		m_bFlipX = true;
}

bool AActor::CheckEnemy(int iRange)
{
	VECCOLLTILE VecRange;
	m_pLevel->GetRange(VecRange, m_iTileIndex, iRange);
	
	m_pTarget = nullptr;

	for (auto& pTile : VecRange)
	{
		CGameObject* pObject = pTile->pGameObject;
		if (nullptr != pObject && pObject->GetTeamID() != m_eTeam
			&& pObject->GetTeamID() != TEAM_NEUTRAL)
		{
			m_pTarget = pTile;
			return true;
		}
	}

	return false;
}

void AActor::CheckCollTile()
{
	if(nullptr == m_pLevel)
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

	int m_iTemp = m_pLevel->GetTileIndex(m_tInfo.vPosition);

	if (m_iTileIndex != m_iTemp)
	{
		if (m_pLevel->GetCollTile(m_iTemp)->byOption != 0)
		{
			if(m_eObjectID == OBJ_PLAYER)
				m_tInfo.vPosition -= m_tInfo.vDir;
			return;
		}

		// 타일이 기억하는 오브젝트와 내가 같을 때만 null로 변경.
		if(m_pLevel->GetTileObject(m_iTileIndex) == this)
			m_pLevel->SetTileObject(m_iTileIndex, nullptr);

		if(nullptr == m_pLevel->GetTileObject(m_iTemp))
			m_pLevel->SetTileObject(m_iTemp, this);

		m_iTileIndex = m_iTemp;
	}

	if (nullptr == m_pLevel->GetTileObject(m_iTileIndex))
		m_pLevel->SetTileObject(m_iTileIndex, this);
}
