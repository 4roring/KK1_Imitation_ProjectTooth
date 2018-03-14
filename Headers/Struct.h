#pragma once

class CGameObject;

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
	float fSceneMax;	// 1 / MaxFrame
	int iMaxFrame;		// Scene �� MaxFrame
	int iScene;			// ���� Scene ��ȣ
	int iFrame;			// ���� Frame ��ȣ
}ANIMSCENE;

typedef struct tagCollisionTile
{
	D3DXVECTOR3 vPosition;
	BYTE byOption;
	BYTE byDrawID;
	CGameObject* pGameObject; // Ÿ�Ͽ� �����ϴ� ������ �ּҸ� ��� ������
}COLLTILE;

typedef struct tagDecoration
{
	D3DXVECTOR3 vPosition;
	std::wstring wstrObjKey;
	std::wstring wstrStateKey;
	int iCount;
}DECO;

typedef struct tagUnitInfo
{
	int iMaxHp;
	int iHp;
	int iAtk;
	float fAtkTime;
	int iCount;
	int iSight;
	int iRange;
}UNITINFO;

// ������ ���� ����
typedef struct tagTexturePath
{
	TEXTYPE eType;
	std::wstring wstrObjKey;
	std::wstring wstrStateKey;
	std::wstring wstrPath;
	int iCount;
}TEXPATH;