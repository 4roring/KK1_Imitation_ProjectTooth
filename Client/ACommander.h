#pragma once
#include "Actor.h"

class DCommand;
class ACommander :
	public CActor
{
public:
	ACommander();
	virtual ~ACommander();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	enum ANIMSTATE { Idle, Order, Run, Build, RunOrder, RunBuild, ReturnHome, Dead, End };
	ANIMSTATE m_eCurAnimState = ACommander::Idle;
	ANIMSTATE m_ePreAnimState = ACommander::End;
	
private:
	void UpdateState(float deltaTime);
	void Move(float deltaTime);
	void SetAnimState();

public:
	void CheckTileObject();
	void CheckHQ();
	void CheckFarm();
	void CheckSlotUnit();
	void CheckTileUnit();
	void CreateSlotUnitBuilding();

public:
	bool CheckObjectID(CGameObject* pObject, OBJID eObjectID);
	bool CheckObjectTeam(CGameObject* pObject, TEAMID eTeam);
	bool CheckObjectNetual(CGameObject* pObject, OBJID eObjectID);

private:
	bool OffsetX();
	bool OffsetY();

private:
	DCommand* m_pCommand;
	friend class DPlayerCommand;

private:
	float m_fReturn;
	float m_fOrder;
	bool m_bBuild;
	int m_iGroup;
	int m_iSelectSlot;
	UNITID m_eUnit[SLOT_MAX];
};

