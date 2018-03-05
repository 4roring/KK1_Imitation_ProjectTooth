#pragma once
class CDevice
	: public CSingleton<CDevice>
{
public:
	CDevice();
	~CDevice();

public:
	HRESULT InitDevice();

public:
	void Begin();
	void End(HWND hWnd);

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPD3DXFONT GetFont() { return m_pFont; }

public:
	void Draw(const D3DXMATRIX& matWorld);

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	HRESULT FontInit();
	void Release();

private:
	LPDIRECT3D9 m_pD3D9 = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;
};

