#pragma once

// ��� ����, �÷��̾�� AI�� Commander�� ����.

class ACommander;
class DCommand
{
public:
	DCommand();
	virtual ~DCommand();

	virtual void Update() PURE;

public:
	void SetCommander(ACommander* pActor) { m_pACommander = pActor; }

protected:
	ACommander* m_pACommander;
};

