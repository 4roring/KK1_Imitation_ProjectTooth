// MiniMap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MiniMap.h"
#include "Level.h"

// CMiniMap

IMPLEMENT_DYNCREATE(CMiniMap, CView)

CMiniMap::CMiniMap()
{

}

CMiniMap::~CMiniMap()
{
}

BEGIN_MESSAGE_MAP(CMiniMap, CView)
END_MESSAGE_MAP()


// CMiniMap �׸����Դϴ�.

void CMiniMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	Device->Begin();
	
	ToolMgr->GetLevel()->MiniMap();

	Device->End(m_hWnd);
}


// CMiniMap �����Դϴ�.

#ifdef _DEBUG
void CMiniMap::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniMap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniMap �޽��� ó�����Դϴ�.
