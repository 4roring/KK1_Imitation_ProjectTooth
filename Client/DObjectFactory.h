#pragma once

class CGameObject;
class AActor;
class AUnit;
class BBuilding;
class BUnitFactory;
class CEffect;
class DEffectBridge;
class DBulletEffectBridge;
class DOneShotEffectBridge;

template <typename T>
class DObjectFactory
{
public:
	static CGameObject* Create()
	{
		CGameObject* pObject = new T;
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create Deco Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* Create(Vector3 vPos)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(vPos);
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create GameObject Error!!!"));
			return nullptr;
		}
		return pObject;
	}

	static CGameObject* Create(Vector3 vPos, TEAMID eTeam)
	{
		CGameObject* pObject = new T;
		pObject->SetPos(vPos);
		pObject->SetTeam(eTeam);
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create GameObject Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* CreateBuilding(int iStart, TEAMID eTeam)
	{
		BBuilding* pObject = new T;
		pObject->SetTileIndexArray(iStart);
		pObject->SetTeam(eTeam);
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create Building Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* CreateUnitFactory(int iStart, UNITID eUnitID, TEAMID eTeam)
	{
		BUnitFactory* pObject = new BUnitFactory;
		pObject->SetTileIndexArray(iStart);
		pObject->SetUnitID(eUnitID);
		pObject->SetTeam(eTeam);

		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create UnitFactory Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* CreateUnit(int iStart, UNITID eUnitID, TEAMID eTeam, BUnitFactory* pFactory)
	{
		AUnit* pObject = new T;
		
		pObject->SetUnitID(eUnitID);
		pObject->SetTeam(eTeam);
		pObject->SetTileIndex(iStart);
		pObject->SetFactory(pFactory);
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create Unit Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* CreateDeco(const std::wstring& wstrObjKey, const std::wstring& wstrStateKey, int iCount, const Vector3& vPos)
	{
		CGameObject* pObject = new T;
		pObject->SetPos(vPos);
		pObject->SetTexMain(TextureMgr->GetTexture(wstrObjKey, wstrStateKey, iCount));
		if (FAILED(pObject->Initialize()))
		{
			MSG_BOX(TEXT("Create Deco Error!!!"));
			return nullptr;
		}

		return pObject;
	}

	static CGameObject* CreateBullet(COLLTILE* pTarget, BULLETID eBulletID, const Vector3& vPos, int iAtk)
	{
		CEffect* pEffect = new CEffect;
		DEffectBridge* pBulletEffect = new DBulletEffectBridge;
		pBulletEffect->SetBulletID(eBulletID);
		pBulletEffect->SetTarget(pTarget);
		pBulletEffect->SetAtk(iAtk);
		pEffect->SetEffectBridge(pBulletEffect);
		pEffect->SetPos(vPos);
		if (FAILED(pEffect->Initialize()))
		{
			MSG_BOX(TEXT("Create Bullet Effect Error!!!"));
			return nullptr;
		}
		
		return pEffect;
	}

	static CGameObject* CreateOneShotParticle(PARTICLEID eParticleID, const Vector3& vPos)
	{
		CEffect* pEffect = new CEffect;
		DEffectBridge* pOneShotEffect = new DOneShotEffectBridge;
		pOneShotEffect->SetParticleID(eParticleID);
		pEffect->SetEffectBridge(pOneShotEffect);
		pEffect->SetPos(vPos);
		if (FAILED(pEffect->Initialize()))
		{
			MSG_BOX(TEXT("Create Bullet Effect Error!!!"));
			return nullptr;
		}

		return pEffect;
	}
};