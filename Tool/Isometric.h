#pragma once
class CToolView;
class CIsometric
{
public:
	CIsometric();
	~CIsometric();

public: 
	HRESULT Initialize();
	void Update();
	void Render();
	void Release();

public:
	void MiniMap();
	bool isCulling(const D3DXVECTOR3& vPos);

public: // Tile Picking
	D3DXVECTOR3 GetMousePos();
	int GetTileIndex(D3DXVECTOR3 vPos);
	void Picking();
	void TileChange();

public:
	const VECISOTILE* GetIsoTileList() const { return &m_vecIsoTile; }

public:
	void SetMainView(CToolView* pMainView) { m_pMainView = pMainView; }

private:
	VECISOTILE m_vecIsoTile;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;
	CToolView* m_pMainView = nullptr;

private:
	BYTE m_byOption = 0;
	BYTE m_byDrawID = 0;
	int m_iPickIndex = 0;
};

