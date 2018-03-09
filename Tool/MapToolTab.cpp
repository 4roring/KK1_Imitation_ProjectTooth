// MapToolTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapToolTab.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ItemView.h"
#include "Level.h"


// CMapToolTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapToolTab, CPropertyPage)

CMapToolTab::CMapToolTab()
	: CPropertyPage(IDD_MAPTOOL)
{

}

CMapToolTab::~CMapToolTab()
{
}

void CMapToolTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_OptionList);
	DDX_Control(pDX, IDC_LIST4, m_DecoList);
}


BEGIN_MESSAGE_MAP(CMapToolTab, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNTILESAVE, &CMapToolTab::OnBnClickedCollTileSave)
	ON_BN_CLICKED(IDC_BTNTILELOAD, &CMapToolTab::OnBnClickedCollTileLoad)
	ON_LBN_SELCHANGE(IDC_LIST3, &CMapToolTab::OnLbnSelchangeOption)
	ON_LBN_SELCHANGE(IDC_LIST4, &CMapToolTab::OnLbnSelchangeDeco)
	ON_BN_CLICKED(IDC_BUTTON8, &CMapToolTab::OnBnClickedLoadFile)
	ON_BN_CLICKED(IDC_BTNDECOSAVE, &CMapToolTab::OnBnClickedDecoSave)
	ON_BN_CLICKED(IDC_BTNDECOLOAD, &CMapToolTab::OnBnClickedDecoLoad)
END_MESSAGE_MAP()


// CMapToolTab 메시지 처리기입니다.


BOOL CMapToolTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_pItemView = ToolMgr->GetMainFrame()->m_pItemView;
	m_pLevel = ToolMgr->GetLevel();
	m_bLoad = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapToolTab::OnLbnSelchangeOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_DecoList.SetCurSel(-1);
	int iSelect = m_OptionList.GetCurSel();
	if (iSelect < 0) return;

	CString m_strKey;
	m_OptionList.GetText(iSelect, m_strKey);

	auto iter = m_ItemInfoMap.find(m_strKey.operator LPCWSTR());

	if (iter != m_ItemInfoMap.end())
	{
		m_pItemView->SetItem(iter->second);
		m_pItemView->Invalidate(0);
		m_pLevel->SetOption(iSelect);
		m_pLevel->SetItem(nullptr);
		m_pLevel->SetTileMode(true);
	}
}


void CMapToolTab::OnLbnSelchangeDeco()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_OptionList.SetCurSel(-1);
	int iSelect = m_DecoList.GetCurSel();
	if (iSelect < 0) return;

	CString m_strKey;
	m_DecoList.GetText(iSelect, m_strKey);

	auto iter = m_ItemInfoMap.find(m_strKey.operator LPCWSTR());

	if (iter != m_ItemInfoMap.end())
	{
		m_pItemView->SetItem(iter->second);
		m_pItemView->Invalidate(0);
		m_pLevel->SetItem(iter->second);
		m_pLevel->SetTileMode(false);
	}
}

void CMapToolTab::OnBnClickedLoadFile()
{
	// TODO: FilePath에서 맵과 관련된 파일을 읽어온다.
	UpdateData(TRUE);

	if (true == m_bLoad) return;

	std::wifstream LoadFile;
	LoadFile.open(TEXT("../Data/MapTexture.dat")
		, std::ios::in, std::ios::binary);

	TCHAR szBuf[128];

	TEXTYPE eType;
	int iCount;
	std::wstring wstrObjKey = TEXT("");
	std::wstring wstrStateKey = TEXT("");
	std::wstring wstrPath = TEXT("");

	while (false == LoadFile.eof())
	{
		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		eType = static_cast<TEXTYPE>(_wtoi(szBuf));
		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		iCount = _wtoi(szBuf);
		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		wstrStateKey = szBuf;
		LoadFile.getline(szBuf, sizeof(szBuf), '@');
		wstrObjKey = szBuf;
		LoadFile.getline(szBuf, sizeof(szBuf));
		wstrPath = szBuf;

		TextureMgr->InsertTexture(wstrPath, wstrObjKey, eType
			, wstrStateKey, iCount);

		for (int i = 0; i < iCount; ++i)
		{
			DECO* pDeco = new DECO;
			pDeco->wstrObjKey = wstrObjKey;
			pDeco->wstrStateKey = wstrStateKey;
			pDeco->iCount = i;
			
			std::wstring wstrKey = TEXT("");
			TCHAR szIndex[10] = {};
			_itow_s(i, szIndex, sizeof(szIndex));

			wstrKey = wstrStateKey + szIndex;
			
			auto iter = m_ItemInfoMap.find(wstrKey);
			if (iter != m_ItemInfoMap.end()) continue;

			m_ItemInfoMap.insert(ITEMTEXMAP::value_type(wstrKey, pDeco));
		
			if (0 == wstrStateKey.compare(TEXT("Tile")))
				m_OptionList.AddString(wstrKey.c_str());
			else
				m_DecoList.AddString(wstrKey.c_str());
		}
	}

	m_bLoad = true;

	UpdateData(FALSE);
}

