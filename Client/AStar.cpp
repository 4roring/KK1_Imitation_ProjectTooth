#include "stdafx.h"
#include "Astar.h"
#include "Level.h"

CAStar::CAStar()
{
}


CAStar::~CAStar()
{

}

void CAStar::AStarStart(int iStart, const COLLTILE * pGoal, VECCOLLTILE& rVecPath)
{
	if (nullptr == m_pLevel)
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).front());

	m_iStart = iStart;

	m_iGoal = m_pLevel->GetTileIndex(pGoal->vPosition);

	if (pGoal->byOption != 0)
		m_iGoal = m_pLevel->GetNeighborTileIndex(GameMgr->GetRandom(0, NEIGHBOR_END - 1), m_iGoal, 2);

	if (m_iStart == m_iGoal)
		return;

	rVecPath.clear();
	ReleaseList();

	m_Thread = std::thread(
		[&]() 
	{ 
		m_Mutex.lock();
		MakeRoute(rVecPath); 
		m_Mutex.unlock();
	});

	if(true == m_Thread.joinable())
		m_Thread.join();
	
	//MakeRoute(rVecPath);
}

void CAStar::MakeRoute(VECCOLLTILE& rVecPath)
{
	ASTARNODE* pParentNode = new ASTARNODE;
	pParentNode->pParent = nullptr;
	pParentNode->iIndex = m_iStart;
	pParentNode->fCost = 0.f;

	m_CloseList.push_back(pParentNode);

	while (true)
	{
		for (int i = 0; i < NEIGHBOR_END; ++i)
		{
			int iIndex = m_pLevel->GetNeighborTileIndex(i, pParentNode->iIndex);

			if (false == CheckTileIndex(iIndex))
				continue;

			ASTARNODE* pNode = MakeNode(iIndex, pParentNode);
			m_OpenList.push_back(pNode);
		}

		m_OpenList.sort([](auto& p1, auto& p2){ return p1->fCost < p2->fCost; });

		pParentNode = m_OpenList.front();

		if (pParentNode->iIndex == m_iGoal)
			break;

		m_OpenList.pop_front();
		m_CloseList.push_back(pParentNode);
	}
	
	while (nullptr != pParentNode->pParent)
	{
		rVecPath.push_back(m_pLevel->GetCollTile(pParentNode->iIndex));
		pParentNode = pParentNode->pParent;
	}
	ReleaseList();
}

void CAStar::ReleaseList()
{
	std::for_each(m_OpenList.begin(), m_OpenList.end(), SafeDelete<ASTARNODE*>);
	m_OpenList.clear();
	std::for_each(m_CloseList.begin(), m_CloseList.end(), SafeDelete<ASTARNODE*>);
	m_CloseList.clear();
}

bool CAStar::CheckTileIndex(int iIndex)
{
	if (iIndex < 0 || iIndex > COLLTILEX * COLLTILEY - 1)
		return false;

	if (m_pLevel->GetCollTile(iIndex)->byOption == 1)
		return false;

	//if (nullptr != m_pLevel->GetTileObject(iIndex))
	//	return false;

	if (false == m_OpenList.empty())
	{
		auto iterOpen = std::find_if(m_OpenList.begin(), m_OpenList.end(), [iIndex](auto& pNode) {return (pNode->iIndex == iIndex); });
		if (iterOpen != m_OpenList.end()) return false;
	}
	
	if (false == m_CloseList.empty())
	{
		auto iterClose = std::find_if(m_CloseList.begin(), m_CloseList.end(), [iIndex](auto& pNode) {return (pNode->iIndex == iIndex); });
		if (iterClose != m_CloseList.end()) return false;
	}
	
	return true;
}

ASTARNODE* CAStar::MakeNode(int iIndex, ASTARNODE* pParent)
{
	ASTARNODE* pNode = new ASTARNODE;
	Vector3 vParent = m_pLevel->GetCollTile(pParent->iIndex)->vPosition;
	Vector3 vPos = m_pLevel->GetCollTile(iIndex)->vPosition;
	Vector3 vGoal = m_pLevel->GetCollTile(m_iGoal)->vPosition;

	float fG = D3DXVec3Length(&(vPos - vParent));
	float fH = D3DXVec3Length(&(vGoal - vPos));

	pNode->fCost = fG + fH;
	pNode->iIndex = iIndex;
	pNode->pParent = pParent;

	return pNode;
}
