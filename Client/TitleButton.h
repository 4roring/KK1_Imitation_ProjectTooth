#pragma once
#include "GameObject.h"

class CScene;
class CTitleButton :
	public CGameObject
{
public:
	CTitleButton();
	virtual ~CTitleButton();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual OBJSTATE Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetButtonOption(int iOption) { m_iOption = iOption; }
	
private:
	void FrameEnd();
	bool CheckMousePos();
	void ButtonRender();
	void TextRender();

private:
	bool m_bOnMouse = false;
	bool m_bOnMouseSound = false;
	int m_iOption = 0;
	const TEXINFO* m_TexOverlay = nullptr;
	const TEXINFO* m_TexTabOn = nullptr;
	const TEXINFO* m_TexTabOff = nullptr;
	LPD3DXFONT m_pFont = nullptr;
	CScene* m_pTitle = nullptr;
};

