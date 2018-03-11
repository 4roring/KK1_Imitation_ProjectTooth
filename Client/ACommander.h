#pragma once
#include "Actor.h"

class DCommand;
class ACommander :
	public CActor
{
public:
	ACommander();
	virtual ~ACommander();

	// CActor을(를) 통해 상속됨
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
	void CheckTileObject();
	void CheckHQ();
	void CheckUnit();

private:
	bool OffsetX();
	bool OffsetY();

private:
	DCommand* m_pOperator;
	friend class DPlayerCommand;

private:
	float m_fReturn;
	float m_fOrder;
	bool m_bBuild;
	int m_iGroup;
};

