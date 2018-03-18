#include "stdafx.h"
#include "UnitUI.h"
#include "DObserver.h"

CUnitUI::CUnitUI()
{
}


CUnitUI::~CUnitUI()
{
	Release();
}

HRESULT CUnitUI::Initialize()
{
	UUI::Initialize();
	m_pMidBar = TextureMgr->GetTexture(TEXT("ui"), TEXT("unitbar_woodbg"))->pRect;
	m_pInfoBar = TextureMgr->GetTexture(TEXT("ui"), TEXT("portrait_woodbg"))->pRect;
	
	m_tInfo.vPosition = Vector3(390.f, 723.f, 0.f);

	return S_OK;
}

OBJSTATE CUnitUI::Update(float deltaTime)
{
	if (nullptr == m_pColor)
		SetUnitUI();

	m_iSelectSlot = m_pObserver->GetSelectSlot();

	return STATE_PLAY;
}

void CUnitUI::LateUpdate()
{
	UpdateMatrix();
}

void CUnitUI::Render()
{
	UnitInfoUIRender();
	UnitSelectUIRender();
}

void CUnitUI::Release()
{
}

void CUnitUI::SetUnitUI()
{
	for (int i = 0; i<SLOT_MAX; ++i)
		m_eUnitSlot[i] = m_pObserver->GetUnitSlot(i);

	m_pColor = GameMgr->GetTeamColor(m_eTeam);
	m_pTexUnitCircle = TextureMgr->GetTexture(TEXT("ui"), TEXT("unitbar_circlebg1"))->pRect;
	m_pTexPogarrows = TextureMgr->GetTexture(TEXT("ui"), TEXT("pogarrows"))->pRect;

	for (int i = 0; i < SLOT_MAX; ++i)
	{
		switch (m_eUnitSlot[i])
		{
		case UNIT_SQUIRREL:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_squirrel"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_squirrel_tint"))->pRect;
			break;
		case UNIT_LIZARD:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_lizard"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_lizard_tint"))->pRect;
			break;
		case UNIT_TOAD:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_toad"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_toad_tint"))->pRect;
			break;
		case UNIT_PIGEON:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_pigeon"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_pigeon_tint"))->pRect;
			break;
		case UNIT_MOLE:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_mole"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_mole_tint"))->pRect;
			break;
		case UNIT_FERRET:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ferret"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ferret_tint"))->pRect;
			break;
		case UNIT_CHAMELEON:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_chameleon"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_chameleon_tint"))->pRect;
			break;
		case UNIT_FALCON:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_falcon"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_falcon_tint"))->pRect;
			break;
		case UNIT_SKUNK:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_skunk"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_skunk_tint"))->pRect;
			break;
		case UNIT_SNAKE:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_snake"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_snake_tint"))->pRect;
			break;
		case UNIT_BADGER:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_badger"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_badger_tint"))->pRect;
			break;
		case UNIT_BOAR:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_boar"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_boar_tint"))->pRect;
			break;
		case UNIT_FOX:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_fox"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_fox_tint"))->pRect;
			break;
		case UNIT_OWL:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_owl"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_owl_tint"))->pRect;
			break;
		case UNIT_WOLF:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_wolf"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_wolf_tint"))->pRect;
			break;
		case UNIT_BARBEDWIRE:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_barbedwire"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_barbedwire_tint"))->pRect;
			break;
		case UNIT_LANDMINE:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_landmine"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_landmine_tint"))->pRect;
			break;
		case UNIT_BALLON:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ballon"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ballon_tint"))->pRect;
			break;
		case UNIT_TURRET:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_turret"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_turret_tint"))->pRect;
			break;
		case UNIT_ARTILLERY:
			m_pTexUnitUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_artillery"))->pRect;
			m_pTexUnitTintUI[i] = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_artillery_tint"))->pRect;
			break;
		case UNIT_ALL:
		default:
#ifdef _DEBUG
			assert(!"UnitUI Select Error!!!! (UNIT_ALL or default)");
#endif
			break;
		}
	}
}

void CUnitUI::UnitSelectUIRender()
{
	D3DXMATRIX matScale, matTrans, matWorld;

	for (int i = 0; i < SLOT_MAX; ++i)
	{
		if(i == m_iSelectSlot)
			D3DXMatrixScaling(&matScale, 0.45f, 0.45f, 1.f);
		else
			D3DXMatrixScaling(&matScale, 0.35f, 0.35f, 1.f);

		D3DXMatrixTranslation(&matTrans
			, m_tInfo.vPosition.x + 39.f + 58.f * i  
			, m_tInfo.vPosition.y + 5.f
			, 0.f);

		matWorld = matScale * matTrans;

		m_pSprite->SetTransform(&matWorld);

		int iWidth = m_pTexUnitCircle->right - m_pTexUnitCircle->left;
		int iHeight = m_pTexUnitCircle->bottom - m_pTexUnitCircle->top;
		m_pSprite->Draw(m_pTexMain->pTexture
			, m_pTexUnitCircle
			, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));

		iWidth = m_pTexUnitUI[i]->right - m_pTexUnitUI[i]->left;
		iHeight	= m_pTexUnitUI[i]->bottom - m_pTexUnitUI[i]->top;
		m_pSprite->Draw(m_pTexMain->pTexture
			, m_pTexUnitUI[i]
			, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));


		iWidth = m_pTexUnitTintUI[i]->right - m_pTexUnitTintUI[i]->left;
		iHeight = m_pTexUnitTintUI[i]->bottom - m_pTexUnitTintUI[i]->top;
		m_pSprite->Draw(m_pTexMain->pTexture
			, m_pTexUnitTintUI[i]
			, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
			, nullptr
			, *m_pColor);


		if (i == m_iSelectSlot)
		{
			iWidth = m_pTexPogarrows->right - m_pTexPogarrows->left;
			iHeight = m_pTexPogarrows->bottom - m_pTexPogarrows->top;
			m_pSprite->Draw(m_pTexMain->pTexture
				, m_pTexPogarrows
				, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CUnitUI::UnitInfoUIRender()
{
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pMidBar
		, nullptr
		, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pInfoBar
		, nullptr
		, &Vector3(919.5f, -50.f, 0.f)
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}
