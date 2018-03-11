#pragma once

// 명령 패턴, 플레이어와 AI가 Commander를 조작.

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

