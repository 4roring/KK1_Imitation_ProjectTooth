#pragma once

// ��� ����, �÷��̾�� AI�� Commander�� ����.

class ACommander;
class COperator
{
public:
	COperator();
	virtual ~COperator();

	virtual void Update() PURE;

public:
	void SetCommander(ACommander* pActor) { m_pACommander = pActor; }

protected:
	ACommander* m_pACommander;
};

