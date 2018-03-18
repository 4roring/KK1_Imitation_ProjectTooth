#include "stdafx.h"
#include "APig.h"
#include "Level.h"

APig::APig()
{
}


APig::~APig()
{
}

HRESULT APig::Initialize()
{
	return S_OK;
}

OBJSTATE APig::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

	return STATE_PLAY;
}

void APig::LateUpdate()
{
}

void APig::Render()
{
}

void APig::Release()
{
}
