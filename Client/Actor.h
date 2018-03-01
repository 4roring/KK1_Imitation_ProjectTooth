#pragma once
#include "GameObject.h"
class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime);
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	void SetTintColor();
	void FrameMove(float deltaTime);

protected:
	float m_fSpeed;
	int m_iMaxHp;
	int m_iHp;

	TEAMID m_eTeam;
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
};

