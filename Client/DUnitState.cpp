#include "stdafx.h"
#include "DUnitState.h"
#include "AUnit.h"
#include "Level.h"

DUnitState::DUnitState()
{
}


DUnitState::~DUnitState()
{
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

void DUnitState::SetPath(decltype(m_vecPath)& vecPath)
{
	m_vecPath.clear();
	m_vecPath.assign(vecPath.begin(), vecPath.end());
}

void DUnitState::MovePath(float deltaTime)
{
	INFO& rInfo = m_pUnit->m_tInfo;
	Vector3 vTarget = Vector3(0.f, 0.f, 0.f);

	vTarget = m_vecPath.back()->vPosition - rInfo.vPosition;
	D3DXVec3Normalize(&rInfo.vDir, &vTarget);


	rInfo.vPosition += rInfo.vDir * m_pUnit->m_fSpeed * deltaTime;

	if (D3DXVec3Length(&vTarget) < 2.f)
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

	return vecCollTile.front();
}

