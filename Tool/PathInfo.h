#pragma once
class CPathInfo
{
public:
	CPathInfo();
	~CPathInfo();

public:
	const std::wstring ConvertRelativePath(const std::wstring& wstrFullPath);
	void DirInfoExtraction(const std::wstring& wstrPath, TEXPATHLIST& TexInfoList, TEXTYPE eType);
	int DirFileCount(const std::wstring& wstrPath);
};

