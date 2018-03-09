#pragma once
class CDevice
	: public CSingleton<CDevice>
{
	friend CSingleton;

private:
	CDevice();
	~CDevice();

public:
	HRESULT InitDevice();

public:
	void Begin();
	void End();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
public:
	void Draw(const D3DXMATRIX& matWorld);

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void Release();

private:
	LPDIRECT3D9 m_pD3D9 = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

	LPD3DXSPRITE m_pSprite = nullptr;
};

