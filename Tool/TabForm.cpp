// TabForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "TabForm.h"
#include "MySheet.h"

// CTabForm

IMPLEMENT_DYNCREATE(CTabForm, CFormView)

CTabForm::CTabForm()
	: CFormView(IDD_TAPFORM)
{

}

CTabForm::~CTabForm()
{
}

void CTabForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabForm, CFormView)
END_MESSAGE_MAP()


// CTabForm �����Դϴ�.

#ifdef _DEBUG
void CTabForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTabForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTabForm �޽��� ó�����Դϴ�.


void CTabForm::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SafeDelete(m_pMySheet);

	CFormView::PostNcDestroy();
}


void CTabForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMySheet = new CMySheet;
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_pMySheet->MoveWindow(0, 0, 250, 500);
}
