#pragma once

class CGameObject;
class CActor;
class CBuilding;
template <typename T>
class DObjectFactory
{
public:
	static CGameObject* Create()
	{
		CGameObject* pObject = new T;
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* Create(Vector3 vPos)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(vPos);

		return pObject;
	}

	static CGameObject* Create(Vector3 vPos, TEAMID eTeam)
	{
		CGameObject* pObject = new T;
		pObject->SetPos(vPos);
		pObject->SetTeam(eTeam);
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateFarm(int iStart, TEAMID eTeam)
	{
		CBuilding* pObject = new T;
		pObject->SetTileIndexArray(iStart);
		pObject->SetTeam(eTeam);
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateDeco(const std::wstring& wstrObjKey, const std::wstring& wstrStateKey, int iCount, const Vector3& vPos)
	{
		CGameObject* pObject = new T;
		pObject->SetPos(vPos);
		pObject->SetTexMain(TextureMgr->GetTexture(wstrObjKey, wstrStateKey, iCount));
		pObject->Initialize();

		return pObject;
	}

	
};