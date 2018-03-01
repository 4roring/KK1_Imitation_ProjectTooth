#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vDir;
	D3DXMATRIX matWorld;
}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImageInfo;
}TEXINFO;

typedef struct tagAnimFrame
{
	float fMin, fFrame, fCount, fMax;
}ANIMFRAME;

typedef struct tagAnimScene
{
	float fSceneMax;
	int iMaxFrame;
	int iScene, iFrame;
}ANIMSCENE;

