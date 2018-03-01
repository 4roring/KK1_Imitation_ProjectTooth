#pragma once

class CTimeManager :
	public CSingleton<CTimeManager>
{
public:
	CTimeManager();
	virtual ~CTimeManager();

public:
	const float& GetTime() { return m_fTime; }
	void InitTime();
	void SetTime();

private:
	LARGE_INTEGER m_FrameTime = {};
	LARGE_INTEGER m_FixTime = {};
	LARGE_INTEGER m_LastTime = {};
	LARGE_INTEGER m_CpuTick = {};

private:
	float m_fTime;
};

