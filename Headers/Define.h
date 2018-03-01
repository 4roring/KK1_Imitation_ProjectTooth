#pragma once

#define WINCX 1280
#define WINCY 720

#define GameMgr CGameManager::GetInstance() 
#define GetKey CKeyManager::GetInstance()
#define Device CDevice::GetInstance()
#define TextureMgr CTextureManager::GetInstance()
#define Time CTimeManager::GetInstance()

#define MSG_BOX(text) MessageBox(NULL, text, TEXT("System Message"), MB_OK);