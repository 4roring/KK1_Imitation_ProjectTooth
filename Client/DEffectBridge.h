#pragma once
#include "DBridge.h"

class CEffect;
class DEffectBridge :
	public DBridge
{
public:
	DEffectBridge();
	virtual ~DEffectBridge();

	// DBridge을(를) 통해 상속됨
	virtual HRESULT Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() override;
	virtual void Release() PURE;

public:
	void SetEffect(CEffect* pEffect) { m_pEffect = pEffect; }
	void SetBulletID(BULLETID eBulletID) { m_eBulletID = eBulletID; }
	void SetParticleID(PARTICLEID eParticleID) { m_eParticleID = eParticleID; }
	void SetTarget(COLLTILE* pTile) { m_pTarget = pTile; }

protected:
	BULLETID m_eBulletID = BULLET_END;
	PARTICLEID m_eParticleID = PARTICLE_END;
	CEffect* m_pEffect = nullptr;
	COLLTILE* m_pTarget = nullptr;

private:
	const TEXINFO* m_pTexMain = nullptr;
};

