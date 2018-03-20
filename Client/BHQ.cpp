#include "stdafx.h"
#include "BHQ.h"
#include "Level.h"
#include "Effect.h"
#include "DOneShotEffectBridge.h"

BHQ::BHQ()
{
}


BHQ::~BHQ()
{
	Release();
}

HRESULT BHQ::Initialize()
{
	BBuilding::Initialize();

	m_eLayer = LAYER_OBJ;
	
	if (FAILED(SetTexture()))
		return E_FAIL;

	m_iImageCX = WINDMILL_CX;
	m_iImageCY = WINDMILL_CY;

	m_tFrame.fCenterX = (float)(m_iImageCX >> 1);
	m_tFrame.fCenterY = (float)m_iImageCY * 0.9f;

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 16;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_tWindmillScene.iFrame = 0;
	m_tWindmillScene.iMaxFrame = 16;
	m_tWindmillScene.iScene = 0;
	m_tWindmillScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_iMaxHp = 100;
	m_iHp = m_iMaxHp;

	InitHpUI();
	return S_OK;
}

OBJSTATE BHQ::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
	{
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

		for (int iTileNum : m_iTileIndexArr)
		{
			m_pLevel->GetCollTile(iTileNum)->pGameObject = this;
			m_pLevel->GetCollTile(iTileNum)->byDrawID = 1;
			m_pLevel->GetCollTile(iTileNum)->byOption = 1;
		}
		m_iTileIndex = m_iTileIndexArr[0];
		Vector3 vPos = m_pLevel->GetCollTile(m_iTileIndexArr[0])->vPosition;
		m_tInfo.vPosition = Vector3(vPos.x, vPos.y, 0.f);
	}
	BBuilding::Update(deltaTime);
	UpdateState(deltaTime);
	return STATE_PLAY;
}

void BHQ::LateUpdate()
{
	BBuilding::LateUpdate();
	UpdateWindmillRect();
	SetAnimState();
}

void BHQ::Render()
{
	BBuilding::Render();
	if(m_eCurState != BHQ::Dead)
		WindmillRender();
}

void BHQ::Release()
{
}

void BHQ::UpdateState(float deltaTime)
{
	if (m_iHp <= 0 && m_eCurState != BHQ::Dead)
	{
		// TODO: HQ 터지는 이펙트 
		// 이펙트 터지고 Dead로 상태 변환.
		m_eCurState = BHQ::Dead;
		CGameObject* pExplosion = DObjectFactory<CEffect>::CreateOneShotParticle(PARTICLE_EXPLOSION, m_tInfo.vPosition);
		GameMgr->CreateObject(pExplosion, OBJ_EFFECT);
	}

	switch (m_eCurState)
	{
	case BHQ::Build:
		if (m_tFrame.fFrame >= 95.5f)
		{
			WindmillFrameMove(deltaTime);
			m_tFrame.fFrame = 95.5f;
		}
			
		// TODO: 만들어지는 동안의 이펙트!
		if (m_tWindmillFrame.fFrame >= 42.5f)
		{
			// TODO: 완성 이펙트!
			m_bFirstBuild = true;
			m_eCurState = BHQ::Idle;

			// 주변 팜들의 팀을 자신의 팀으로!
			for (int i = 0; i < 8; ++i)
			{
				int iFramIndex = m_pLevel->GetNeighborTileIndex(i, m_iTileIndexArr[0], 2);
				m_pLevel->GetTileObject(iFramIndex)->SetTeam(m_eTeam);
			}
		}
		if (m_bDestroy)
		{
			if (false == m_bFirstBuild)
			{
				// 고기는 돌려주고 중립 HQ 소환!
			}
			else
			{
				// 고기는 돌려주고 Dead로 다시 변환.
			}
		}
		break;
	case BHQ::Idle:
	case BHQ::Sawing:
	case BHQ::Meat1:
	case BHQ::Meat2:
		WindmillFrameMove(deltaTime);

		// Idle에서 확률적으로 Sawing갔다가 Meat1, 2중 랜덤하게 재생.
		break;
	case BHQ::Dead:
		if (true == m_bDestroy)
		{
			// TODO: 이펙트 펑
			m_eCurState = BHQ::ReBuild;
		}

		break;
	case BHQ::ReBuild:
		if (m_tFrame.fFrame >= 211.5f)
		{

		}
		break;
	case BHQ::End:
	default:
		break;
	}
}

