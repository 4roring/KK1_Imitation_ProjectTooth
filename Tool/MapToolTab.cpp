// MapToolTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapToolTab.h"
#include "afxdialogex.h"


// CMapToolTab ��ȭ �����Դϴ�.

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


// CMapToolTab �޽��� ó�����Դϴ�.


BOOL CMapToolTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
