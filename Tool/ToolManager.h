#pragma once

class CIsometric;
class CMainFrame;
class CToolManager :
	public CSingleton<CToolManager>
{
public:
	CToolManager();
	virtual ~CToolManager();

public:
	HRESULT Initialize();
	void Release();

public:
	CIsometric* GetIsometric() const { return m_pIsometric; }
	const D3DXVECTOR3 GetScroll() const { return m_vScroll; }
	const float GetZoom() const { return m_fZoom; }
	const CMainFrame* GetMainFrame() const { return m_pMainFrame; }
	bool GetIsoRender() { return m_bIsoRender; }
	
public:
	void SetScroll(D3DXVECTOR3& vScroll) { m_vScroll -= vScroll; }
	void SetZoom(float fZoom) { m_fZoom += fZoom; }
	void SetMainFrame(CMainFrame* pMainFrame) { m_pMainFrame = m_pMainFrame; }
	void SetIsoRender() { m_bIsoRender = !m_bIsoRender; }

private:
	CIsometric* m_pIsometric = nullptr;
	CMainFrame* m_pMainFrame = nullptr;

private:
	D3DXVECTOR3 m_vScroll = {};
	float m_fZoom = 0.f;
	bool m_bIsoRender = false;
};

#define ToolMgr CToolManager::GetInstance() 