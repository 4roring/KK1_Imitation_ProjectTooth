#pragma once
class CToolView;
class CLevel
{
public:
	CLevel();
	~CLevel();

public: 
	HRESULT Initialize();
	void Update();
	void Render();
	void Release();

public:
	void CollTileRelease();
	void DecoRelease();

public:
	void MiniMap();
	bool isCulling(const Vector3& vPos);

public:
	void MapRender(float& fZoom, Vector3& vScroll, D3DXMATRIX& matScale);
	void CollTileRender(float& fZoom, Vector3& vScroll, D3DXMATRIX& matScale);
	void DecoRender(float& fZoom, Vector3& vScroll, D3DXMATRIX& matScale);
	void InfoRender();

public: // Tile Picking
	Vector3 GetMousePos();
	int GetTileIndex(Vector3 vPos);
	void Picking();
	void TileChange();
	void InsertDeco();

public:
	VECCOLLTILE* GetVecCollTile(){ return &m_vecCollTile; }
	VECDECO* GetVecDeco(){ return &m_vecDeco; }

public:
	void SetMainView(CToolView* pMainView) { m_pMainView = pMainView; }

public:
	void SetOption(BYTE byOptoin) { m_byOption = m_byDrawID = byOptoin; }
	void SetTileMode(bool bMode) { m_bTileMode = bMode; }
	void SetItem(const DECO* pItem) { m_pItem = pItem; }
	void SetFileMode(bool bFileMode) { m_bFileMode = bFileMode; }

private:
	VECCOLLTILE m_vecCollTile;
	VECDECO m_vecDeco;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;
	CToolView* m_pMainView = nullptr;
	const DECO* m_pItem = nullptr;

private:
	BYTE m_byOption = 0;
	BYTE m_byDrawID = 0;
	int m_iPickIndex = 0;
	bool m_bTileMode = false;
	bool m_bFileMode = false;
};

