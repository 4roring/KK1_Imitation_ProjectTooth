#include "stdafx.h"
#include "PathInfo.h"


CPathInfo::CPathInfo()
{
}


CPathInfo::~CPathInfo()
{
}

const std::wstring CPathInfo::ConvertRelativePath(const std::wstring & wstrFullPath)
{
	TCHAR szRelativePath[MAX_PATH] = TEXT("");
	TCHAR szDirPath[MAX_PATH] = TEXT("");

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	PathRelativePathTo((LPWSTR)szRelativePath
		, szDirPath, FILE_ATTRIBUTE_DIRECTORY
		, wstrFullPath.c_str(), FILE_ATTRIBUTE_NORMAL);

	return szRelativePath;
}

void CPathInfo::DirInfoExtraction(const std::wstring & wstrPath, TEXPATHLIST & TexPathList, TEXTYPE eType)
{
	CFileFind Find;
	Find.FindFile(wstrPath.c_str());

	int iContinue = true;

	while (1 == iContinue)
	{
		iContinue = Find.FindNextFile();
		if (Find.IsDots())
			continue;

		if (Find.IsDirectory())
			DirInfoExtraction(std::wstring(Find.GetFilePath() + L"\\*.*"), TexPathList, eType);
		else
		{
			if (Find.IsSystem())
				continue;

			TCHAR szPathBuf[MAX_PATH] = TEXT("");
			std::wstring wstrTextureName = TEXT("");

			lstrcpy(szPathBuf, Find.GetFilePath().operator LPCWSTR());

			if (lstrcmp(PathFindExtension(szPathBuf), TEXT(".png")))
				continue;

			TEXPATH* pTexPath = new TEXPATH;

			if (eType == TEX_MULTI)
			{
				PathRemoveFileSpec(szPathBuf);
				pTexPath->iCount = DirFileCount(szPathBuf);
				wstrTextureName = Find.GetFileTitle().operator LPCWSTR();
				wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + TEXT("%d.png");
			}
			else
			{
				lstrcpy(szPathBuf, Find.GetFileTitle().operator LPCWSTR());
				pTexPath->wstrObjKey = PathFindFileName(szPathBuf);
			}
				
			TCHAR szBuf[MAX_PATH] = TEXT("");
			lstrcpy(szBuf, Find.GetFilePath().operator LPCWSTR());

			if(eType == TEX_MULTI)
				PathRemoveFileSpec(szBuf);
			PathCombine(szBuf, szBuf, (LPWSTR)wstrTextureName.c_str());
			pTexPath->wstrPath = ConvertRelativePath(szBuf);

			if (eType == TEX_MULTI) // 멀티텍스처일때에만 상태키와 Obj키로 저장. 
			{
				PathRemoveFileSpec(szBuf);
				pTexPath->wstrStateKey = PathFindFileName(szBuf);

				PathRemoveFileSpec(szBuf);
				pTexPath->wstrObjKey = PathFindFileName(szBuf);

				iContinue = 0;
			}
			pTexPath->eType = eType;
			TexPathList.push_back(pTexPath);
		}
	}
}

int CPathInfo::DirFileCount(const std::wstring & wstrPath)
{
	std::wstring wstrTemp = wstrPath + TEXT("\\*.png");

	CFileFind Find;
	Find.FindFile(wstrTemp.c_str());

	int iFileCount = 0;
	int iContinue = 1;

	while (1 == iContinue)
	{
		iContinue = Find.FindNextFile();

		if (false == Find.IsDirectory())
			++iFileCount;
	}
	return iFileCount;
}
