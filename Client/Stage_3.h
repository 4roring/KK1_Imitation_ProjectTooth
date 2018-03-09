#pragma once
#include "Scene.h"
class CStage_3 :
	public CScene
{
public:
	CStage_3();
	virtual ~CStage_3();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void LoadDeco();
	void LoadCollTile();
};

