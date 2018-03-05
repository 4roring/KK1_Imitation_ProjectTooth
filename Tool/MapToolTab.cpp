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
}


BEGIN_MESSAGE_MAP(CMapToolTab, CPropertyPage)
END_MESSAGE_MAP()


// CMapToolTab 메시지 처리기입니다.


BOOL CMapToolTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
