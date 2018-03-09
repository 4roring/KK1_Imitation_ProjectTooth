#pragma once

class CScene;
class CSceneManager :
	public CSingleton<CSceneManager>
{
	friend CSingleton;

private:
	CSceneManager();
	virtual ~CSceneManager();

public:
	HRESULT SceneChange(SCENEID eSceneID);

public:
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	SCENEID m_eSceneID;
	CScene* m_pScene;
};

#define SceneMgr CSceneManager::GetInstance()