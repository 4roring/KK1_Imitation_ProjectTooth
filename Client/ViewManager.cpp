#include "stdafx.h"
#include "ViewManager.h"


ViewManager::ViewManager()
{
}


ViewManager::~ViewManager()
{
}

void ViewManager::MoveScrollX(float fMoveX)
{
	m_vScroll.x -= fMoveX;

	if (false == IsScreen())
		m_vScroll.x += fMoveX;
}

void ViewManager::MoveScrollY(float fMoveY)
{
	m_vScroll.y -= fMoveY;

	if (false == IsScreen())
		m_vScroll.y += fMoveY;
}

bool ViewManager::IsScreen()
{
	if (m_vScroll.x > 0.f) return false;
	if (m_vScroll.y > 0.f) return false;
	if (m_vScroll.x < -m_vMaxScroll.x) return false;
	if (m_vScroll.y < -m_vMaxScroll.y) return false;

	return true;
}
