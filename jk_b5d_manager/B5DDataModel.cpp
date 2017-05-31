#include "stdafx.h"
#include "B5DDataModel.h"
#include "DMB5DFiles.h"
#include "B5DFile.h"

static int my_sort_reverse(int *v1, int *v2)
{
	return *v2 - *v1;
}

static int my_sort(int *v1, int *v2)
{
	return *v1 - *v2;
}


B5DDataModel::B5DDataModel(DMB5DFiles *pB5dFiles) 
	: wxDataViewVirtualListModel()
	, m_pB5DFiles(pB5dFiles)
{
	this->refresh();
}

void B5DDataModel::refresh()
{
	this->Reset(m_pB5DFiles->fileCount());
}

void B5DDataModel::Prepend(const wxString &text)
{
	RowPrepended();
}

void B5DDataModel::DeleteItem(const wxDataViewItem &item)
{
	unsigned int row = GetRow(item);

	RowDeleted(row);
}

void B5DDataModel::DeleteItems(const wxDataViewItemArray &items)
{
	unsigned i;
	wxArrayInt rows;
	for (i = 0; i < items.GetCount(); i++)
	{
		unsigned int row = GetRow(items[i]);
		rows.Add(row);
	}

	if (rows.GetCount() == 0)
	{
		// none of the selected items were in the range of the items
		// which we store... for simplicity, don't allow removing them
		wxLogError("Cannot remove rows with an index greater than %d");
		return;
	}

	// Sort in descending order so that the last
	// row will be deleted first. Otherwise the
	// remaining indeces would all be wrong.
	rows.Sort(my_sort_reverse);

	// This is just to test if wxDataViewCtrl can
	// cope with removing rows not sorted in
	// descending order
	rows.Sort(my_sort);
	RowsDeleted(rows);
}

unsigned int B5DDataModel::GetColumnCount() const
{
	return Col_Path + 1;
}

void B5DDataModel::GetValueByRow(wxVariant &variant,
	unsigned int row, unsigned int col) const
{
	B5DFile* pB5DFile = (*m_pB5DFiles)[row];
	switch (col)
	{
	case Col_Name:
		variant = pB5DFile->getFileName();
		break;
	case Col_Path:
		variant = pB5DFile->getFullPath();
		break;
	case Col_Version:
		variant = pB5DFile->getVersionNum();
		break;
	default:
		break;
	}
}

bool B5DDataModel::GetAttrByRow(unsigned int row, unsigned int col,	wxDataViewItemAttr &attr) const
{
	return true;
}

bool B5DDataModel::SetValueByRow(const wxVariant &variant,unsigned int row, unsigned int col)
{
	B5DFile* pB5DFile = m_pB5DFiles->getB5DFile(row);
	switch (col)
	{
	case Col_Name:
		pB5DFile->setFileName(variant);
		break;
	case Col_Path:
		pB5DFile->setFullPath(variant);
		break;
	case Col_Version:
		pB5DFile->setVersionNum(variant);
		break;
	default:
		break;
	}
	return false;
}