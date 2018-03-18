#include "stdafx.h"
#include "DUnit_1Tear.h"
#include "AUnit.h"
#include "Level.h"
#include "DObserver.h"
#include "DSubject.h"
#include "AStar.h"

DUnit_1Tear::DUnit_1Tear()
{
}


DUnit_1Tear::~DUnit_1Tear()
{
	Release();
}

HRESULT DUnit_1Tear::Initialize()
{
	if (FAILED(SetUnitState()))
		return E_FAIL;

	m_pObserver = new DObserver;
	GameMgr->GetSubject(m_pUnit->m_eTeam)->Subscribe(m_pObserver);

	return S_OK;
}

void DUnit_1Tear::Update(float deltaTime)
{
	if (true == IsOrder())
		GetPath(m_pObserver->GetVecPath());

	UpdateState(deltaTime);
}

void DUnit_1Tear::LateUpdate()
{
	SetAnimState();
}

void DUnit_1Tear::UpdateState(float deltaTime)
{
	switch (m_eCurState)
	{
	case DUnit_1Tear::Idle:
		// 자신이 서있는 타일에 오브젝트가 존재하면 근처로 이동(생성직후)
		if (nullptr != GetTileIndexObject() && m_pUnit != GetTileIndexObject())
			m_vecPath.push_back(GetAroundEmptyTile());

		if (false == m_vecPath.empty())
			m_eCurState = DUnit_1Tear::Move;

		// 자신의 시야에 적이 있으면 이동(A*)
		if (true == CheckSight())
			GameMgr->GetAStar()->AStarStart(m_pUnit->m_iTileIndex, m_pUnit->m_pTarget, m_vecPath);
		
		// 자신의 공격범위에 적이 있으면 공격
		if (true == CheckRange())
			m_eCurState = DUnit_1Tear::Attack;

		break;
	case DUnit_1Tear::Move:
		/*if (true == CheckAroundBlockTile())
			GameMgr->GetAStar()->AStarStart(m_pUnit->m_iTileIndex, m_vecPath.front(), m_vecPath);*/
		MovePath(deltaTime);

		// 자신의 공격 범위에 적이 있으면 공격
		if (true == CheckRange())
		{
			if (nullptr != GetTileIndexObject() && m_pUnit != GetTileIndexObject())
				m_vecPath.push_back(GetAroundEmptyTile());
			else
				m_eCurState = DUnit_1Tear::Attack;
			break;
		}

		// 자신의 시야에 적이 있거나 타겟이 잡히면 타겟을 향해 이동
		if (true == CheckSight())
			GameMgr->GetAStar()->AStarStart(m_pUnit->m_iTileIndex, m_pUnit->m_pTarget, m_vecPath);

		if (true == m_vecPath.empty())
			m_eCurState = Idle;

		break;
	case DUnit_1Tear::Attack:
		m_vecPath.clear();
		m_fAttackDelay += deltaTime;

		switch (m_pUnit->m_eUnitID)
		{
			// 다람쥐는 초당 1공격
		case UNIT_SQUIRREL:
			if (m_fAttackDelay >= 1.f)
			{
				ShotBullet(BULLET_PISTOL);
				m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= 0.7f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;
			// TODO: 도마뱀과 두더지는 0.25의 대기 후 공격
		case UNIT_LIZARD:
			if (m_fAttackDelay >= 0.75f)
			{
				if(m_pUnit->m_tFrame.fFrame >= m_pUnit->m_tFrame.fMax - 0.5f)
				ShotBullet(BULLET_SPEAR);
				
				if (m_fAttackDelay >= 1.f)
					m_fAttackDelay = 0.f;
			}

			if (m_fAttackDelay <= 0.5f)
				m_pUnit->m_tFrame.fFrame = m_pUnit->m_tFrame.fMin;
			break;
		case UNIT_MOLE:

			break;
			// TODO: 두꺼비는 애니메이션 끝나면 자폭
		case UNIT_TOAD:
			break;
		}
		
		// TODO: 자신의 범위에 적이 없으면 Idle
		if (false == CheckRange())
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_1Tear::Idle;
		}
			
		if (m_pObserver->GetOrder() > 1.f)
		{
			m_fAttackDelay = 0.f;
			m_eCurState = DUnit_1Tear::Move;
		}
		break;
	case DUnit_1Tear::End:
	default:
#ifdef _DEBUG
		assert(!"Unit_1tear Anim Update Error!!!");
#endif
		break;
	}
}

