#pragma once

#define WINCX 1024
#define WINCY 768

// Tool, Client ���� �Ŵ��� ��ũ�� 
// ���� ��ũ�δ� �� ������Ʈ ���� �Ŵ������� ��ũ�� ����
#define GameMgr CGameManager::GetInstance() 
#define KeyMgr CKeyManager::GetInstance()
#define Device CDevice::GetInstance()
#define TextureMgr CTextureManager::GetInstance()

#define MSG_BOX(text) MessageBox(NULL, text, TEXT("System Message"), MB_OK);




