#pragma once

#include "wx/dataview.h"

class DMB5DFiles;

class B5DDataModel : public wxDataViewVirtualListModel
{
public:
	enum
	{
		Col_Name = 0,
		Col_Version,
		Col_Path,
	};

	B5DDataModel(DMB5DFiles *pB5dFiles);

	void refresh();

	void Prepend(const wxString &text);
	void DeleteItem(const wxDataViewItem &item);
	void DeleteItems(const wxDataViewItemArray &items);


	// implementation of base class virtuals to define model

	virtual unsigned int GetColumnCount() const;


	virtual wxString GetColumnType(unsigned int col) const
	{
		return wxT("string");
	}

	virtual void GetValueByRow(wxVariant &variant, unsigned int row, unsigned int col) const;
	virtual bool GetAttrByRow(unsigned int row, unsigned int col,wxDataViewItemAttr &attr) const;
	virtual bool SetValueByRow(const wxVariant &variant,unsigned int row, unsigned int col);

private:
	DMB5DFiles* m_pB5DFiles;
};
