#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo;
	RECT m_tRect;
	const TEXINFO* m_pTexMain;
	const TEXINFO* m_pTexTint;
};

