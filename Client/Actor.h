#pragma once
#include "GameObject.h"
class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	void SetTeamID(TEAMID eTeam) { m_eTeam = eTeam; }

protected:
	void FrameMove(float deltaTime);
	void UpdateRect();
	void RenderShadow(BYTE Alpha);
	void RenderFlyChar();
	void RenderGroundChar();
	void SetAnimFrame(float fMin, float fMax, float fFrameSpeed);
	void UpdateFlipX();

protected:
	bool m_bFlipX;
	float m_fSpeed;
	int m_iMaxHp;
	int m_iHp;
	bool m_bDead;

	TEAMID m_eTeam;
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	RECT m_tRect;

	const D3DCOLOR* m_TeamColor;
	const TEXINFO* m_pTexTint = nullptr;
};

