#pragma once



class B5DFile
{
public:
	B5DFile();
	B5DFile(wxString fineName, wxString versionNum, wxString fullPath);
	~B5DFile();

	void setFileName(const wxString &fileName);
	wxString getFileName();
	void setVersionNum(const wxString &versionNum);
	wxString getVersionNum();
	void setFullPath(const wxString &path);
	wxString getFullPath();

private:
	wxString m_FileName;
	wxString m_FullPath;
	wxString m_VersionNum;

};


