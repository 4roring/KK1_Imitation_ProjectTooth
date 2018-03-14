#pragma once

class ViewManager :
	public CSingleton<ViewManager>
{
private:
	friend CSingleton;
	explicit ViewManager();
	virtual ~ViewManager();
	ViewManager(const ViewManager&) = delete;
	ViewManager& operator=(ViewManager&) = delete;

public:
	const Vector3& GetScroll() const { return m_vScroll; }

public:
	void SetMaxScroll(Vector3 vMaxScroll) { m_vMaxScroll = vMaxScroll; }
	void SetScroll(Vector3 vScroll) { m_vScroll = vScroll; }

public:
	void MoveScrollX(float fMoveX);
	void MoveScrollY(float fMoveY);
	bool IsScreen();
	
private:
	Vector3 m_vScroll = Vector3(0.f, 0.f, 0.f);
	Vector3 m_vMaxScroll = Vector3(0.f, 0.f, 0.f);
};

#define ViewMgr ViewManager::GetInstance()