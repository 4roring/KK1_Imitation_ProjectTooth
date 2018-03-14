#pragma once
class CDevice
	: public CSingleton<CDevice>
{
private:
	friend CSingleton;
	explicit CDevice();
	virtual ~CDevice();
	CDevice(const CDevice&) = delete;
	CDevice& operator=(CDevice&) = delete;
public:
	HRESULT InitDevice();

public:
	void Begin();
	void End();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPD3DXFONT GetFont() { return m_pFont; }

public:
	void Draw(const D3DXMATRIX& matWorld);

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void Release();

private:
	HRESULT FontInit();

private:
	LPDIRECT3D9 m_pD3D9 = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;
};

