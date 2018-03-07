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

	if (m_pItem != nullptr)
	{
		const TEXINFO* pTexture = TextureMgr->GetTexture(m_pItem->wstrObjKey, m_pItem->wstrStateKey, m_pItem->iCount);

		D3DXMATRIX matScale, matTrans;
		D3DXMatrixScaling(&matScale, 10.f, 10.f, 1.f);
		D3DXMatrixTranslation(&matTrans, 512.f, 500.f, 0.f);

		matScale *= matTrans;
		Device->GetSprite()->SetTransform(&matScale);
		Device->GetSprite()->Draw(pTexture->pTexture, nullptr
			, &D3DXVECTOR3(float(pTexture->tImageInfo.Width >> 1), float(pTexture->tImageInfo.Height >> 1), 0.f)
			, nullptr,D3DCOLOR_ARGB(255, 255, 255, 255));
	}

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
