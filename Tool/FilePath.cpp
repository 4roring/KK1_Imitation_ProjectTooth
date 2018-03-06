// FilePath.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "FilePath.h"
#include "afxdialogex.h"
#include "PathInfo.h"

// CFilePath 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFilePath, CDialog)

CFilePath::CFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FILEPATH, pParent)
{

}

CFilePath::~CFilePath()
{
	Release();
}

void CFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_FilePathList);
	DDX_Control(pDX, IDC_LIST1, m_TexTypeList);
}


BEGIN_MESSAGE_MAP(CFilePath, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFilePath::OnLbnSelTexOption)
	ON_BN_CLICKED(IDC_BUTTON1, &CFilePath::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CFilePath::OnBnClickedLoad)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON6, &CFilePath::OnBnClickedRemove)
END_MESSAGE_MAP()


// CFilePath 메시지 처리기입니다.


void CFilePath::OnLbnSelTexOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_TexTypeList.GetCurSel();

	if (iSelect < 0) return;

	CString m_strSelectName;
	m_TexTypeList.GetText(iSelect, m_strSelectName);
	
	if (m_strSelectName == TEXT("SingleTexture"))
		m_eTexType = TEX_SINGLE;
	else if (m_strSelectName == TEXT("MultiTexture"))
		m_eTexType = TEX_MULTI;
	else if (m_strSelectName == TEXT("AtlasTexture"))
		m_eTexType = TEX_ATLAS;

	UpdateData(FALSE);
}


void CFilePath::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CFileDialog Dlg(FALSE, TEXT("dat"), TEXT("*.dat")
		, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, TEXT("*.dat"), this);

	HMODULE hModule = GetModuleHandle(nullptr);

	TCHAR szFullPath[MAX_PATH] = L"";
	VERIFY(GetModuleFileNameW(hModule, szFullPath, MAX_PATH));
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);

	swprintf_s(szFullPath, L"%s\\Data\\", szFullPath);

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	if (Dlg.DoModal() == IDCANCEL)
		return;

	std::wofstream SaveFile;
	SaveFile.open(Dlg.GetPathName(), std::ios::out, std::ios::binary);

	int iCount = 0;
	for (auto& pTexPath : m_TexPathList)
	{
		++iCount;
		
		switch (pTexPath->eType)
		{
		case TEX_MULTI:
			SaveFile << TEXT("MULTI@") << pTexPath->iCount;
			SaveFile << TEXT("@") << pTexPath->wstrStateKey;
			break;
		case TEX_ATLAS:
		case TEX_SINGLE:
			SaveFile << pTexPath->eType;
			break;
		}
		SaveFile << TEXT("@") << pTexPath->wstrObjKey;

		if(iCount == m_TexPathList.size())
			SaveFile << TEXT("@") << pTexPath->wstrPath << std::flush;
		else
			SaveFile << TEXT("@") << pTexPath->wstrPath << std::endl;
	}
	SaveFile.close();

	UpdateData(FALSE);
}


void CFilePath::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);



	UpdateData(FALSE);
}

void CFilePath::Release()
{
	std::for_each(m_TexPathList.begin(), m_TexPathList.end(), SafeDelete<TEXPATH*>);
	m_TexPathList.clear();
}

void CFilePath::OnBnClickedRemove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	Release();
	m_FilePathList.ResetContent();

	UpdateData(FALSE);
}

BOOL CFilePath::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_TexTypeList.AddString(TEXT("SingleTexture"));
	m_TexTypeList.AddString(TEXT("MultiTexture"));
	m_TexTypeList.AddString(TEXT("AtlasTexture"));

	m_TexTypeList.SelectString(0, TEXT("SingleTexture"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFilePath::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);

	m_FilePathList.ResetContent();

	int iFileCount = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szFullPath[MAX_PATH] = TEXT("");

	CPathInfo PathInfo;

	for (int i = 0; i < iFileCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_PATH);
		PathInfo.DirInfoExtraction(szFullPath, m_TexPathList, m_eTexType);

		std::wstring wstrCombined = TEXT("");
		TCHAR szBuf[128] = L"";

		for (auto& pTexPath : m_TexPathList)
		{
			switch (m_eTexType)
			{
			case TEX_SINGLE:
				wstrCombined = TEXT("SINGLE");
				break;
			case TEX_MULTI:
				_itow_s(pTexPath->iCount, szBuf, 10);
				wstrCombined = TEXT("MULTI@");
				wstrCombined +=	szBuf;
				wstrCombined += TEXT("@") + pTexPath->wstrStateKey;
				break;
			case TEX_ATLAS:
				wstrCombined = TEXT("ATLAS");
				break;
			}	
			wstrCombined += TEXT("@") + pTexPath->wstrObjKey;
			wstrCombined += TEXT("@") + pTexPath->wstrPath;

			m_FilePathList.AddString(wstrCombined.c_str());
		}
	}

	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

