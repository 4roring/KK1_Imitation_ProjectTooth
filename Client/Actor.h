#pragma once
#include "GameObject.h"
class AActor :
	public CGameObject
{
public:
	AActor();
	virtual ~AActor();

public:
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() PURE;
	virtual void Release() PURE;


protected:
	void FrameMove(float deltaTime);
	void UpdateRect();
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void RenderShadow(BYTE Alpha);
	void RenderFlyChar();
	void RenderGroundChar();
	void UpdateFlipX();
	bool CheckEnemy(int iRange);

private:
	void CheckCollTile();

protected:
	float m_fSpeed = 0.f;
	int m_iMaxHp = 0;
	int m_iHp = 0;
	bool m_bFlipX = false;
	bool m_bDead = false;
	int m_iImageX = 0;
	int m_iImageY = 0;

protected:
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	const TEXINFO* m_pTexTint = nullptr;

protected:
	COLLTILE* m_pTarget = nullptr;

private:
	RECT m_tRect;
	const D3DCOLOR* m_TeamColor = nullptr;
};

