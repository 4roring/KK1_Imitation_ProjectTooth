// OtherTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "OtherTab.h"
#include "afxdialogex.h"


// COtherTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(COtherTab, CPropertyPage)

COtherTab::COtherTab()
	: CPropertyPage(IDD_OTHERTAB)
{

}

COtherTab::~COtherTab()
{
}

void COtherTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COtherTab, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &COtherTab::OnBnClickedFilePath)
	ON_BN_CLICKED(IDC_BUTTON2, &COtherTab::OnBnClickedUnitTool)
END_MESSAGE_MAP()


// COtherTab 메시지 처리기입니다.


void COtherTab::OnBnClickedFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_FilePath.GetSafeHwnd() == NULL)
		m_FilePath.Create(IDD_FILEPATH);

	m_FilePath.ShowWindow(SW_SHOW);
}


void COtherTab::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_UnitTool.GetSafeHwnd() == NULL)
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);
}
