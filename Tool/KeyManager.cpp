#include "stdafx.h"
#include "KeyManager.h"


CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKey, sizeof(m_bKey));
}


CKeyManager::~CKeyManager()
{
}
