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

public:
	virtual void ApplyDamage(int iDamage) override;

protected:
	void FrameMove(float deltaTime);
	void HealTime(float deltaTime);
	void UpdateRect();
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void RenderShadow(BYTE Alpha);
	void RenderFlyChar();
	void RenderGroundChar();
	void UpdateFlipX();
	bool CheckEnemy(int iRange);
	bool AttackPossible(CGameObject* pObject);

private:
	void CheckCollTile();

protected:
	float m_fSpeed = 0.f;
	bool m_bFlipX = false;
	bool m_bDead = false;
	int m_iImageCX = 0;
	int m_iImageCY = 0;
	float m_fHealTime = 0.f;

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

