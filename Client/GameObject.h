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

public:
	OBJLAYER GetLayer() { return m_eLayer; }
	const INFO& GetInfo() { return m_tInfo; }

public:
	void SetPos(Vector3 vPos) { m_tInfo.vPosition = vPos; }
	void SetTexMain(const TEXINFO* pTexInfo) { m_pTexMain = pTexInfo; }

protected:
	LPD3DXSPRITE m_pSprite;

protected:
	INFO m_tInfo = {};
	const TEXINFO* m_pTexMain = nullptr;
	OBJLAYER m_eLayer = LAYER_END;
};

