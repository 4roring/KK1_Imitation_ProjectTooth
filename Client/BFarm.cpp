#include "stdafx.h"
#include "BFarm.h"
#include "Level.h"
#include "ACommander.h"
#include "Crop.h"
#include "APig.h"
#include "Effect.h"
#include "DExplosionEffectBridge.h"

BFarm::BFarm()
{
}


BFarm::~BFarm()
{
	Release();
}

HRESULT BFarm::Initialize()
{
	m_eLayer = LAYER_BACK;

	m_pTexMain = TextureMgr->GetTexture(TEXT("farmland"));

	m_iImageCX = FARM_CX;
	m_iImageCY = FARM_CY;

	m_tFrame.fCenterX = (float)(m_iImageCX >> 1);
	m_tFrame.fCenterY = (float)(m_iImageCY >> 1);

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 8;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_iMaxHp = 40;
	m_iHp = 0;

	m_iFood = 300;

	InitHpUI();
	return S_OK;
}

OBJSTATE BFarm::Update(float deltaTime)
{
	if (nullptr == m_pCommander && m_eTeam != TEAM_NEUTRAL)
		m_pCommander = GameMgr->GetCommander(m_eTeam);

	if (nullptr == m_pLevel)
		SetLevel();

	BBuilding::Update(deltaTime);
	UpdateState(deltaTime);

	return STATE_PLAY;
}

void BFarm::LateUpdate()
{
	BBuilding::LateUpdate();
	SetAnimState();

	if (m_eCurState == BFarm::Farm && m_iHp <= 0)
	{
		SoundMgr->PlayEffectSound(TEXT("Destroy_Small"), m_tInfo.vPosition);
		CGameObject* pExplosion = DObjectFactory<CEffect>::CreateExplosionEffect(PARTICLE_EXPLOSION, m_tInfo.vPosition, 0.5f);
		GameMgr->CreateObject(pExplosion, OBJ_EFFECT);
		DestroyPig();
		DestroyCropAll();
		RemoveTileObject();
		m_eCurState = BFarm::FarmEnd;
	}
}

void BFarm::Render()
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
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void BFarm::Release()
{
}

void BFarm::UpdateState(float deltaTime)
{
	switch (m_eCurState)
	{
	case BFarm::Grass:
		if (true == m_bDestroy)
		{
			// TODO: ¿Ã∆Â∆Æ ∆„!
			SoundMgr->PlayEffectSound(TEXT("Build_Farm"), m_tInfo.vPosition);
			m_fBuildTime = 100.f;
			m_bDestroy = false;
			m_eCurState = BFarm::OnStream;
			if (nullptr == m_pCommander)
				m_pCommander = GameMgr->GetCommander(m_eTeam);
			m_pCommander->SetFarmReserve(true);
		}
		break;
	case BFarm::OnStream:
		if (m_fBuildTime == 100.f)
		{
			if (m_pCommander->GetFood() >= 60)
			{
				m_pCommander->AddFood(-60);
				m_fBuildTime = 30.f;
				m_pCommander->SetFarmReserve(false);
			}
		}

		if (m_fBuildTime <= 30.f)
			m_fBuildTime -= deltaTime;

		if (m_fBuildTime < 0)
		{
			CreateFinished();
			m_eCurState = BFarm::Farm;
		}
		//if (true == m_bDestroy) // Farm Cancel¿∫ ¿Ãπ¯ πˆ¿¸ø°º≠ ªË¡¶.
		//{
		//	m_pCommander->AddFood(60);
		//	m_eCurState = BFarm::Grass;
		//	m_bDestroy = false;
		//}
		break;
	case BFarm::Farm:
		if (nullptr != m_pPig)
		{
			m_fFoodUpTime += deltaTime;
			if (m_fFoodUpTime >= 1.f)
			{
				m_pCommander->AddFood(2);
				--m_iFood;
				m_fFoodUpTime = 0.f;

				if (m_iFood % 34 == 0)
					DestroyCropRandom();
			}
		}
		
		if(m_iFood <= 0)
			m_eCurState = BFarm::FarmEnd;
		break;
	case BFarm::FarmEnd:
		DestroyPig();
		m_iHp = 0;
		break;
	case BFarm::End:
	default:
#ifdef _DEBUG
		assert(!"Farm AnimState Error(defalut or End");
#endif
		break;
	}
}

