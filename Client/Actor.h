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
	void SetTeamID(TEAMID eTeam);

protected:
	void FrameMove(float deltaTime);
	void UpdateRect();
	void RenderShadow(BYTE Alpha);
	void RenderFlyChar();
	void RenderGroundChar();
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void UpdateFlipX();

private:
	void CheckCollTile();

protected:
	bool m_bFlipX;
	float m_fSpeed;
	int m_iMaxHp;
	int m_iHp;
	bool m_bDead;

protected:
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	const TEXINFO* m_pTexTint = nullptr;

protected:
	class CLevel* m_pLevel;
	int m_iTileIndex;

private:
	RECT m_tRect;
	TEAMID m_eTeam;
	const D3DCOLOR* m_TeamColor;
};

