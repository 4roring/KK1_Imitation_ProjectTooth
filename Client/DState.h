#pragma once
class DState
{
public:
	DState();
	virtual ~DState();

public:
	virtual HRESULT Initialize() PURE;
	virtual void Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
};

