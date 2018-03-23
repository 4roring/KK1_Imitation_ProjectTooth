#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void TextureLoad(TCHAR* FilePath);
	void SetLoadingMessage(const TCHAR* pMessage) { m_pLoadingMessage = pMessage; }

public:
	static unsigned int _stdcall ThreadFunc(void* pArg);
	bool m_bComplete = false;

private:
	const TCHAR* m_pLoadingMessage;
	HANDLE m_hThread = nullptr;
	LPD3DXFONT m_pFont = nullptr;
};

