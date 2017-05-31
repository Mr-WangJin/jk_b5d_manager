#include "stdafx.h"
#include "MainWindows.h"
#include "B5DDataModel.h"
#include "DMB5DFiles.h"
#include "B5DFile.h"

#include <Windows.h>
#include "wx/filepicker.h"
#include "wx/image.h"
#include "wx/imagpng.h"
#include "wx/dataview.h"


enum {
	ID_ATTR_CTRL = wxID_HIGHEST + 1,

	ID_ADD_B5D,
	ID_SAVE_B5D,
	ID_Delete_B5D,

	ID_RUN_B5D,
};


wxBEGIN_EVENT_TABLE(MainWindows, wxFrame)

EVT_CLOSE(MainWindows::OnClose)

EVT_MENU(wxID_ADD, MainWindows::addB5D)
EVT_MENU(ID_SAVE_B5D, MainWindows::saveB5D)
EVT_MENU(ID_Delete_B5D, MainWindows::deleteB5D)
EVT_MENU(wxID_EXIT, MainWindows::OnQuit)


EVT_BUTTON(ID_RUN_B5D, MainWindows::runB5D)

wxEND_EVENT_TABLE()


// frame constructor
MainWindows::MainWindows(const wxString& title)
	: wxFrame((wxFrame *)NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(500, 300))
{
	SetIcon(wxICON(sample));
	m_pB5DFiles = new DMB5DFiles;

	this->initilize();
}

MainWindows::~MainWindows()
{
	delete m_pB5DFiles;
	m_pB5DFiles = nullptr;
}

void MainWindows::initilize()
{
	wxMenu *pMenu = new wxMenu;
	pMenu->Append(wxID_ADD, "Add");
	pMenu->Append(ID_SAVE_B5D, "Save");
	pMenu->Append(ID_Delete_B5D, "Delete");
	pMenu->Append(wxID_EXIT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(pMenu, _("&File"));
	SetMenuBar(menuBar);

	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *pPanel = new wxPanel(this, wxID_ANY);
	wxDataViewCtrl* pDataViewCtrl = this->createTableView(pPanel);

	const wxSizerFlags border = wxSizerFlags().DoubleBorder();
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	button_sizer->Add(new wxButton(pPanel, ID_RUN_B5D, "Run B5D"), border);

	wxSizer* pPanelSizer = new wxBoxSizer(wxVERTICAL);
	pPanelSizer->Add(pDataViewCtrl, 1, wxGROW | wxALL, 5);
	pPanelSizer->Add(button_sizer);

	pPanel->SetSizerAndFit(pPanelSizer);

	mainSizer->Add(pPanel, 1, wxGROW | wxALL, 5);
	this->SetSizer(mainSizer);
}

wxDataViewCtrl* MainWindows::createTableView(wxPanel* parent, unsigned long style/* = 0*/)
{
	m_pDataViewer = new wxDataViewCtrl(parent, ID_ATTR_CTRL, wxDefaultPosition,wxDefaultSize, style);

	m_list_model = new B5DDataModel(m_pB5DFiles);
	m_pDataViewer->AssociateModel(m_list_model.get());

	// the various columns
	m_pDataViewer->AppendTextColumn(wxT("B5D Name"), B5DDataModel::Col_Name, wxDATAVIEW_CELL_EDITABLE,wxCOL_WIDTH_AUTOSIZE);
	m_pDataViewer->AppendTextColumn(wxT("Version"), B5DDataModel::Col_Version, wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE);
	m_pDataViewer->AppendTextColumn(wxT("Patn"), B5DDataModel::Col_Path, wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE);

	return m_pDataViewer;
}

void MainWindows::OnClose(wxCloseEvent& event)
{
	m_pB5DFiles->saveB5DFile();


	Destroy();  // you may also do:  event.Skip();
				// since the default event handler does call Destroy(), too
}

void MainWindows::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	m_pB5DFiles->saveB5DFile();
	// true is to force the frame to close
	Close(true);
}

void MainWindows::addB5D(wxCommandEvent & WXUNUSED(event))
{
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to run"), wxEmptyString, wxEmptyString,	_("*.exe"),	wxFD_OPEN, wxDefaultPosition);

	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		wxString path = OpenDialog->GetPath();
		wxString fileName = OpenDialog->GetFilename();

		B5DFile* pB5DFile = new B5DFile(fileName, "", path);
		m_pB5DFiles->addFile(pB5DFile);
	}

	OpenDialog->Destroy();

	m_list_model->refresh();

}

void MainWindows::runB5D(wxCommandEvent& WXUNUSED(event))
{
	wxDataViewItem item = m_pDataViewer->GetSelection();
	int row = m_list_model->GetRow(item);
	if (row == -1)
		return;

	B5DFile* pB5DFile = (*m_pB5DFiles)[row];
	wxString command = "\"" + pB5DFile->getFullPath() + "\"";
	//int result = system(command);
	//startup(command);
	ShellExecute(NULL, L"open", command.ToStdWstring().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void MainWindows::saveB5D(wxCommandEvent& WXUNUSED(event))
{
	m_pB5DFiles->saveB5DFile();
}

void MainWindows::deleteB5D(wxCommandEvent & event)
{
	wxDataViewItem item = m_pDataViewer->GetSelection();
	int row = m_list_model->GetRow(item);
	if (row == -1)
		return;

	m_pB5DFiles->deleteFile(row);
	m_list_model->refresh();
}

