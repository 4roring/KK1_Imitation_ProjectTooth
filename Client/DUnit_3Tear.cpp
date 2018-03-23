#include "stdafx.h"
#include "DUnit_3Tear.h"
#include "AUnit.h"
#include "Level.h"
#include "DObserver.h"
#include "DSubject.h"
#include "AStar.h"

DUnit_3Tear::DUnit_3Tear()
{
}


DUnit_3Tear::~DUnit_3Tear()
{
}

HRESULT DUnit_3Tear::Initialize()
{
	if (FAILED(SetUnitState()))
		return E_FAIL;

	DUnitState::Initialize();

	return S_OK;
}

void DUnit_3Tear::Update(float deltaTime)
{
	if (true == IsOrder())
		GetPath(m_pObserver->GetVecPath());

	UpdateState(deltaTime);
}

void DUnit_3Tear::LateUpdate()
{
	SetAnimState();

	if (m_pUnit->m_iHp <= 0)
		m_eCurState = DUnit_3Tear::Dead;	
}

void DUnit_3Tear::UpdateState(float deltaTime)
{
	if (m_pUnit->m_eUnitID == UNIT_BADGER)
		BadgerPowerUpdate(deltaTime);

	switch (m_eCurState)
	{
	case DUnit_3Tear::Idle:
		// 자신이 서있는 타일에 오브젝트가 존재하면 근처로 이동
		if (nullptr != GetTileIndexObject() && m_pUnit != GetTileIndexObject())
			m_vecPath.push_back(GetAroundEmptyTile());

		if (false == m_vecPath.empty())
			m_eCurState = DUnit_3Tear::Move;

		//자신의 시야에 적이 있으면 적을 향해 이동
		if (true == CheckSight())
		{
			m_vecPath.clear();
			m_vecPath.push_back(m_pUnit->m_pTarget);
		}

		if (m_fMiniGunTime >= 2.f)
			m_fMiniGunTime = 0.f;

		// 자신의 공격범위에 적이 있으면 공격
		if (true == CheckRange())
			m_eCurState = DUnit_3Tear::Attack;
		break;
	case DUnit_3Tear::Move:
		MovePath(deltaTime);

		// 자신의 공격 범위에 적이 있으면 공격
		if (true == CheckRange())
			m_eCurState = DUnit_3Tear::Attack;

		// 자신의 시야에 적이 있거나 타겟이 잡히면 타겟을 향해 이동
		if (true == CheckSight())
		{
			m_vecPath.clear();
			m_vecPath.push_back(m_pUnit->m_pTarget);
		}

		if (true == m_vecPath.empty())
			m_eCurState = Idle;

		break;
	case DUnit_3Tear::Attack:
		m_vecPath.clear();
		m_fAttackDelay += deltaTime;

		switch (m_pUnit->m_eUnitID)
		{
		case UNIT_BADGER:
			if (m_fAttackDelay >= m_pUnit->m_tUnitInfo.fAtkTime)
			{
				SoundMgr->PlayEffectSound(TEXT("Unit_Badger_Attack"), m_pUnit->m_tInfo.vPosition);
				ShotBullet(BULLET_MINIGUN);
				m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= m_pUnit->m_tUnitInfo.fAtkTime - 0.1f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;
		case UNIT_BOAR:

			break;
		case UNIT_FOX:
			if (m_fAttackDelay >= m_pUnit->m_tUnitInfo.fAtkTime)
			{
				SoundMgr->PlayEffectSound(TEXT("Unit_Fox_Attack"), m_pUnit->m_tInfo.vPosition);
				ShotBullet(BULLET_SNIPER);
				m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= 1.7f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;
		case UNIT_WOLF:
			break;
		}

		if (false == CheckRange())
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_3Tear::Idle;

			if (m_fMiniGunTime >= 2.f && m_pUnit->m_eUnitID == UNIT_BADGER)
				m_fMiniGunTime = 0.f;
		}
		if (m_pObserver->GetOrder() > 1.f)
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_3Tear::Move;
			
			if (m_fMiniGunTime >= 2.f && m_pUnit->m_eUnitID == UNIT_BADGER)
				m_fMiniGunTime = 0.f;
		}
		break;
	case DUnit_3Tear::Dead:
		m_pUnit->m_iHp = 1;
		if (m_pUnit->m_tFrame.fFrame >= m_pUnit->m_tFrame.fMax - 0.3f)
		{
			m_pUnit->m_bDead = true;
			m_pUnit->m_iHp = 0;
		}
			
		break;
	case DUnit_3Tear::End:
	default:
#ifdef _DEBUG
		assert(!"Unit_1tear Anim Update Error!!!");
#endif
		break;
	}
}

