#include "stdafx.h"
#include "UUnitFactoryUI.h"


UUnitFactoryUI::UUnitFactoryUI()
{
}


UUnitFactoryUI::~UUnitFactoryUI()
{
}

HRESULT UUnitFactoryUI::Initialize()
{
	m_eLayer = LAYER_WORLDUI;

	m_pColor = GameMgr->GetTeamColor(m_eTeam);
	m_pTexMain = TextureMgr->GetTexture(TEXT("ui"), TEXT("unitbar_circlebg1"));
	m_pTexUnitCircle = m_pTexMain->pRect;
	m_tHpFill = *TextureMgr->GetTexture(TEXT("ui"), TEXT("healthgauge_factory_fill"))->pRect;

	m_iHpFillHeight = m_tHpFill.bottom - m_tHpFill.top;

	return S_OK;
}

OBJSTATE UUnitFactoryUI::Update(float deltaTime)
{
	if (nullptr == m_pTexUnitUI)
		SetUnitUI();

	if (true == m_bDestroy)
		return STATE_DESTROY;

	m_tInfo.vPosition = m_pTarget->GetInfo().vPosition + Vector3(0.f, -1.f, 0.f) * 30.f;

	return STATE_PLAY;
}

void UUnitFactoryUI::LateUpdate()
{
	SetFillRatio();
}

void UUnitFactoryUI::Render()
{
	UnitIconRender();
	
	if(m_pTarget->GetHpRatio() < 1.f)
		HpFillRender();
}

void UUnitFactoryUI::Release()
{
}

void UUnitFactoryUI::SetUnitUI()
{
	switch (m_eUnitID)
	{
	case UNIT_SQUIRREL:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_squirrel"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_squirrel_tint"))->pRect;
		break;
	case UNIT_LIZARD:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_lizard"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_lizard_tint"))->pRect;
		break;
	case UNIT_TOAD:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_toad"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_toad_tint"))->pRect;
		break;
	case UNIT_PIGEON:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_pigeon"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_pigeon_tint"))->pRect;
		break;
	case UNIT_MOLE:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_mole"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_mole_tint"))->pRect;
		break;
	case UNIT_FERRET:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ferret"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ferret_tint"))->pRect;
		break;
	case UNIT_CHAMELEON:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_chameleon"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_chameleon_tint"))->pRect;
		break;
	case UNIT_FALCON:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_falcon"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_falcon_tint"))->pRect;
		break;
	case UNIT_SKUNK:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_skunk"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_skunk_tint"))->pRect;
		break;
	case UNIT_SNAKE:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_snake"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_snake_tint"))->pRect;
		break;
	case UNIT_BADGER:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_badger"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_badger_tint"))->pRect;
		break;
	case UNIT_BOAR:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_boar"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_boar_tint"))->pRect;
		break;
	case UNIT_FOX:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_fox"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_fox_tint"))->pRect;
		break;
	case UNIT_OWL:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_owl"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_owl_tint"))->pRect;
		break;
	case UNIT_WOLF:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_wolf"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_wolf_tint"))->pRect;
		break;
	case UNIT_BARBEDWIRE:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_barbedwire"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_barbedwire_tint"))->pRect;
		break;
	case UNIT_LANDMINE:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_landmine"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_landmine_tint"))->pRect;
		break;
	case UNIT_BALLON:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ballon"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_ballon_tint"))->pRect;
		break;
	case UNIT_TURRET:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_turret"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_turret_tint"))->pRect;
		break;
	case UNIT_ARTILLERY:
		m_pTexUnitUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_artillery"))->pRect;
		m_pTexUnitTintUI = TextureMgr->GetTexture(TEXT("ui"), TEXT("unit_artillery_tint"))->pRect;
		break;
	case UNIT_ALL:
	default:
#ifdef _DEBUG
		assert(!"UnitUI Select Error!!!! (UNIT_ALL or default)");
#endif
		break;
	}
}

void UUnitFactoryUI::SetFillRatio()
{
	float fRatio = m_iHpFillHeight * m_pTarget->GetHpRatio();
	m_tHpFill.top = m_tHpFill.bottom - (LONG)fRatio;
}

void UUnitFactoryUI::UnitIconRender()
{
	UpdateMatrixWorldUI(0.23f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	int iWidth = m_pTexUnitCircle->right - m_pTexUnitCircle->left;
	int iHeight = m_pTexUnitCircle->bottom - m_pTexUnitCircle->top;
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pTexUnitCircle
		, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	iWidth = m_pTexUnitUI->right - m_pTexUnitUI->left;
	iHeight = m_pTexUnitUI->bottom - m_pTexUnitUI->top;
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pTexUnitUI
		, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	iWidth = m_pTexUnitTintUI->right - m_pTexUnitTintUI->left;
	iHeight = m_pTexUnitTintUI->bottom - m_pTexUnitTintUI->top;
	m_pSprite->Draw(m_pTexMain->pTexture
		, m_pTexUnitTintUI
		, &Vector3(float(iWidth >> 1), float(iHeight >> 1), 0.f)
		, nullptr
		, *m_pColor);
}

void UUnitFactoryUI::HpFillRender()
{
	UpdateMatrixWorldUI(0.5f);

	const int iWidth = m_tHpFill.right - m_tHpFill.left;
	const int iHeight = m_tHpFill.bottom - m_tHpFill.top;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(m_pTexMain->pTexture
		, &m_tHpFill
		, &Vector3(float(iWidth >> 1), float(iHeight - (m_iHpFillHeight >> 1)), 0.f)
		, nullptr
		, D3DCOLOR_ARGB(80, 255, 0, 0));
}
