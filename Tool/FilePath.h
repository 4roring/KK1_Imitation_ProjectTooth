#pragma once
#include "afxwin.h"


// CFilePath 대화 상자입니다.

class CFilePath : public CDialog
{
	DECLARE_DYNAMIC(CFilePath)

public:
	CFilePath(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFilePath();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_FilePathList;
	CListBox m_TexTypeList;
	afx_msg void OnLbnSelTexOption();
	afx_msg void OnBnClickedCollTileSave();
	afx_msg void OnBnClickedCollTileLoad();

public:
	void Release();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedRemove();

private:
	TEXTYPE m_eTexType = TEX_SINGLE;
	TEXPATHLIST m_TexPathList;

};
