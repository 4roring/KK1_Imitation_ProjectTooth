#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
{
}


CActor::~CActor()
{
}

OBJSTATE CActor::Update(float deltaTime)
{
	FrameMove(deltaTime);

	return STATE_PLAY;
}

void CActor::SetTintColor()
{
	D3DLOCKED_RECT LockRect;
	m_pTexTint->pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);
	DWORD* pColor = (DWORD*)LockRect.pBits;

	for (size_t y = 0; y < m_pTexTint->tImageInfo.Height; ++y)
	{
		for (size_t x = 0; x < m_pTexTint->tImageInfo.Width; ++x)
		{
			int iIdx = y * m_pTexTint->tImageInfo.Width + x;

			D3DXCOLOR xColor = pColor[iIdx];

			switch (m_eTeam)
			{
			case TEAM_RED:
				xColor.g = 0;
				xColor.b = 0;
				break;
			case TEAM_BLUE:
				xColor.r = 0;
				xColor.g = 0;
				break;
			case TEAM_GREEN:
				xColor.r = 0;
				xColor.b = 0;
				break;
			case TEAM_YELLO:
				xColor.b = 0;
				break;
			default:
				assert(!"Team Color Select Error");
				break;
			}
			pColor[iIdx] = xColor;
		}
	}

	m_pTexTint->pTexture->UnlockRect(0);
}

void CActor::FrameMove(float deltaTime)
{
	m_tFrame.fFrame += m_tFrame.fCount * deltaTime;
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMin;

	m_tScene.iScene = int(m_tScene.fSceneMax * m_tFrame.fFrame);
	m_tScene.iFrame = int(m_tFrame.fFrame - m_tScene.iMaxFrame * m_tScene.iScene);
}
