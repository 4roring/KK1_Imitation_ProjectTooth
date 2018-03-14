#pragma once
#include "Building.h"
class BHQ :
	public CBuilding
{
public:
	BHQ();
	virtual ~BHQ();

	// CBuilding을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetHQState(int iState) { m_eCurState = (HQSTATE)iState; }

private:
	enum HQSTATE { Build, Idle, Sawing, Meat1, Meat2, Dead, ReBuild, End };
	HQSTATE m_eCurState = HQSTATE::Build;
	HQSTATE m_ePreState = HQSTATE::End;

private:
	void UpdateState(float deltaTime);
	void SetAnimState();

private:
	void WindmillFrameMove(float deltaTime);
	void SetWindmillAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed);
	void UpdateWindmillRect();
	void WindmillRender();

private:
	HRESULT SetTexture();

private:
	RECT m_tWindmillRect;
	ANIMFRAME m_tWindmillFrame;
	ANIMSCENE m_tWindmillScene;

private:
	const TEXINFO* m_pWindmillTexMain = nullptr;
	const TEXINFO* m_pWindmillTexTint = nullptr;

private:
	bool m_bFirstBuild = false;
};

