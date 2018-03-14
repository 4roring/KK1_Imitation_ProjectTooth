#pragma once

class CLevel;
class CMainFrame;
class CToolManager :
	public CSingleton<CToolManager>
{
private:
	friend CSingleton;
	CToolManager();
	virtual ~CToolManager();
	CToolManager(const CToolManager&) = delete;
	CToolManager& operator=(CToolManager&) = delete;

public:
	HRESULT Initialize();
	void Release();

public:
	CLevel* GetLevel() const { return m_pLevel; }
	const D3DXVECTOR3 GetScroll() const { return m_vScroll; }
	const CMainFrame* GetMainFrame() const { return m_pMainFrame; }
	const float GetZoom() const { return m_fZoom; }
	bool GetCollTileRender() { return m_bCollTileRender; }
	
public:
	void SetScroll(D3DXVECTOR3& vScroll) { m_vScroll -= vScroll; }
	void SetZoom(float fZoom) { m_fZoom += fZoom; }
	void SetMainFrame(CMainFrame* pMainFrame) { m_pMainFrame = pMainFrame; }
	void SetCollTileRender() { m_bCollTileRender = !m_bCollTileRender; }

private:
	CLevel* m_pLevel = nullptr;
	CMainFrame* m_pMainFrame = nullptr;

private:
	D3DXVECTOR3 m_vScroll = {};
	float m_fZoom = 0.f;
	bool m_bCollTileRender = false;
};

#define ToolMgr CToolManager::GetInstance() 