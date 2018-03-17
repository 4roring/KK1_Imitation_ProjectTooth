#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
	m_pSprite = Device->GetSprite();
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = Vector3(1.f, 0.f, 0.f);
}


CGameObject::~CGameObject()
{
}

