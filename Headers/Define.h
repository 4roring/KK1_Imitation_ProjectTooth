#pragma once

#define WINCX 1024
#define WINCY 768

// Tool, Client 공용 매니저 매크로 
// 전용 매크로는 각 프로젝트 내의 매니저에서 매크로 정의
#define GameMgr CGameManager::GetInstance() 
#define KeyMgr CKeyManager::GetInstance()
#define Device CDevice::GetInstance()
#define TextureMgr CTextureManager::GetInstance()

#define MSG_BOX(text) MessageBox(NULL, text, TEXT("System Message"), MB_OK);




