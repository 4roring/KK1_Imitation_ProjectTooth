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
	void MapRender(Vector3& vScroll, D3DXMATRIX& matScale);
	void CollTileRender(Vector3& vScroll, D3DXMATRIX& matScale);

public: // Tile Picking
	int GetTileIndex(Vector3 vPos);
//	void GetRange(VECCOLLTILE& rVecRange, int iStart); // 마름모꼴 타일 사거리 1
	void GetRange(VECCOLLTILE& rVecRange, int iStart, int iRange);
	// 원하는 방향의 인접 타일의 번호를 가져온다.
	int GetNeighborTileIndex(int iNeighbor, int iStart);
	// 원하는 방향의 인접 타일의 번호를 원하는 깊이만큼 들어가서 가져온다.
	int GetNeighborTileIndex(int iNeighbor, int iStart, int iCount);

public:
	void LoadCollTile();
	void CreateBuilding();
	void CreateFarm(int TileIndex, TEAMID eTeam);
	void CreateNeutralFarm(int TileIndex);
	void CreateTeamStartFarm(int TileIndex, TEAMID eTeam);


public:
	const VECCOLLTILE* GetVecCollTile() const { return &m_vecCollTile; }

private:
	VECCOLLTILE m_vecCollTile;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

private:
	int m_iPickIndex = 0;
	bool m_bTileRender = false;
};

