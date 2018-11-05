#pragma once


// COtherTab ��ȭ �����Դϴ�.

#include "FilePath.h"
#include "UnitTool.h"

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
public:
	afx_msg void OnBnClickedFilePath();
	afx_msg void OnBnClickedUnitTool();

public:
	CFilePath m_FilePath;
	CUnitTool m_UnitTool;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnEnable(BOOL bEnable);
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
};
