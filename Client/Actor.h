#pragma once
#include "GameObject.h"
class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	void FrameMove(float deltaTime);

protected:
	float m_fSpeed;
	int m_iMaxHp;
	int m_iHp;

	TEAMID m_eTeam;
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;

	D3DCOLOR* m_TeamColor;
};

