#pragma once
#include "GameObject.h"
class AActor :
	public CGameObject
{
public:
	AActor();
	virtual ~AActor();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	int GetTileIndex() { return m_iTileIndex; }

public:
	void SetTileIndex(int iTileIndex) { m_iTileIndex = iTileIndex; }

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
	int m_iImageX = 0;
	int m_iImageY = 0;

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

