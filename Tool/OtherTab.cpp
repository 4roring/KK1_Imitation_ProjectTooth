// OtherTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "OtherTab.h"
#include "afxdialogex.h"


// COtherTab ��ȭ �����Դϴ�.

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


// COtherTab �޽��� ó�����Դϴ�.


void COtherTab::OnBnClickedFilePath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_FilePath.GetSafeHwnd() == NULL)
		m_FilePath.Create(IDD_FILEPATH);

	m_FilePath.ShowWindow(SW_SHOW);
}


void COtherTab::OnBnClickedUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_UnitTool.GetSafeHwnd() == NULL)
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);
}
