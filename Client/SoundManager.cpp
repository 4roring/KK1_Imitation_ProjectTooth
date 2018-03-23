#include "stdafx.h"
#include "SoundManager.h"
#include <io.h>
#include <filesystem>

namespace FileSystem = std::experimental::filesystem::v1;
static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

CSoundManager::CSoundManager()
{
	ZeroMemory(m_pChannelArr, sizeof(m_pChannelArr));
}


CSoundManager::~CSoundManager()
{
	Release();
}

HRESULT CSoundManager::Initialize()
{
	FMOD_RESULT res = FMOD_System_Create(&m_pSystem);
	if (res != FMOD_OK)
	{
		MSG_BOX(TEXT("FMOD System Create Failed"));
		return E_FAIL;
	}

	FMOD_System_Init(m_pSystem, END, FMOD_INIT_NORMAL, nullptr);
	
	if (FAILED(LoadSoundFile()))
	{
		MSG_BOX(TEXT("SoundFile Load Failed!!!"));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CSoundManager::LoadSoundFile()
{
	FileSystem::path FindFile(TEXT("../Sound"));
	
	if (false == FileSystem::is_directory(FindFile))
		return E_FAIL;

	for (const auto& directory : FileSystem::directory_iterator(FindFile))
	{
		if (FileSystem::is_regular_file(directory.status()))
		{
			FindFile = directory.path();

			FMOD_SOUND* pSound = nullptr;
			FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem
				, converter.to_bytes(FindFile).c_str(), FMOD_HARDWARE
				, nullptr, &pSound);

			if (res == FMOD_OK)
			{
				auto& iter_find = m_SoundMap.find(FindFile.stem());
				if (iter_find != m_SoundMap.end())
				{
					FMOD_Sound_Release(pSound);
					continue;
				}
				m_SoundMap.emplace(FindFile.stem(), pSound);
			}
		}
	}

	//FindFile.clear();

	FMOD_System_Update(m_pSystem);

	return S_OK;
}

void CSoundManager::Update()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlaySound(const std::wstring pSoundKey, ChannelID eChannel)
{
	auto iter_find = m_SoundMap.find(pSoundKey);

	if (iter_find == m_SoundMap.end())
	{
		MSG_BOX(TEXT("Sound File Not Found"));
		return;
	}
		
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &m_pChannelArr[eChannel]);
}

void CSoundManager::PlayEffectSound(const std::wstring pSoundKey,  Vector3 vPos)
{
	auto iter_find = m_SoundMap.find(pSoundKey);
	
	if (iter_find == m_SoundMap.end())
	{
		MSG_BOX(TEXT("Sound File Not Found"));
		return;
	}
	
	Vector3 vScroll = ViewMgr->GetScroll();

	if(true == CullNear(vPos + vScroll))
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
			iter_find->second, FALSE, &m_pChannelArr[NEAR_EFFECT]);
	else if (true == CullFar(vPos + vScroll))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
			iter_find->second, FALSE, &m_pChannelArr[FAR_EFFECT]);

		FMOD_Channel_SetVolume(m_pChannelArr[FAR_EFFECT], 0.5f);
	}
		
}

void CSoundManager::PlayBGM(const std::wstring pSoundKey)
{
	auto iter_find = m_SoundMap.find(pSoundKey);

	if (iter_find == m_SoundMap.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &m_pChannelArr[BGM]);

	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
}

void CSoundManager::StopSound(ChannelID eChannel)
{
	FMOD_Channel_Stop(m_pChannelArr[eChannel]);
}

void CSoundManager::StopAll()
{
	for (auto& pChannel : m_pChannelArr)
		FMOD_Channel_Stop(pChannel);
}

void CSoundManager::Release()
{
	for (auto& pair : m_SoundMap)
		FMOD_Sound_Release(pair.second);
	
	m_SoundMap.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

bool CSoundManager::CullNear(const Vector3& vPos)
{
	if (vPos.x < 200.f || vPos.x > WINCX - 200.f) return false;
	if (vPos.y < 140.f || vPos.y > WINCY - 140.f) return false;
	
	return true;
}

bool CSoundManager::CullFar(const Vector3& vPos)
{
	if (vPos.x < -100.f || vPos.x > WINCX + 100.f) return false;
	if (vPos.y < -100.f || vPos.y > WINCY + 100.f) return false;

	return true;
}
