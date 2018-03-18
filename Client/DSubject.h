#pragma once

class DObserver;
class DSubject
{
public:
	DSubject();
	virtual ~DSubject();

public:
	void Subscribe(DObserver* pObserver);
	void UnSubscribe(DObserver* pObserver);
	void Notify(int iFood);
	void Notify(UNITID eUnitID, int iSlot);
	void NotifySlotNum(int iSlot);
	void Notify(float fOrder, UNITID eUnitID, VECCOLLTILE vecPath);
	void Release();

private:
	std::list<DObserver*> m_Observerlist;
};