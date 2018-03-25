#pragma once

#include "GameObject.h"

class CToolView;
class CLevel
	: public CGameObject
{
public:
	CLevel();
	virtual ~CLevel();

public: 
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	bool isCulling(const Vector3& vPos);
	
public:
	void MapRender(const Vector3& vScroll, const D3DXMATRIX& matScale);
	void CollTileRender(const Vector3& vScroll, const D3DXMATRIX& matScale);

public: // Tile Picking
	int GetTileIndex(const Vector3& vPos);
	void GetRange(VECCOLLTILE& rVecRange, int iStart);
	void GetRange(VECCOLLTILE& rVecRange, int iStart, int iRange);
	int GetNeighborTileIndex(int iNeighbor, int iStart);
	int GetNeighborTileIndex(int iNeighbor, int iStart, int iDepth);

public:
	void LoadCollTile();
	void CreateBuilding();
	void CreateFarm(int iTileIndex, TEAMID eTeamID);
	void CreateFinishedFarm(int iTileIndex, TEAMID eTeamID);
	void CreateNeutralFarm(int iTileIndex);
	void CreateTeamStartFarm(int iTileIndex, TEAMID eTeamID);
	void CreateTeamHQ(int iTileIndex, TEAMID eTeamID);

public:
	COLLTILE* GetCollTile(int iIndex) const { return m_vecCollTile[iIndex]; }
	CGameObject* GetTileObject(int iIndex) const { return m_vecCollTile[iIndex]->pGameObject; }

public:
	void SetTileObject(int iIndex, CGameObject* pObject) { m_vecCollTile[iIndex]->pGameObject = pObject; }

private:
	VECCOLLTILE m_vecCollTile;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

private:
	bool m_bTileRender = false;
};

