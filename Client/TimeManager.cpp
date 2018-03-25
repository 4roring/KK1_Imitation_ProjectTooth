#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager()
{
}


CTimeManager::~CTimeManager()
{
}

void CTimeManager::InitTime()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);

	m_iFixFrame = 90;

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart);
	m_fPerFrame = float(m_CpuTick.QuadPart / m_iFixFrame);
}

void CTimeManager::SetTime()
{
	while (true)
	{
		QueryPerformanceCounter(&m_FrameTime);
		m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart);

		if (m_fPerFrame < m_fTime)
		{
			m_fDeltaTime = float(m_fTime / m_CpuTick.QuadPart);
			m_FixTime = m_FrameTime;
			break;
		}
	}
		
	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}
}
