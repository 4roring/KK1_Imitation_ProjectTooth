#pragma once



// CTabForm �� ���Դϴ�.

class CTabForm : public CFormView
{
	DECLARE_DYNCREATE(CTabForm)

protected:
	CTabForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTabForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAPFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnInitialUpdate();
	virtual void PostNcDestroy();

private:
	class CMySheet* m_pMySheet = nullptr;
};


