#include "stdafx.h"
#include "DUnitState.h"
#include "AUnit.h"
#include "Level.h"
#include "DObserver.h"
#include "DSubject.h"
#include "AStar.h"
#include "Effect.h"
#include "DBulletEffectBridge.h"

DUnitState::DUnitState()
{
}


DUnitState::~DUnitState()
{
}

void DUnitState::Release()
{
	GameMgr->GetSubject(m_pUnit->m_eTeam)->Subscribe(m_pObserver);
	SafeDelete(m_pObserver);
}

void DUnitState::SetUnitInfo(UNITINFO& rUnitInfo, int iMaxHp, int iAtk, float fAtkTime, int iRange, int iSight)
{
	rUnitInfo.iMaxHp = iMaxHp;
	rUnitInfo.iHp = iMaxHp;
	rUnitInfo.iAtk = iAtk;
	rUnitInfo.fAtkTime = fAtkTime;
	rUnitInfo.iRange = iRange;
	rUnitInfo.iSight = iSight;
}

void DUnitState::MovePath(float deltaTime)
{
	INFO& rInfo = m_pUnit->m_tInfo;
	Vector3 vTarget = Vector3(0.f, 0.f, 0.f);

	vTarget = m_vecPath.back()->vPosition - rInfo.vPosition;
	D3DXVec3Normalize(&rInfo.vDir, &vTarget);

	rInfo.vDir *= m_pUnit->m_fSpeed * deltaTime;
	rInfo.vPosition += rInfo.vDir;

	if (D3DXVec3Length(&vTarget) < 5.f)
		m_vecPath.pop_back();
}

CGameObject * DUnitState::GetTileIndexObject()
{
	return m_pUnit->m_pLevel->GetTileObject(m_pUnit->m_iTileIndex);
}

const Vector3 & DUnitState::GetTilePos(int iIndex)
{
	return m_pUnit->m_pLevel->GetCollTile(iIndex)->vPosition;
}

bool DUnitState::CheckTileEmpty()
{
	if (nullptr == GetTileIndexObject())
		return true;

	return false;
}

bool DUnitState::IsOrder()
{
	if (m_pObserver->GetOrder() == 0.f) return false;
	if (m_pUnit->m_eUnitID == m_pObserver->GetOrderID())
	{
		m_vecPath.clear();
		return true;
	}
	else if (m_pObserver->GetOrderID() == UNIT_ALL)
	{
		m_vecPath.clear();
		return true;
	}

	return false;
}

bool DUnitState::CheckAroundBlockTile()
{
	VECCOLLTILE vecCollTile;
	int iStart = m_pUnit->m_iTileIndex;
	m_pUnit->m_pLevel->GetRange(vecCollTile, iStart);

	for (auto& pTile : vecCollTile)
		if (pTile->byOption == 1)
			return true;

	return false;
}

bool DUnitState::CheckSight()
{
	if (m_pObserver->GetOrder() > 1.f) return false;

	return (m_pUnit->CheckEnemy(m_pUnit->m_tUnitInfo.iSight));
}

bool DUnitState::CheckRange()
{
	if (m_pObserver->GetOrder() > 1.f) return false;

	return (m_pUnit->CheckEnemy(m_pUnit->m_tUnitInfo.iRange));
}

void DUnitState::ShotBullet(BULLETID eBulletID)
{
	CGameObject* pEffect = pEffect = DObjectFactory<CEffect>::CreateBullet(m_pUnit->m_pTarget, eBulletID, m_pUnit->m_tInfo.vPosition);
	GameMgr->CreateObject(pEffect, OBJ_EFFECT);
}

COLLTILE* DUnitState::GetAroundEmptyTile()
{
	VECCOLLTILE vecCollTile;
	int iStart = m_pUnit->m_iTileIndex;
	int iRange = 1;

	while (true == vecCollTile.empty())
	{
		m_pUnit->m_pLevel->GetRange(vecCollTile, iStart, iRange);

		for (auto iter = vecCollTile.begin(); iter != vecCollTile.end();)
		{
			if (nullptr != (*iter)->pGameObject || (*iter)->byOption == 1)
				iter = vecCollTile.erase(iter);
			else
				++iter;
		}
		++iRange;
	}

	std::random_shuffle(vecCollTile.begin(), vecCollTile.end());

	return vecCollTile.back();
}

void DUnitState::GetPath(const VECCOLLTILE vecPath)
{
	m_vecPath.clear();
	m_vecPath.assign(vecPath.begin(), vecPath.end());
}



