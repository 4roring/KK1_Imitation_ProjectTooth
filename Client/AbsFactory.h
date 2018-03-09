#pragma once

class CGameObject;

template <typename T>
class CAbsFactory
{
public:
	static CGameObject* Create()
	{
		CGameObject* pObject = new T;
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