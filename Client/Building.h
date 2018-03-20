#pragma once
#include "GameObject.h"
class BBuilding :
	public CGameObject
{
public:
	BBuilding();
	virtual ~BBuilding();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() PURE;

public:
	virtual void ApplyDamage(int iDamage) override;

public:
	void SetTileIndexArray(int iStart);

protected:
	void InitHpUI();
	void DestroyHpUI();
	void FrameMove(float deltaTime);
	void SetAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void UpdateRect();
	
protected:
	float m_fBuildTime = 0.f;

protected:
	RECT m_tRect;
	ANIMFRAME m_tFrame;
	ANIMSCENE m_tScene;
	const TEXINFO* m_pTexTint = nullptr;
	const D3DCOLOR* m_TeamColor = nullptr;

protected:
	int m_iTileIndexArr[4] = {};
	int m_iImageCX;
	int m_iImageCY;

protected:
	CGameObject* m_pStateUI;
};

