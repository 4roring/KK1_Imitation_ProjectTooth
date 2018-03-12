#pragma once
#include "GameObject.h"
class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject��(��) ���� ��ӵ�
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
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void RenderShadow(BYTE Alpha);
	void RenderFlyChar();
	void RenderGroundChar();
	void UpdateFlipX();

private:
	void CheckCollTile();

protected:
	float m_fSpeed = 0.f;
	int m_iMaxHp = 0;
	int m_iHp = 0;
	bool m_bFlipX = false;
	bool m_bDead = false;

protected:
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	const TEXINFO* m_pTexTint = nullptr;

protected:
	int m_iTileIndex = 0;

private:
	RECT m_tRect;
	const D3DCOLOR* m_TeamColor = nullptr;
};

