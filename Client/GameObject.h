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
	TEAMID GetTeamID() { return m_eTeam; }
	OBJID GetObjectID() { return m_eObjectID; }

public:
	void SetPos(Vector3 vPos) { m_tInfo.vPosition = vPos; }
	void SetTexMain(const TEXINFO* pTexInfo) { m_pTexMain = pTexInfo; }
	void SetObjectID(OBJID eObjectID) { m_eObjectID = eObjectID; }
	void SetTeam(TEAMID eTeam) { m_eTeam = eTeam; }
	void Destroy() { m_bDestroy = true; }

protected:
	LPD3DXSPRITE m_pSprite;
	class CLevel* m_pLevel = nullptr;

protected:
	INFO m_tInfo = {};
	const TEXINFO* m_pTexMain = nullptr;
	TEAMID m_eTeam = TEAM_END;
	OBJID m_eObjectID = OBJ_END;
	OBJLAYER m_eLayer = LAYER_END;

protected:
	bool m_bDestroy = false;
};

