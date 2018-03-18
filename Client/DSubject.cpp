#include "stdafx.h"
#include "DSubject.h"
#include "DObserver.h"

DSubject::DSubject()
{
}


DSubject::~DSubject()
{
}

void DSubject::Subscribe(DObserver * pObserver)
{
	if (nullptr == pObserver)
		return;

	m_Observerlist.push_back(pObserver);
}

void DSubject::UnSubscribe(DObserver * pObserver)
{
	auto iter = find(m_Observerlist.begin(), m_Observerlist.end(), pObserver);
	if (iter == m_Observerlist.end())
		return;

	m_Observerlist.erase(iter);
}

void DSubject::Notify(float fOrder, UNITID eUnitID, VECCOLLTILE vecPath)
{
	for (auto& pObserver : m_Observerlist)
		pObserver->UpdateOrder(fOrder, eUnitID, vecPath);
}

void DSubject::Notify(UNITID eUnitID, int iSlot)
{
	for (auto& pObserver : m_Observerlist)
		pObserver->UpdateUnitSlot(eUnitID, iSlot);
}

void DSubject::NotifySlotNum(int iSlot)
{
	for (auto& pObserver : m_Observerlist)
		pObserver->UpdateSelectSlot(iSlot);
}

void DSubject::Notify(int iFood)
{
	for (auto& pObserver : m_Observerlist)
		pObserver->UpdateFood(iFood);
}

void DSubject::Release()
{
	m_Observerlist.clear();
}
