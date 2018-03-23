#pragma once

class CSoundManager :
	public CSingleton<CSoundManager>
{
public:
	enum ChannelID { BGM, PLAYER, EXPLOSION, NEAR_EFFECT, FAR_EFFECT, END };

private:
	friend CSingleton;
	explicit CSoundManager();
	virtual ~CSoundManager();
	CSoundManager(const CSoundManager&) = delete;
	CSoundManager& operator=(CSoundManager&) = delete;

public:
	HRESULT Initialize();
	HRESULT LoadSoundFile();
	void Update();
	void PlaySound(const std::wstring pSoundKey, ChannelID eChannel);
	void PlayEffectSound(const std::wstring pSoundKey, Vector3 vPos);
	void PlayBGM(const std::wstring pSoundKey);
	void StopSound(ChannelID eChannel);
	void StopAll();
	void Release();

public:
	bool CullNear(const Vector3& vPos);
	bool CullFar(const Vector3& vPos);

private:
	FMOD_SYSTEM* m_pSystem = nullptr;
	FMOD_CHANNEL* m_pChannelArr[END] = {};
	SOUNDMAP m_SoundMap;
};

#define SoundMgr CSoundManager::GetInstance()
