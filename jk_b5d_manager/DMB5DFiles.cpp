#include "stdafx.h"
#include "DMB5DFiles.h"
#include "B5DFile.h"
#include "wx/txtstrm.h"
#include "wx/wfstream.h"
#include "wx/textfile.h"
#include "json/reader.h"
#include "json/writer.h"


const wxString B5D_JSON_DIR(L"b5d.json");

DMB5DFiles::DMB5DFiles()
{
	this->initialize();
}

DMB5DFiles::~DMB5DFiles()
{
	for each (B5DFile* file in m_VecFiles)
	{
		delete file;
	}
	m_VecFiles.clear();
}

void DMB5DFiles::initialize()
{
// 	wxFileInputStream input(B5D_JSON_DIR);
// 	wxTextInputStream text(input);
// 
// 	while (input.IsOk() && !input.Eof())
// 	{
// 		m_jsonStr += text.ReadLine();
// 	}
	wxTextFile tfile;
	tfile.Open(B5D_JSON_DIR);
	m_jsonStr += tfile.GetFirstLine();
	while (!tfile.Eof())
	{
		m_jsonStr += tfile.GetNextLine();
	}

	Json::Reader reader;
	Json::Value result;
	reader.parse(m_jsonStr.ToStdString(), result);

	Json::Value b5DFiles = result["B5DFiles"];
	for (int i = 0; i< b5DFiles.size(); ++i)
	{
		Json::Value b5dFile = b5DFiles[i];
		
		B5DFile* pB5DFile = new B5DFile;
		pB5DFile->setFileName(b5dFile["name"].asString());
		pB5DFile->setFullPath(b5dFile["path"].asString());
		pB5DFile->setVersionNum(b5dFile["versionNum"].asString());

		m_VecFiles.push_back(pB5DFile);
	}
}

void DMB5DFiles::addFile(B5DFile* pB5DFile)
{
	assert(pB5DFile);

	m_VecFiles.push_back(pB5DFile);
}

void DMB5DFiles::deleteFile(const int & idx)
{
	if (m_VecFiles.size() <= idx)
		return;

	std::vector<B5DFile*>::iterator iterTemp = std::find(m_VecFiles.begin(), m_VecFiles.end(), m_VecFiles[idx]);
	if (iterTemp != m_VecFiles.end())
	{
		m_VecFiles.erase(iterTemp);
	}
}

bool WriteFile(const char* fileName, const char *_Mode, const char *buffer, const long &lSize)
{
	FILE *pFile;
	pFile = fopen(fileName, _Mode);
	if (pFile == NULL) { fputs("File error", stderr); return false; }

	fwrite(buffer, sizeof(char), lSize, pFile);

	fclose(pFile);
	return true;
}

void DMB5DFiles::saveB5DFile()
{
	Json::Value root;
	Json::Value arrayObj;

	for each (B5DFile* pB5DFile in m_VecFiles)
	{
		Json::Value item;
		item["name"] = pB5DFile->getFileName().ToStdString();
		item["path"] = pB5DFile->getFullPath().ToStdString();
		item["versionNum"] = pB5DFile->getVersionNum().ToStdString();
		arrayObj.append(item);
	}

	root["B5DFiles"] = arrayObj;

	std::string out = root.toStyledString();
	WriteFile(B5D_JSON_DIR.ToStdString().c_str(), "w", out.c_str(), out.size());
}


B5DFile * DMB5DFiles::getB5DFile(const int &idx)
{
	return m_VecFiles[idx];
}

int DMB5DFiles::fileCount()
{
	return m_VecFiles.size();
}
