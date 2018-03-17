#include "stdafx.h"
#include "DObserver.h"


DObserver::DObserver()
{
}


DObserver::~DObserver()
{
}

void DObserver::UpdateOrder(float bOrder, UNITID eUnitID, VECCOLLTILE vecPath)
{
	m_fOrder = bOrder;
	m_eUnitID = eUnitID;
	m_vecPath.clear();
	m_vecPath.assign(vecPath.begin(), vecPath.end());
}