void BFarm::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BFarm::Grass: SetAnimFrame(12.f, 28.f, 1.f);
			break;
		case BFarm::OnStream: SetAnimFrame(2.f, 7.f, 1.3f);
			break;
		case BFarm::Farm: SetAnimFrame(0.f, 0.f, 0.f);
			break;
		case BFarm::FarmEnd: SetAnimFrame(11.f, 11.f, 0.f);
			break;
		case BFarm::End:
		default:
#ifdef _DEBUG
			assert(!"Farm AnimState Error(defalut or End)");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void BFarm::SetLevel()
{
	m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());
	for (int iTileNum : m_iTileIndexArr)
	{
		m_pLevel->SetTileObject(iTileNum, this);
		m_pLevel->GetCollTile(iTileNum)->byDrawID = 0;
		m_pLevel->GetCollTile(iTileNum)->byOption = 0;
	}
	m_iTileIndex = m_iTileIndexArr[0];
	Vector3 vPos = m_pLevel->GetCollTile(m_iTileIndexArr[0])->vPosition;
	m_tInfo.vPosition = Vector3(vPos.x, vPos.y - COLLTILECY, 0.f);

	if (m_eCurState == BFarm::Farm)
		CreateFinished();
}

void BFarm::SetCrop()
{
	for (int i = 0; i < 9; ++i)
	{
		const int idxX = i % 3;
		const int idxY = i / 3;
		constexpr int iCenterX = 1;
		constexpr int iCenterY = 1;
		constexpr float fMagicSize = 0.3333f;
		
		float fDistanceX = ((idxX - iCenterX) * fMagicSize - (idxY - iCenterY) * fMagicSize) * m_iImageCX;
		const float fDistanceY = ((idxX - iCenterX) * fMagicSize + (idxY - iCenterY) * fMagicSize) * m_iImageCY;
	
		Vector3 vPos(m_tInfo.vPosition.x + fDistanceX, m_tInfo.vPosition.y -15.f + fDistanceY, 0);

		CGameObject* pCrop = DObjectFactory<CCrop>::Create(vPos);
		GameMgr->CreateObject(pCrop, OBJ_FARM);
		m_pCrop[i] = pCrop;
	}
}

void BFarm::CreateFinished()
{
	// TODO: ¿Ã∆Â∆Æ ∆„! && µ≈¡ˆ µÓ¿Â! && ≥Û¿€π∞µµ µÓ¿Â
	SetCrop();
	m_iHp = m_iMaxHp;
	CGameObject* pPig = DObjectFactory<APig>::Create(m_tInfo.vPosition, m_eTeam);
	GameMgr->CreateObject(pPig, OBJ_FARM);
	dynamic_cast<APig*>(pPig)->SetTileIndexArr(m_iTileIndexArr);
	m_pPig = pPig;
}

void BFarm::DestroyCropRandom()
{
	while (true)
	{
		int iIndex = GameMgr->GetRandom(0, 8);
		if (nullptr != m_pCrop[iIndex])
		{
			m_pCrop[iIndex]->Destroy();
			m_pCrop[iIndex] = nullptr;
			break;
		}
	}
}

void BFarm::DestroyCropAll()
{
	for (int i = 0; i < 9; ++i)
	{
		if (nullptr != m_pCrop[i])
		{
			m_pCrop[i]->Destroy();
			m_pCrop[i] = nullptr;
		}
	}
}

void BFarm::DestroyPig()
{
	if (nullptr != m_pPig)
	{
		m_pPig->Destroy();
		m_pPig = nullptr;
	}
}

void BFarm::RemoveTileObject()
{
	for (int i : m_iTileIndexArr)
		m_pLevel->SetTileObject(i, nullptr);
}
