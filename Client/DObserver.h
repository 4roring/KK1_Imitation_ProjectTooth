#pragma once
class DObserver
{
public:
	DObserver();
	virtual ~DObserver();

public:
	void UpdateOrder(float bOrder, UNITID eUnitID, VECCOLLTILE vecPath);

public:
	float GetOrder() const { return m_fOrder; }
	UNITID GetOrderID() const { return m_eUnitID; }
	const VECCOLLTILE& GetVecPath() const { return m_vecPath; }

private:
	float m_fOrder = false;
	UNITID m_eUnitID = UNIT_ALL;
	VECCOLLTILE m_vecPath;
};

