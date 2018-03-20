#include "stdafx.h"
#include "DUnit_2Tear.h"
#include "AUnit.h"
#include "Level.h"
#include "DObserver.h"
#include "DSubject.h"
#include "AStar.h"

DUnit_2Tear::DUnit_2Tear()
{
}


DUnit_2Tear::~DUnit_2Tear()
{
	Release();
}

HRESULT DUnit_2Tear::Initialize()
{
	if (FAILED(SetUnitState()))
		return E_FAIL;

	DUnitState::Initialize();

	return S_OK;
}

void DUnit_2Tear::Update(float deltaTime)
{
	if (true == IsOrder())
		GetPath(m_pObserver->GetVecPath());

	UpdateState(deltaTime);
}

void DUnit_2Tear::LateUpdate()
{
	SetAnimState();
}

void DUnit_2Tear::UpdateState(float deltaTime)
{
	switch (m_eCurState)
	{
	case DUnit_2Tear::Idle:
		// 자신이 서있는 타일에 오브젝트가 존재하면 근처로 이동
		if (nullptr != GetTileIndexObject() && m_pUnit != GetTileIndexObject())
			m_vecPath.push_back(GetAroundEmptyTile());

		if (false == m_vecPath.empty())
			m_eCurState = DUnit_2Tear::Move;

		//자신의 시야에 적이 있으면 적을 향해 이동
		if (true == CheckSight())
		{
			m_vecPath.clear();
			m_vecPath.push_back(m_pUnit->m_pTarget);
		}

		// 자신의 공격범위에 적이 있으면 공격
		if (true == CheckRange())
			m_eCurState = DUnit_2Tear::Attack;
		break;
	case DUnit_2Tear::Move:
		MovePath(deltaTime);

		// 자신의 공격 범위에 적이 있으면 공격
		if (true == CheckRange())
			m_eCurState = DUnit_2Tear::Attack;

		// 자신의 시야에 적이 있거나 타겟이 잡히면 타겟을 향해 이동
		if (true == CheckSight())
		{
			m_vecPath.clear();
			m_vecPath.push_back(m_pUnit->m_pTarget);
		}

		if (true == m_vecPath.empty())
			m_eCurState = Idle;

		break;
	case DUnit_2Tear::Attack:
		m_vecPath.clear();
		m_fAttackDelay += deltaTime;

		switch (m_pUnit->m_eUnitID)
		{
		case UNIT_FERRET:
			break;
		case UNIT_CHAMELEON:
			break;
		case UNIT_SKUNK:
			if (m_fAttackDelay >= m_pUnit->m_tUnitInfo.fAtkTime)
			{
				ShotBullet(BULLET_GRENADE);
				m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= 0.7f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;

		case UNIT_SNAKE:
			if (m_fAttackDelay >= m_pUnit->m_tUnitInfo.fAtkTime)
			{
				ShotBullet(BULLET_VENOM);
				m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= 0.7f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;
		}

		if (false == CheckRange())
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_2Tear::Idle;
		}
		if (m_pObserver->GetOrder() > 1.f)
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_2Tear::Move;
		}
		break;

	case DUnit_2Tear::End:
	default:
#ifdef _DEBUG
		assert(!"Unit_1tear Anim Update Error!!!");
#endif
			break;
	}
}

void DUnit_2Tear::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case DUnit_2Tear::Idle:
			m_pUnit->SetAnimFrame(0.f, 3.f, 2.f);
			break;
		case DUnit_2Tear::Move:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_FERRET:
				break;
			case UNIT_CHAMELEON:
				break;
			case UNIT_SKUNK:
			case UNIT_SNAKE:
				m_pUnit->SetAnimFrame(4.f, 11.f, 2.f);
				break;
			}
			break;
		case DUnit_2Tear::Attack:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_FERRET:
				break;
			case UNIT_CHAMELEON:
				break;
			case UNIT_SKUNK:
				m_pUnit->SetAnimFrame(12.f, 15.f, 2.f);
				break;
			case UNIT_SNAKE:
				m_pUnit->SetAnimFrame(12.f, 16.f, 2.f);
				break;
			}
			break;
		case DUnit_2Tear::End:
		default:
#ifdef _DEBUG
			assert(!"Unit_1tear Anim Update Error!!!");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

HRESULT DUnit_2Tear::SetUnitState()
{
	switch (m_pUnit->m_eUnitID)
	{
		// TODO: 유닛툴에서 만든 데이터 읽어오기. 또는 여기서 노가다?
	case UNIT_FERRET:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT(""));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT(""));
		break;
	case UNIT_CHAMELEON:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT(""));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT(""));
		break;
	case UNIT_SKUNK:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("skunk"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("skunk_tint"));

		SetUnitInfo(m_pUnit->m_tUnitInfo, 32, 5, 1.f, 4, 4);

		m_pUnit->m_iImageCX = 32;
		m_pUnit->m_iImageCY = 32;

		m_pUnit->m_fSpeed = 130.f;
		break;
	case UNIT_SNAKE:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("snake"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("snake_tint"));

		SetUnitInfo(m_pUnit->m_tUnitInfo, 35, 4, 1.f, 4, 4);

		m_pUnit->m_iImageCX = 30;
		m_pUnit->m_iImageCY = 30;

		m_pUnit->m_fSpeed = 160.f;
		break;
	default:
		MSG_BOX(TEXT("1Tear Unit Initialize Failed!!!"));
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
