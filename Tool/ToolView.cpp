
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "MiniMap.h"
#include "Level.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
HWND g_hMain;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	Device->Begin();

	ToolMgr->GetLevel()->Render();

	Device->End(m_hWnd);
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetWindow();

	if (FAILED(Device->InitDevice()))
		AfxMessageBox(TEXT("Device Initialize Failed!!!"));

	if (FAILED(ToolMgr->Initialize()))
		AfxMessageBox(TEXT("ToolMgr Initialize Failed!!!"));

	ToolMgr->SetMainFrame(m_pMainFrame);

	m_pDevice = Device->GetDevice();
	m_pSprite = Device->GetSprite();

	g_hWnd = m_hWnd;

	SetTimer(0, 10, nullptr);
}


void CToolView::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ToolMgr->DestroyInstance();
	TextureMgr->DestroyInstance();
	Device->DestroyInstance();
	KeyMgr->DestroyInstance();
	
	CView::PostNcDestroy();
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nChar == VK_ESCAPE)
		AfxGetMainWnd()->PostMessage(WM_CLOSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CToolView::SetWindow()
{
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	RECT rcFrameWindows;

	m_pMainFrame->GetWindowRect(&rcFrameWindows);
	SetRect(&rcFrameWindows, 0, 0
		, rcFrameWindows.right - rcFrameWindows.left
		, rcFrameWindows.bottom - rcFrameWindows.top);

	RECT rcMainView;
	GetClientRect(&rcMainView);

	int fRowFrm = rcFrameWindows.right - rcMainView.right;
	int fColFrm = rcFrameWindows.bottom - rcMainView.bottom;

	m_pMainFrame->SetWindowPos(nullptr, 0, 0, WINCX + fRowFrm, WINCY + fColFrm, SWP_NOZORDER);
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_pMainFrame->m_pMiniMap->Invalidate(0);
	ToolMgr->GetLevel()->Update();

	CView::OnMouseMove(nFlags, point);
}


void CToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (KeyMgr->KeyPress('A'))
		ToolMgr->SetScroll(D3DXVECTOR3(-100.f, 0.f, 0.f));

	if (KeyMgr->KeyPress('D'))
		ToolMgr->SetScroll(D3DXVECTOR3(100.f, 0.f, 0.f));

	if (KeyMgr->KeyPress('W'))
		ToolMgr->SetScroll(D3DXVECTOR3(0.f, -100.f, 0.f));

	if (KeyMgr->KeyPress('S'))
		ToolMgr->SetScroll(D3DXVECTOR3(0.f, 100.f, 0.f));

	if (KeyMgr->KeyDown('Z'))
		ToolMgr->SetCollTileRender();

	ToolMgr->GetLevel()->Picking();

	KeyMgr->Update();

	Invalidate(0);

	CView::OnTimer(nIDEvent);
}


BOOL CToolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (zDelta > 0.f)
		ToolMgr->SetZoom(0.5f);

	if (zDelta < 0.f)
		ToolMgr->SetZoom(-0.5f);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
