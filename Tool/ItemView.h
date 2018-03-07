#pragma once


// CItemView ���Դϴ�.
class CItemView : public CView
{
	DECLARE_DYNCREATE(CItemView)

protected:
	CItemView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CItemView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetItem(const DECO* pItem) { m_pItem = pItem; }

private:
	const DECO* m_pItem = nullptr;
};


