#pragma once


// CMapToolTab ��ȭ �����Դϴ�.


class CMapToolTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CMapToolTab)

public:
	CMapToolTab();
	virtual ~CMapToolTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
