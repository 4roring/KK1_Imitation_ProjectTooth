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


// CMapToolTab �޽��� ó�����Դϴ�.


BOOL CMapToolTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Ÿ��, ���� �ڵ� �ε�


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapToolTab::LoadDecoObj()
{
}

void CMapToolTab::LoadTile()
{
}


void CMapToolTab::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapToolTab::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapToolTab::OnLbnSelchangeOption()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapToolTab::OnLbnSelchangeDeco()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapToolTab::OnBnClickedLoadFile()
{
	// TODO: FilePath���� Ÿ��, ���ڷ��̼� ������ �о�´�.

}
