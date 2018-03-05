#pragma once


// CMapToolTab 대화 상자입니다.


class CMapToolTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CMapToolTab)

public:
	CMapToolTab();
	virtual ~CMapToolTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
