#include "stdafx.h"
#include "BHQ.h"
#include "Level.h"

BHQ::BHQ()
{
}


BHQ::~BHQ()
{
	Release();
}

HRESULT BHQ::Initialize()
{
	CBuilding::Initialize();

	m_eLayer = LAYER_OBJ;

	m_pTexMain = TextureMgr->GetTexture(TEXT("windmill_base"));
	m_pTexTint = TextureMgr->GetTexture(TEXT("windmill_base_tint"));

	m_pWindmillTexMain = TextureMgr->GetTexture(TEXT("windmill_topper"));
	m_pWindmillTexTint = TextureMgr->GetTexture(TEXT("windmill_topper_tint"));

	iImageCX = WINDMILL_CX;
	iImageCY = WINDMILL_CY;

	m_tFrame.fCenterX = (float)(iImageCX >> 1);
	m_tFrame.fCenterY = (float)iImageCY * 0.9f;

	m_tScene.iFrame = 0;
	m_tScene.iMaxFrame = 16;
	m_tScene.iScene = 0;
	m_tScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_tWindmillScene.iFrame = 0;
	m_tWindmillScene.iMaxFrame = 16;
	m_tWindmillScene.iScene = 0;
	m_tWindmillScene.fSceneMax = 1.f / (float)m_tScene.iMaxFrame;

	m_iMaxHp = 50;
	m_iHp = m_iMaxHp;

	return S_OK;
}

OBJSTATE BHQ::Update(float deltaTime)
{
	if (nullptr == m_pLevel)
	{
		m_pLevel = dynamic_cast<CLevel*>(GameMgr->GetObjectList(OBJ_LEVEL).back());

		for (int iTileNum : m_iTileIndexArr)
		{
			(*m_pLevel->GetVecCollTile())[iTileNum]->pGameObject = this;
			(*m_pLevel->GetVecCollTile())[iTileNum]->byDrawID = 1;
			(*m_pLevel->GetVecCollTile())[iTileNum]->byOption = 1;
		}

		Vector3 vPos = (*m_pLevel->GetVecCollTile())[m_iTileIndexArr[0]]->vPosition;
		m_tInfo.vPosition = Vector3(vPos.x, vPos.y, 0.f);
	}
	CBuilding::Update(deltaTime);
	UpdateState(deltaTime);
	return STATE_PLAY;
}

void BHQ::LateUpdate()
{
	CBuilding::LateUpdate();
	UpdateWindmillRect();
	SetAnimState();
}

void BHQ::Render()
{
	CBuilding::Render();
	WindmillRender();
}

void BHQ::Release()
{
}

void BHQ::UpdateState(float deltaTime)
{
	if (m_iHp <= 0)
	{
		// TODO: HQ ������ ����Ʈ 
		// ����Ʈ ������ Dead�� ���� ��ȯ.
		m_eCurState = BHQ::Dead;
	}

	switch (m_eCurState)
	{
	case BHQ::Build:
		if (m_tFrame.fFrame >= 95.5f)
		{
			WindmillFrameMove(deltaTime);
			m_tFrame.fFrame = 95.5f;
		}
			
		// TODO: ��������� ������ ����Ʈ!
		if (m_tWindmillFrame.fFrame >= 42.5f)
		{
			// TODO: �ϼ� ����Ʈ!
			m_bFirstBuild = true;
			m_eCurState = BHQ::Idle;

			// �ֺ� �ʵ��� ���� �ڽ��� ������!
			for (int i = 0; i < 8; ++i)
			{
				int iFramIndex = m_pLevel->GetNeighborTileIndex(i, m_iTileIndexArr[0], 2);
				(*m_pLevel->GetVecCollTile())[iFramIndex]->pGameObject->SetTeam(m_eTeam);
			}
		}
		if (m_bDestroy)
		{
			if (false == m_bFirstBuild)
			{
				// ����� �����ְ� �߸� HQ ��ȯ!
			}
			else
			{
				// ����� �����ְ� Dead�� �ٽ� ��ȯ.
			}
		}
		break;
	case BHQ::Idle:
	case BHQ::Sawing:
	case BHQ::Meat1:
	case BHQ::Meat2:
		WindmillFrameMove(deltaTime);

		// Idle���� Ȯ�������� Sawing���ٰ� Meat1, 2�� �����ϰ� ���.
		break;
	case BHQ::Dead:
		if (true == m_bDestroy)
		{
			// TODO: ����Ʈ ��
			m_eCurState = BHQ::ReBuild;
		}

		break;
	case BHQ::ReBuild:
		if (m_tFrame.fFrame >= 211.5f)
		{

		}
		break;
	case BHQ::End:
	default:
		break;
	}
}

