#pragma once
class AUnit;
class DBridge
{
public:
	DBridge();
	virtual ~DBridge();

public:
	virtual HRESULT Initialize() PURE;
	virtual OBJSTATE Update(float deltaTime) PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:


protected:

};

