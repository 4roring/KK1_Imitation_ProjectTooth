#pragma once

class CScene;
class CSceneManager :
	public CSingleton<CSceneManager>
{
	friend CSingleton;

private:
	explicit CSceneManager();
	virtual ~CSceneManager();
	CSceneManager(const CSceneManager&) = delete;
	CSceneManager& operator=(CSceneManager&) = delete;

public:
	SCENEID GetCurSceneID() { return m_eSceneID; }

public:
	HRESULT SceneChange(SCENEID eSceneID);

public:
	void Update();
	void LateUpdate();
	void Render();
	void Release();
	

private:
	void FrameEnd();
	void FadeIn();
	void FadeOut();

private:
	SCENEID m_eSceneID;
	CScene* m_pScene = nullptr;
	D3DXMATRIX m_matIdentity;
	float m_fAlpha = 0.f;
	bool m_bSceneChange = nullptr;
	bool m_bFade = false;
};

#define SceneMgr CSceneManager::GetInstance()