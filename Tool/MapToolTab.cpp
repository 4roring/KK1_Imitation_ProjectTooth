// MapToolTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapToolTab.h"
#include "afxdialogex.h"


// CMapToolTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapToolTab, CPropertyPage)

CMapToolTab::CMapToolTab()
	: CPropertyPage(IDD_MAPTOOL)
{

}

CMapToolTab::~CMapToolTab()
{
}

void CMapToolTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_OptionList);
	DDX_Control(pDX, IDC_LIST4, m_DecoList);
}


BEGIN_MESSAGE_MAP(CMapToolTab, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapToolTab::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapToolTab::OnBnClickedLoad)
	ON_LBN_SELCHANGE(IDC_LIST3, &CMapToolTab::OnLbnSelchangeOption)
	ON_LBN_SELCHANGE(IDC_LIST4, &CMapToolTab::OnLbnSelchangeDeco)
	ON_BN_CLICKED(IDC_BUTTON8, &CMapToolTab::OnBnClickedLoadFile)
END_MESSAGE_MAP()


// CMapToolTab 메시지 처리기입니다.


BOOL CMapToolTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: 타일, 데코 자동 로드


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapToolTab::LoadDecoObj()
{
}

void CMapToolTab::LoadTile()
{
}


void CMapToolTab::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapToolTab::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapToolTab::OnLbnSelchangeOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapToolTab::OnLbnSelchangeDeco()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapToolTab::OnBnClickedLoadFile()
{
	// TODO: FilePath에서 타일, 데코레이션 파일을 읽어온다.

}
