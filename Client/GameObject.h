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
	virtual void ApplyDamage(int iDamage);

public:
	OBJLAYER GetLayer() const { return m_eLayer; }
	const INFO& GetInfo() const { return m_tInfo; }
	TEAMID GetTeamID() const { return m_eTeam; }
	OBJID GetObjectID() const { return m_eObjectID; }
	int GetTileIndex() const { return m_iTileIndex; }
	int GetHp() const { return m_iHp; }
	float GetHpRatio() const { return m_iHp / (float)m_iMaxHp; }

public:
	void SetPos(const Vector3& vPos) { m_tInfo.vPosition = vPos; }
	void SetTexMain(const TEXINFO* pTexInfo) { m_pTexMain = pTexInfo; }
	void SetObjectID(OBJID eObjectID) { m_eObjectID = eObjectID; }
	void SetTeam(TEAMID eTeamID) { m_eTeam = eTeamID; }
	void SetTileIndex(int iTileIndex) { m_iTileIndex = iTileIndex; }
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
	int m_iTileIndex = 0;
	int m_iMaxHp = 0;
	int m_iHp = 0;

protected:
	bool m_bDestroy = false;
};

