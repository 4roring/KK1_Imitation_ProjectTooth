// TabForm.cpp : 구현 파일입니다.
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


// CTabForm 진단입니다.

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


// CTabForm 메시지 처리기입니다.


void CTabForm::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	SafeDelete(m_pMySheet);

	CFormView::PostNcDestroy();
}


void CTabForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pMySheet = new CMySheet;
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_pMySheet->MoveWindow(0, 0, 250, 500);
}
