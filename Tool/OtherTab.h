#pragma once


// COtherTab ��ȭ �����Դϴ�.

class COtherTab : public CPropertyPage
{
	DECLARE_DYNAMIC(COtherTab)

public:
	COtherTab();
	virtual ~COtherTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OTHERTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