void DUnit_1Tear::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case DUnit_1Tear::Idle:
			m_pUnit->SetAnimFrame(0.f, 3.f, 2.f);
			break;
		case DUnit_1Tear::Move:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_SQUIRREL:
				m_pUnit->SetAnimFrame(4.f, 8.f, 2.f);
				break;
			case UNIT_LIZARD:
			case UNIT_TOAD:
				m_pUnit->SetAnimFrame(4.f, 9.f, 2.f);
				break;
			case UNIT_MOLE:
				m_pUnit->SetAnimFrame(4.f, 11.f, 2.f);
				break;
			}
			break;
		case DUnit_1Tear::Attack:
			switch (m_pUnit->m_eUnitID)
			{
			case UNIT_SQUIRREL:
				m_pUnit->SetAnimFrame(9.f, 12.f, 2.f);
				break;
			case UNIT_LIZARD:
				m_pUnit->SetAnimFrame(10.f, 17.f, 2.f);
				break;
			case UNIT_TOAD:
				m_pUnit->SetAnimFrame(10.f, 20.f, 4.f);
				break;
			case UNIT_MOLE:
				m_pUnit->SetAnimFrame(12.f, 18.f, 2.f);
				break;
			}
			break;
		case DUnit_1Tear::End:
		default:
#ifdef _DEBUG
			assert(!"Unit_1tear Anim Update Error!!!");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

HRESULT DUnit_1Tear::SetUnitState()
{
	switch (m_pUnit->m_eUnitID)
	{
		// TODO: 유닛툴에서 만든 데이터 읽어오기. 또는 여기서 노가다?
	case UNIT_SQUIRREL:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("squirrel"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("squirrel_tint"));
		SetUnitInfo(m_pUnit->m_tUnitInfo, 8, 2, 1.f, 4, 4);

		m_pUnit->m_iImageX = 26;
		m_pUnit->m_iImageY = 26;

		m_pUnit->m_fSpeed = 100.f;

		break;
	case UNIT_LIZARD:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("lizard"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("lizard_tint"));
		
		SetUnitInfo(m_pUnit->m_tUnitInfo, 9, 3, 1.f, 2, 4);

		m_pUnit->m_iImageX = 32;
		m_pUnit->m_iImageY = 32;

		m_pUnit->m_fSpeed = 140.f;

		break;
	case UNIT_TOAD:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT(""));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT(""));
		break;
	case UNIT_MOLE:
		m_pUnit->m_pTexMain = TextureMgr->GetTexture(TEXT("mole"));
		m_pUnit->m_pTexTint = TextureMgr->GetTexture(TEXT("mole_tint"));
		break;
	default:
		MSG_BOX(TEXT("1Tear Unit Initialize Failed!!!"));
		return E_FAIL;
	}

	m_pUnit->m_tFrame.fCenterX = float(m_pUnit->m_iImageX >> 1);
	m_pUnit->m_tFrame.fCenterY = float(m_pUnit->m_iImageY * 0.9f);

	m_pUnit->m_tScene.iFrame = 0;
	m_pUnit->m_tScene.iMaxFrame = 8;
	m_pUnit->m_tScene.iScene = 0;
	m_pUnit->m_tScene.fSceneMax = 1.f / (float)m_pUnit->m_tScene.iMaxFrame;

	return S_OK;
}