void BHQ::SetAnimState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BHQ::Build:
			SetAnimFrame(0.f, 96.f, 0.1f);
			SetWindmillAnimFrame(0.f, 43.f, 0.25f);
			break;
		case BHQ::Idle:
			SetAnimFrame(96.f, 97.f, 1.f);
			SetWindmillAnimFrame(44.f, 105.f, 0.2f);
			break;
		case BHQ::Sawing:
			SetAnimFrame(96.f, 142.f, 0.2f);
			break;
		case BHQ::Meat1:
			SetAnimFrame(143.f, 166.f, 0.2f);
			break;
		case BHQ::Meat2:
			SetAnimFrame(166.f, 203.f, 0.2f);
			break;
		case BHQ::Dead:
			SetAnimFrame(204.f, 207.f, 0.2f);
			SetWindmillAnimFrame(0.f, 0.f, 0.2f);
			break;
		case BHQ::ReBuild:
			SetAnimFrame(208.f, 212.f, 0.2f);
			SetWindmillAnimFrame(0.f, 0.f, 0.2f);
			break;
		case BHQ::End:
		default:
#ifdef _DEBUG
			assert(!"Farm AnimState Error(defalut or End");
#endif
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void BHQ::WindmillFrameMove(float deltaTime)
{
	m_tWindmillFrame.fFrame += m_tWindmillFrame.fCount * deltaTime;
	if (m_tWindmillFrame.fFrame > m_tWindmillFrame.fMax)
		m_tWindmillFrame.fFrame = m_tWindmillFrame.fMin;

	m_tWindmillScene.iScene = int(m_tWindmillScene.fSceneMax * m_tWindmillFrame.fFrame);
	m_tWindmillScene.iFrame = int(m_tWindmillFrame.fFrame - m_tWindmillScene.iMaxFrame * m_tWindmillScene.iScene);
}

void BHQ::SetWindmillAnimFrame(float fFrameMin, float fFrameMax, float fFrameSpeed)
{
	m_tWindmillFrame.fMin = fFrameMin;
	m_tWindmillFrame.fFrame = fFrameMin;
	m_tWindmillFrame.fCount = (fFrameMax - fFrameMin) * fFrameSpeed;
	m_tWindmillFrame.fMax = fFrameMax;
}

void BHQ::UpdateWindmillRect()
{
	int iSceneLeft = m_tWindmillScene.iFrame * iImageCX;
	int iSceneTop = m_tWindmillScene.iScene * iImageCY;
	int iSceneRight = m_tWindmillScene.iFrame * iImageCX + iImageCX;
	int iSceneBottom = m_tWindmillScene.iScene * iImageCY + iImageCY;

	m_tWindmillRect = { iSceneLeft, iSceneTop, iSceneRight, iSceneBottom };
}

void BHQ::WindmillRender()
{
	m_pSprite->Draw(m_pWindmillTexMain->pTexture
		, &m_tWindmillRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_pWindmillTexTint->pTexture
		, &m_tWindmillRect
		, &Vector3(m_tFrame.fCenterX, m_tFrame.fCenterY, 0.f)
		, nullptr, *m_TeamColor);
}