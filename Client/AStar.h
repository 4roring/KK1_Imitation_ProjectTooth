#pragma once

class CLevel;
class CAStar
{
public:
	CAStar();
	~CAStar();

public:
	void AStarStart(int iStart, const COLLTILE* pGoal, VECCOLLTILE& rVecPath);

private:
	void MakeRoute(VECCOLLTILE& rVecCollTile);
	void ReleaseList();

private:
	bool CheckTileIndex(int iIndex);

private:
	CLevel* m_pLevel = nullptr;
	ASTARNODELIST m_OpenList;
	ASTARNODELIST m_CloseList;
	int m_iStart;
	int m_iGoal;

private:
	ASTARNODE* MakeNode(int iIndex, ASTARNODE* pParent);
	std::thread m_Thread;
	std::mutex m_Mutex;
};

