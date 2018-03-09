#include "stdafx.h"
#include "ViewManager.h"


ViewManager::ViewManager()
{
}


ViewManager::~ViewManager()
{
}

void ViewManager::MoveScroll(Vector3 m_vMove)
{
	m_vScroll -= m_vMove;

	if (false == IsScreen())
		m_vScroll += m_vMove;
}

bool ViewManager::IsScreen()
{
	if (m_vScroll.x > 0.f) return false;
	if (m_vScroll.y > 0.f) return false;
	if (m_vScroll.x < -m_vMaxScroll.x) return false;
	if (m_vScroll.y < -m_vMaxScroll.y) return false;

	return true;
}
