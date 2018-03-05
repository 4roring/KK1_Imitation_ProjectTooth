// ItemView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItemView.h"


// CItemView

IMPLEMENT_DYNCREATE(CItemView, CView)

CItemView::CItemView()
{

}

CItemView::~CItemView()
{
}

BEGIN_MESSAGE_MAP(CItemView, CView)
END_MESSAGE_MAP()


// CItemView 그리기입니다.

void CItemView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	Device->Begin();



	Device->End(m_hWnd);
}


// CItemView 진단입니다.

#ifdef _DEBUG
void CItemView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CItemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CItemView 메시지 처리기입니다.