void CMapToolTab::OnBnClickedCollTileSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pLevel->SetFileMode(true);
	SaveCollTile();
	m_pLevel->SetFileMode(false);
}

void CMapToolTab::OnBnClickedCollTileLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pLevel->SetFileMode(true);
	m_pLevel->CollTileRelease();
	LoadCollTile();
	m_pLevel->SetFileMode(false);
}

void CMapToolTab::OnBnClickedDecoSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pLevel->SetFileMode(true);
	SaveDeco();
	m_pLevel->SetFileMode(false);
}


void CMapToolTab::OnBnClickedDecoLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pLevel->SetFileMode(true);
	m_pLevel->DecoRelease();
	LoadDeco();
	m_pLevel->SetFileMode(false);
}

void CMapToolTab::SaveCollTile()
{
	CString strPath;
	GetFilePath(FALSE, strPath);
	
	if (strPath.IsEmpty())
		return;

	HANDLE hFile = CreateFile(strPath
		, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	const VECCOLLTILE* pVecTile = m_pLevel->GetVecCollTile();
	for (auto& pCollTile : *pVecTile)
		WriteFile(hFile, pCollTile, sizeof(COLLTILE), &dwByte, nullptr);

	CloseHandle(hFile);
}

void CMapToolTab::SaveDeco()
{
	CString strPath;
	GetFilePath(FALSE, strPath);

	if (strPath.IsEmpty())
		return;

	HANDLE hFile = CreateFile(strPath
		, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	const VECDECO* pVecDeco = m_pLevel->GetVecDeco();

	DWORD dwByte = 0;
	TCHAR szBuf[128] = {};

	for (auto& pDeco : *pVecDeco)
	{
		lstrcpy(szBuf, pDeco->wstrObjKey.c_str());
		WriteFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);

		lstrcpy(szBuf, pDeco->wstrStateKey.c_str());
		WriteFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);

		WriteFile(hFile, pDeco->vPosition, sizeof(Vector3), &dwByte, nullptr);
		WriteFile(hFile, &pDeco->iCount, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
}

void CMapToolTab::LoadCollTile()
{
	CString strPath = {};
	GetFilePath(TRUE, strPath);

	if (strPath.IsEmpty())
		return;

	HANDLE hFile = CreateFile(strPath
		, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	VECCOLLTILE* pVecTile = m_pLevel->GetVecCollTile();

	while (true)
	{
		COLLTILE* pCollTile = new COLLTILE;
		ReadFile(hFile, pCollTile, sizeof(COLLTILE), &dwByte, nullptr);

		if (dwByte <= 0)
		{
			SafeDelete(pCollTile);
			break;
		}
		pVecTile->push_back(pCollTile);
	}

	CloseHandle(hFile);
}

void CMapToolTab::LoadDeco()
{
	CString strPath;
	GetFilePath(TRUE, strPath);

	if (strPath.IsEmpty())
		return;

	HANDLE hFile = CreateFile(strPath
		, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	VECDECO* pVecDeco = m_pLevel->GetVecDeco();

	DWORD dwByte = 0;
	TCHAR szBuf[128] = {};

	while (true)
	{
		DECO* pDeco = new DECO;

		ReadFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);

		if (dwByte <= 0)
		{
			SafeDelete(pDeco);
			break;
		}

		pDeco->wstrObjKey = szBuf;
		ReadFile(hFile, szBuf, sizeof(szBuf), &dwByte, nullptr);
		pDeco->wstrStateKey = szBuf;

		ReadFile(hFile, pDeco->vPosition, sizeof(Vector3), &dwByte, nullptr);
		ReadFile(hFile, &pDeco->iCount, sizeof(int), &dwByte, nullptr);

		pVecDeco->push_back(pDeco);
	}

	CloseHandle(hFile);
}

void CMapToolTab::GetFilePath(bool bOpenFileDialog, CString& strPath)
{
	CFileDialog Dlg(bOpenFileDialog, TEXT("dat"), TEXT("*.dat")
		, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, TEXT("*.dat||"), this);

	HMODULE hModule = GetModuleHandle(nullptr);

	TCHAR szFullPath[MAX_PATH] = TEXT("");
	VERIFY(GetModuleFileNameW(hModule, szFullPath, MAX_PATH));
	PathRemoveFileSpecW(szFullPath);
	PathRemoveFileSpecW(szFullPath);

	swprintf_s(szFullPath, L"%s\\Data\\", szFullPath);

	Dlg.m_ofn.lpstrInitialDir = szFullPath;
	
	if (Dlg.DoModal() == IDCANCEL)
		return;

	strPath = Dlg.GetPathName();
}



