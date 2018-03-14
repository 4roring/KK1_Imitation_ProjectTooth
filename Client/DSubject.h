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
	void Notify(bool bOrder, UNITID eUnitID, const COLLTILE* pTile);
	void Release();

private:
	std::list<DObserver*> m_Observerlist;
};

