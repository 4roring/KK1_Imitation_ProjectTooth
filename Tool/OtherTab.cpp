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
END_MESSAGE_MAP()


// COtherTab 메시지 처리기입니다.
