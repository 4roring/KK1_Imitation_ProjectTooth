#pragma once


// CMiniMap ���Դϴ�.
class CIsometric;
class CMiniMap : public CView
{
	DECLARE_DYNCREATE(CMiniMap)

protected:
	CMiniMap();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMiniMap();

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
};

