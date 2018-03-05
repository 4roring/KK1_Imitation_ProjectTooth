#pragma once


// COtherTab 대화 상자입니다.

class COtherTab : public CPropertyPage
{
	DECLARE_DYNAMIC(COtherTab)

public:
	COtherTab();
	virtual ~COtherTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OTHERTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
