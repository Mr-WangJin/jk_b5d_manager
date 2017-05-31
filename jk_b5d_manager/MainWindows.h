#pragma once

#include "wx/frame.h"
#include "wx/event.h"
#include "wx/setup.h"

class B5DDataModel;
class wxDataViewCtrl;
class DMB5DFiles;



class MainWindows : public wxFrame
{
public:
	// ctor(s)
	MainWindows(const wxString& title);
	~MainWindows();

protected:
	void OnClose(wxCloseEvent& event);

private:
	void initilize();

	wxDataViewCtrl* createTableView(wxPanel* parent, unsigned long style = 0);

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void addB5D(wxCommandEvent& event);
	void runB5D(wxCommandEvent& event);
	void saveB5D(wxCommandEvent& event);
	void deleteB5D(wxCommandEvent& event);

private:
	wxObjectDataPtr<B5DDataModel> m_list_model;
	DMB5DFiles* m_pB5DFiles;
	wxDataViewCtrl* m_pDataViewer;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};
