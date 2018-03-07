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
	bool isCulling(const D3DXVECTOR3& vPos);
	
public:
	void MapRender(D3DXVECTOR3& vScroll);
	void CollTileRender(D3DXVECTOR3& vScroll);

public: // Tile Picking
	int GetTileIndex(D3DXVECTOR3 vPos);
	void Picking();

public:
	VECCOLLTILE* GetVecCollTile(){ return &m_vecCollTile; }

private:
	VECCOLLTILE m_vecCollTile;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;
	CToolView* m_pMainView = nullptr;

private:
	int m_iPickIndex = 0;
};

