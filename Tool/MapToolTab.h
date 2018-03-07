#pragma once
#include "afxwin.h"


// CMapToolTab 대화 상자입니다.

typedef std::unordered_map<std::wstring, DECO*> ITEMTEXMAP;

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

public:
	afx_msg void OnBnClickedCollTileSave();
	afx_msg void OnBnClickedCollTileLoad();
	afx_msg void OnBnClickedDecoSave();
	afx_msg void OnBnClickedDecoLoad();
	afx_msg void OnLbnSelchangeOption();
	afx_msg void OnLbnSelchangeDeco();
	afx_msg void OnBnClickedLoadFile();

private:
	void SaveCollTile();
	void SaveDeco();
	void LoadCollTile();
	void LoadDeco();
	void GetFilePath(bool bOpenFileDialog, CString& strPath);

private:
	CListBox m_OptionList;
	CListBox m_DecoList;

private:
	ITEMTEXMAP m_ItemInfoMap;

private:
	class CItemView* m_pItemView;
	class CLevel* m_pLevel;

private:
	bool m_bLoad;
};
