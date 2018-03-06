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
	LPRECT tRect;
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

typedef struct tagCollisionTile
{
	D3DXVECTOR3 vPosition;
	BYTE byOption;
	BYTE byDrawID;
}COLLITILE;

typedef struct tagDecoration
{
	D3DXVECTOR3 vPosition;
	BYTE byDrawID;
}DECO;


// ÅøÀü¿ë
typedef struct tagTexturePath
{
	TEXTYPE eType;
	std::wstring wstrObjKey;
	std::wstring wstrStateKey;
	std::wstring wstrPath;
	int iCount;
}TEXPATH;