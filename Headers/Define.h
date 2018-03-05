#pragma once

#define WINCX 1024
#define WINCY 768

#define GameMgr CGameManager::GetInstance() 
#define GetKey CKeyManager::GetInstance()
#define Device CDevice::GetInstance()
#define TextureMgr CTextureManager::GetInstance()

#define MSG_BOX(text) MessageBox(NULL, text, TEXT("System Message"), MB_OK);

// Client에서만 사용
#define Time CTimeManager::GetInstance()

