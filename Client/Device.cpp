#include "stdafx.h"
#include "Device.h"


CDevice::CDevice()
{
}


CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::InitDevice()
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));
	if (FAILED(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MessageBox(nullptr, L"GetDeviceCaps Failed", L"System Message", MB_OK);
		return E_FAIL;
	}

	DWORD vp;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	SetParameters(d3dpp);
	
	if (FAILED(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd
		, vp, &d3dpp, &m_pDevice)))
	{
		MessageBox(nullptr, L"Create Device Failed", L"System Message", MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MessageBox(nullptr, L"Create Sprite Failed", L"System Message", MB_OK);
		return E_FAIL;
	}

	if (FAILED(FontInit()))
	{
		MSG_BOX(TEXT("Create Font Failed"));
		return E_FAIL;
	}

	if (FAILED(FoodFontInit()))
	{
		MSG_BOX(TEXT("Create FoodFont Failed"));
		return E_FAIL;
	}

	if (FAILED(TitleFontInit()))
	{
		MSG_BOX(TEXT("Create FoodFont Failed"));
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::Begin()
{
	m_pDevice->Clear(0, nullptr
		, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET
		, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::End()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, g_hWnd, nullptr);
}

void CDevice::Draw(const D3DXMATRIX & matWorld)
{
	m_pSprite->SetTransform(&matWorld);
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;

	//d3dpp.Windowed = FALSE;
	d3dpp.Windowed = TRUE;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

HRESULT CDevice::FontInit()
{
	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));

	tFontInfo.Width = 8;
	tFontInfo.Height = 10;
	tFontInfo.Weight = FW_NORMAL;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, TEXT("����"));

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
		return E_FAIL;

	return S_OK;
}

HRESULT CDevice::FoodFontInit()
{
	AddFontResourceEx(TEXT("../Font/FFFFORWA.TTF"), FR_PRIVATE, 0);

	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));

	tFontInfo.Width = 24;
	tFontInfo.Height = 40;
	tFontInfo.Weight = FW_NORMAL;
	tFontInfo.CharSet = DEFAULT_CHARSET;
	lstrcpy(tFontInfo.FaceName, TEXT("FFF Forward"));

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFoodFont)))
		return E_FAIL;

	return S_OK;
}

HRESULT CDevice::TitleFontInit()
{
	AddFontResourceEx(TEXT("../Font/NanumSquareR.ttf"), FR_PRIVATE, 0);

	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));

	tFontInfo.Width = 24;
	tFontInfo.Height = 60;
	tFontInfo.Weight = FW_NORMAL;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, TEXT("����������"));

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pTitleFont)))
		return E_FAIL;

	return S_OK;
}

void CDevice::Release()
{
	SafeRelease(m_pTitleFont);
	SafeRelease(m_pFoodFont);
	SafeRelease(m_pFont);
	SafeRelease(m_pSprite);
	SafeRelease(m_pDevice);
	SafeRelease(m_pD3D9);
}
