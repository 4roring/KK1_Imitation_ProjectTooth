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
//	void GetRange(VECCOLLTILE& rVecRange, int iStart); // ������� Ÿ�� ��Ÿ� 1
	void GetRange(VECCOLLTILE& rVecRange, int iStart, int iRange);
	// ���ϴ� ������ ���� Ÿ���� ��ȣ�� �����´�.
	int GetNeighborTileIndex(int iNeighbor, int iStart);
	// ���ϴ� ������ ���� Ÿ���� ��ȣ�� ���ϴ� ���̸�ŭ ���� �����´�.
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

