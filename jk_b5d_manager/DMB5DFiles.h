#pragma once

#include <vector>

class B5DFile;

class DMB5DFiles
{
public:
	DMB5DFiles();
	~DMB5DFiles();

	void initialize();
	void addFile(B5DFile* pB5DFile);
	void deleteFile(const int &idx);
	void saveB5DFile();

	B5DFile* getB5DFile(const int &idx);
	int fileCount();


	inline B5DFile* operator [] (const int &idx) const;

private:
	wxString m_jsonStr;

	std::vector<B5DFile*> m_VecFiles;
};

inline B5DFile* DMB5DFiles::operator [] (const int &idx) const
{
	return m_VecFiles[idx];
}
