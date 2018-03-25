#pragma once

class CTimeManager :
	public CSingleton<CTimeManager>
{
private:
	friend CSingleton;
	explicit CTimeManager();
	virtual ~CTimeManager();
	CTimeManager(const CTimeManager&) = delete;
	CTimeManager& operator=(CTimeManager&) = delete;

public:
	const float& GetDeltaTime() { return m_fDeltaTime; }
	void InitTime();
	void SetTime();

private:
	LARGE_INTEGER m_FrameTime = {};
	LARGE_INTEGER m_FixTime = {};
	LARGE_INTEGER m_LastTime = {};
	LARGE_INTEGER m_CpuTick = {};

private:
	float m_fTime = 0.0f;
	float m_fPerFrame = 0.0f;
	float m_fDeltaTime = 0.f;
	int m_iFixFrame = 0;
};

#define Time CTimeManager::GetInstance()