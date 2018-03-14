#pragma once

#define VIR_KEY 0xff

class CKeyManager :
	public CSingleton<CKeyManager>
{
private:
	friend CSingleton;
	CKeyManager();
	virtual ~CKeyManager();
	CKeyManager(const CKeyManager&) = delete;
	CKeyManager& operator=(CKeyManager&) = delete;

public:
	bool KeyPress(int iKey)
	{
		if (GetAsyncKeyState(iKey) & 0x8000)
			return true;

		return false;
	}

	bool KeyDown(int iKey)
	{
		if (!m_bKey[iKey] && GetAsyncKeyState(iKey) & 0x8000)
		{
			m_bKey[iKey] = !m_bKey[iKey];
			return true;
		}	
		return false;
	}

	bool KeyUp(int iKey)
	{
		if (m_bKey[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
		{
			m_bKey[iKey] = !m_bKey[iKey];
			return true;
		}
		return false;
	}


public:
	void Update()
	{
		for (int i = 0; i < VIR_KEY; ++i)
		{
			if (!m_bKey[i] && (GetAsyncKeyState(i) & 0x8000))
				m_bKey[i] = !m_bKey[i];

			if (m_bKey[i] && !(GetAsyncKeyState(i) & 0x8000))
				m_bKey[i] = !m_bKey[i];
		}
	}

private:
	bool m_bKey[VIR_KEY];
};

