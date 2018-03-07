// MiniMap.cpp : 구현 파일입니다.
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


// CMiniMap 그리기입니다.

void CMiniMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	Device->Begin();
	
	ToolMgr->GetLevel()->MiniMap();

	Device->End(m_hWnd);
}


// CMiniMap 진단입니다.

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


// CMiniMap 메시지 처리기입니다.
