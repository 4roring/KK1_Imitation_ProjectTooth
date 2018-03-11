#pragma once
#include "GameObject.h"
class CBuilding :
	public CGameObject
{
public:
	CBuilding();
	virtual ~CBuilding();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() PURE;

public:
	void SetTileIndexArray(int iStart);

protected:
	void FrameMove(float deltaTime);
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void UpdateRect();
	
protected:
	int m_iMaxHp = 0;
	int m_iHp = 0;
	float m_fBuildTime = 0.f;

protected:
	RECT m_tRect;
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	const TEXINFO* m_pTexTint = nullptr;

protected:
	int m_iTileIndexArr[4];
	int iImageCX;
	int iImageCY;

private:
	const D3DCOLOR* m_TeamColor = nullptr;
};

