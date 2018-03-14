#pragma once
class DObserver
{
public:
	DObserver();
	virtual ~DObserver();

public:
	void UpdateOrder(bool bOrder, UNITID eUnitID, const COLLTILE* pTarget);

public:
	bool GetOrder() { return m_bOrder; }
	UNITID GetOrderID() { return m_eUnitID; }

private:
	bool m_bOrder = false;
	UNITID m_eUnitID = UNIT_ALL;
	const COLLTILE* m_pTarget = nullptr;
};

