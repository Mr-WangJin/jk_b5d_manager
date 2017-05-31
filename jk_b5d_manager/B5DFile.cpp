#include "stdafx.h"
#include "B5DFile.h"

B5DFile::B5DFile()
{
}

B5DFile::B5DFile(wxString fineName, wxString versionNum, wxString fullPath)
	: m_FileName(fineName)
	, m_FullPath(fullPath)
	, m_VersionNum(versionNum)
{
}

B5DFile::~B5DFile()
{
}

void B5DFile::setFileName(const wxString & fileName)
{
	m_FileName = fileName;
}

wxString B5DFile::getFileName()
{
	return m_FileName;
}

void B5DFile::setVersionNum(const wxString & versionNum)
{
	m_VersionNum = versionNum;
}

wxString B5DFile::getVersionNum()
{
	return m_VersionNum;
}

void B5DFile::setFullPath(const wxString & path)
{
	m_FullPath = path;
}

wxString B5DFile::getFullPath()
{
	return m_FullPath;
}
