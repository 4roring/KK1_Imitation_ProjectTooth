#pragma once

class CGameObject;
class CActor;
class CBuilding;
class BUnitFactory;

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
		CBuilding* pObject = new T;
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
		BUnitFactory* pObject = new T;
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
};