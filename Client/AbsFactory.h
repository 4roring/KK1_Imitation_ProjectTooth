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

};