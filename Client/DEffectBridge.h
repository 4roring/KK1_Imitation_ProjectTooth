#pragma once
#include "DBridge.h"

class CEffect;
class DEffectBridge :
	public DBridge
{
public:
	DEffectBridge();
	virtual ~DEffectBridge();

public:
	virtual HRESULT Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	void SetEffect(CEffect* pEffect) { m_pEffect = pEffect; }
	void SetBulletID(BULLETID eBulletID) { m_eBulletID = eBulletID; }
	void SetParticleID(PARTICLEID eParticleID) { m_eParticleID = eParticleID; }
	void SetTarget(COLLTILE* pTile) { m_pTarget = pTile; }
	void SetAtk(int iAtk) { m_iAtk = iAtk; }
	void SetSize(float fSize) { m_fSize = fSize; }

protected:
	BULLETID m_eBulletID = BULLET_END;
	PARTICLEID m_eParticleID = PARTICLE_END;
	CEffect* m_pEffect = nullptr;
	COLLTILE* m_pTarget = nullptr;
	int m_iAtk = 0;
	float m_fSize = 0.f;

protected:
	const TEXINFO* m_pTexMain = nullptr;

};

