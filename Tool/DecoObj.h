#pragma once
class CDecoObj
{
public:
	CDecoObj();
	~CDecoObj();

public:
	void Update();
	void Render();
	void Release();

public:
	bool isCulling(const D3DXVECTOR3& vPos);

public:
	VECDECO m_vecDeco;

};

