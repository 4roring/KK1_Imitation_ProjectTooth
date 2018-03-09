#pragma once
#include "Scene.h"
class CStage_3 :
	public CScene
{
public:
	CStage_3();
	virtual ~CStage_3();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void LoadDeco();
	void LoadCollTile();
};