void BHQ::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BHQ::Build:
			SetAnimFrame(0.f, 96.f, 0.1f);
			SetWindmillAnimFrame(0.f, 43.f, 0.25f);
			break;
		case BHQ::Idle:
			SetAnimFrame(96.f, 97.f, 1.f);
			SetWindmillAnimFrame(44.f, 105.f, 0.2f);
			break;
		case BHQ::Sawing:
			SetAnimFrame(96.f, 142.f, 0.2f);
			break;
		case BHQ::Meat1:
			SetAnimFrame(143.f, 166.f, 0.2f);
			break;
		case BHQ::Meat2:
			SetAnimFrame(166.f, 203.f, 0.2f);
			break;
		case BHQ::Dead:
			SetAnimFrame(207.f, 207.f, 0.2f);
			SetWindmillAnimFrame(0.f, 0.f, 0.2f);
			break;
		case BHQ::ReBuild:
			SetAnimFrame(208.f, 212.f, 0.2f);
			SetWindmillAnimFrame(0.f, 0.f, 0.2f);
			break;
		case BHQ::End:
		default:
#ifdef _DEBUG
			assert(!"Farm AnimState Error(defalut or End");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void BHQ::WindmillFrameMove(float deltaTime)
{
	m_tWindmillFrame.fFrame += m_tWindmillFrame.fCount * deltaTime;
	if (m_tWindmillFrame.fFrame > m_tWindmillFrame.fMax)
		m_tWindmillFrame.fFrame = m_tWindmillFrame.fMin;

	m_tWindmillScene.iScene = int(m_tWindmillScene.fSceneMax * m_tWindmillFrame.fFrame);
	m_tWindmillScene.iFrame = int(m_tWindmillFrame.fFrame - m_tWindmillScene.iMaxFrame * m_tWindmillScene.iScene);
}

void BHQ::SetWindmillAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed)
{
	m_tWindmillFrame.fMin = fFrameMin;
	m_tWindmillFrame.fFrame = fFrameMin;
	m_tWindmillFrame.fCount = (fFrameMax - fFrameMin) * fFrameSpeed;
	m_tWindmillFrame.fMax = fFrameMax;
}

void BHQ::UpdateWindmillRect()
{
	int iSceneLeft = m_tWindmillScene.iFrame * m_iImageCX;
	int iSceneTop = m_tWindmillScene.iScene * m_iImageCY;
	int iSceneRight = m_tWindmillScene.iFrame * m_iImageCX + m_iImageCX;
	int iSceneBottom = m_tWindmillScene.iScene * m_iImageCY + m_iImageCY;

	m_tWindmillRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}

void BHQ::WindmillRender()
{
	m_pSprite->Draw(m_pWindmillTexMain->pTexture
		, &m_tWindmillRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_pWindmillTexTint->pTexture
		, &m_tWindmillRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, *m_TeamColor);
}

HRESULT BHQ::SetTexture()
{
	m_pTexMain = TextureMgr->GetTexture(TEXT("windmill_base"));
	m_pTexTint = TextureMgr->GetTexture(TEXT("windmill_base_tint"));
	if (nullptr == m_pTexMain || nullptr == m_pTexTint)
		return E_FAIL;

	m_pWindmillTexMain = TextureMgr->GetTexture(TEXT("windmill_topper"));
	m_pWindmillTexTint = TextureMgr->GetTexture(TEXT("windmill_topper_tint"));
	if (nullptr == m_pWindmillTexMain || nullptr == m_pWindmillTexTint)
		return E_FAIL;

	return S_OK;
}
