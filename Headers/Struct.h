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
	float fCenterX, fCenterY;
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
	class CGameObject* pObj = nullptr; // Ÿ�Ͽ� �����ϴ� ������ �ּҸ� ����.
}COLLTILE;

typedef struct tagDecoration
{
	D3DXVECTOR3 vPosition;
	std::wstring wstrObjKey;
	std::wstring wstrStateKey;
	int iCount;
}DECO;

// ������ ���� ����
typedef struct tagTexturePath
{
	TEXTYPE eType;
	std::wstring wstrObjKey;
	std::wstring wstrStateKey;
	std::wstring wstrPath;
	int iCount;
}TEXPATH;