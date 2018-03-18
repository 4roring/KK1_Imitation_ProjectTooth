#pragma once
class DObserver
{
public:
	DObserver();
	virtual ~DObserver();

public:
	void UpdateOrder(float bOrder, UNITID eUnitID, VECCOLLTILE vecPath);
	void UpdateUnitSlot(UNITID eUnitID, int iSlot);
	void UpdateFood(int iFood);
	void UpdateSelectSlot(int iSlot);

public:
	float GetOrder() const { return m_fOrder; }
	UNITID GetOrderID() const { return m_eUnitID; }
	const VECCOLLTILE& GetVecPath() const { return m_vecPath; }
	UNITID GetUnitSlot(int iSlot) { return m_pUnitSlot[iSlot]; }
	TEAMID GetTeamID() { return m_eTeam; }
	int GetSelectSlot() { return m_iSlot; }
	int GetFood() { return m_iFood; }

private:
	float m_fOrder = false;
	UNITID m_eUnitID = UNIT_ALL;
	VECCOLLTILE m_vecPath;
	UNITID m_pUnitSlot[SLOT_MAX];
	TEAMID m_eTeam;
	int m_iSlot;
	int m_iFood;
};

