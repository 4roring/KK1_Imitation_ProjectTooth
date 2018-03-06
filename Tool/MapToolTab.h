#pragma once
#include "afxwin.h"


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

private:
	void LoadDecoObj();
	void LoadTile();
public:
	CListBox m_OptionList;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnLbnSelchangeOption();
	afx_msg void OnLbnSelchangeDeco();
	CListBox m_DecoList;
	afx_msg void OnBnClickedLoadFile();
};
