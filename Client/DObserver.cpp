#include "stdafx.h"
#include "DObserver.h"


DObserver::DObserver()
{
}


DObserver::~DObserver()
{
}

void DObserver::UpdateOrder(bool bOrder, UNITID eUnitID, const COLLTILE* pTarget)
{
	m_bOrder = bOrder;
	m_eUnitID = eUnitID;
	m_pTarget = pTarget;
}
