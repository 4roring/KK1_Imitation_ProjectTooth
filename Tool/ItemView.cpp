// ItemView.cpp : ���� �����Դϴ�.
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


// CItemView �׸����Դϴ�.

void CItemView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	Device->Begin();



	Device->End(m_hWnd);
}


// CItemView �����Դϴ�.

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


// CItemView �޽��� ó�����Դϴ�.
