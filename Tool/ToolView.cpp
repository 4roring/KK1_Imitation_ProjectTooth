
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	Device->Begin();

	ToolMgr->GetLevel()->Render();

	Device->End(m_hWnd);
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ToolMgr->DestroyInstance();
	TextureMgr->DestroyInstance();
	Device->DestroyInstance();
	KeyMgr->DestroyInstance();
	
	CView::PostNcDestroy();
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_pMainFrame->m_pMiniMap->Invalidate(0);
	ToolMgr->GetLevel()->Update();

	CView::OnMouseMove(nFlags, point);
}


void CToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (zDelta > 0.f)
		ToolMgr->SetZoom(0.5f);

	if (zDelta < 0.f)
		ToolMgr->SetZoom(-0.5f);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