void DUnit_3Tear::BadgerPowerUpdate(float deltaTime)
{
	m_fMiniGunTime += deltaTime;

	switch (m_eCurState)
	{
	case DUnit_3Tear::Idle:
		if (m_fMiniGunTime >= 2.f)
		{
			m_fMiniGunTime = 0.f;
			m_pUnit->m_tUnitInfo.fAtkTime = 0.5f;
		}
		break;
	case DUnit_3Tear::Move:
		if (m_fMiniGunTime >= 2.f)
		{
			m_fMiniGunTime = 0.f;
			m_pUnit->m_tUnitInfo.fAtkTime = 0.5f;
		}
		break;
	case DUnit_3Tear::Attack:
		if (m_fMiniGunTime >= 1.f)
		{
			m_fMiniGunTime = 0.f;
			m_pUnit->m_tUnitInfo.fAtkTime -= 0.1f;
			if (m_pUnit->m_tUnitInfo.fAtkTime < 0.1f)
				m_pUnit->m_tUnitInfo.fAtkTime = 0.1f;
		}
		break;
	case DUnit_3Tear::Dead:
	case DUnit_3Tear::End:
	default:
		break;
	}
}

void DUnit_3Tear::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case DUnit_3Tear::Idle:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_BADGER:
				m_pUnit->SetAnimFrame(0.f, 4.f, 2.f);
				break;
			case UNIT_BOAR:
				break;
			case UNIT_FOX:
				m_pUnit->SetAnimFrame(0.f, 7.f, 2.f);
				break;
			case UNIT_WOLF:
				break;
			}
			break;
		case DUnit_3Tear::Move:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_BADGER:
				m_pUnit->SetAnimFrame(5.f, 13.f, 2.f);
				break;
			case UNIT_BOAR:
				break;
			case UNIT_FOX:
				m_pUnit->SetAnimFrame(8.f, 15.f, 2.f);
				break;
			case UNIT_WOLF:
				break;
			}
			break;
		case DUnit_3Tear::Attack:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_BADGER:
				m_pUnit->SetAnimFrame(14.f, 17.f, 5.f);
				break;
			case UNIT_BOAR:
				break;
			case UNIT_FOX:
				m_pUnit->SetAnimFrame(16.f, 20.f, 2.5f);
				break;
			case UNIT_WOLF:
				break;
			}
			break;
		case DUnit_3Tear::Dead:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_BADGER:
				m_pUnit->SetAnimFrame(18.f, 39.f, 1.3f);
				break;
			case UNIT_BOAR:
				break;
			case UNIT_FOX:
				m_pUnit->SetAnimFrame(21.f, 39.f, 1.f);
				break;
			case UNIT_WOLF:
				break;
			}
			break;

		case DUnit_3Tear::End:
		default:
#ifdef _DEBUG
			assert(!"Unit_1tear Anim Update Error!!!");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

HRESULT DUnit_3Tear::SetUnitState()
{
	switch (m_pUnit->m_eUnitID)
	{
	case UNIT_BADGER:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("badger"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("badger_tint"));

		SetUnitInfo(m_pUnit->m_tUnitInfo, 60, 3, 0.5f, 4, 5);

		m_pUnit->m_iImageCX = 52;
		m_pUnit->m_iImageCY = 52;

		m_pUnit->m_fSpeed = 100.f;
		break;
	case UNIT_BOAR:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("boar"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("boar_tint"));
		break;
	case UNIT_FOX:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("fox"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("fox_tint"));

		SetUnitInfo(m_pUnit->m_tUnitInfo, 25, 24, 2.f, 5, 6);

		m_pUnit->m_iImageCX = 72;
		m_pUnit->m_iImageCY = 72;

		m_pUnit->m_fSpeed = 170.f;
		break;
	case UNIT_WOLF:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("snake"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("snake_tint"));
		break;
	default:
		MSG_BOX(TEXT("3Tear Unit Initialize Failed!!!"));
		return E_FAIL;
	}

	m_pUnit->m_tFrame.fCenterX = float(m_pUnit->m_iImageCX >> 1);
	m_pUnit->m_tFrame.fCenterY = float(m_pUnit->m_iImageCY * 0.9f);

	m_pUnit->m_tScene.iFrame = 0;
	m_pUnit->m_tScene.iMaxFrame = 8;
	m_pUnit->m_tScene.iScene = 0;
	m_pUnit->m_tScene.fSceneMax = 1.f / (float)m_pUnit->m_tScene.iMaxFrame;

	return S_OK;
}
