#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo;
	const TEXINFO* m_pTexMain;
	const TEXINFO* m_pTexTint;
};

