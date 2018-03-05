#pragma once



// CMySheet
#include "MapToolTab.h"
#include "OtherTab.h"

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)

public:
	CMySheet();
	CMySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMySheet();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CMapToolTab m_pMapToolTab;
	COtherTab m_pOtherTab;
};


