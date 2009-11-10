#include "FbDataOpenDlg.h"
#include <wx/artprov.h>
#include "FbLogoBitmap.h"
#include "FbConst.h"

BEGIN_EVENT_TABLE( FbDataOpenDlg, wxDialog )
	EVT_BUTTON( ID_FILE_BTN, FbDataOpenDlg::OnSelectFileClick )
END_EVENT_TABLE()

FbDataOpenDlg::FbDataOpenDlg( wxWindow* parent, wxWindowID id )
	: wxDialog( parent, id, GetTitle(), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBitmap * m_bitmap = new wxStaticBitmap( this, wxID_ANY, FbLogoBitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_bitmap, 0, wxALL|wxALIGN_CENTER_VERTICAL, 10 );

	wxBoxSizer* bSizerCtrl;
	bSizerCtrl = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerFIle;
	bSizerFIle = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText * m_FileText = new wxStaticText( this, wxID_ANY, _("Имя файла:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FileText->Wrap( -1 );
	bSizerFIle->Add( m_FileText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_FileBox = new wxComboBox( this, ID_FILE_TXT, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0, NULL, 0 );
	bSizerFIle->Add( m_FileBox, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );

	wxBitmapButton * m_FileButton = new wxBitmapButton( this, ID_FILE_BTN, wxArtProvider::GetBitmap(wxART_FILE_OPEN), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerFIle->Add( m_FileButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	bSizerCtrl->Add( bSizerFIle, 1, wxEXPAND, 5 );

	m_FileCheck = new wxCheckBox( this, ID_DOWNLOAD, _("Скачать коллекцию с сайта программы"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FileCheck->SetValue(false);

	bSizerCtrl->Add( m_FileCheck, 0, wxALL|wxEXPAND, 5 );

	bSizerTop->Add( bSizerCtrl, 1, wxEXPAND, 5 );

	bSizerMain->Add( bSizerTop, 0, wxEXPAND, 5 );

	wxStdDialogButtonSizer * m_sdbSizerBtn = new wxStdDialogButtonSizer();
	wxButton * m_sdbSizerBtnOK = new wxButton( this, wxID_OK );
	m_sdbSizerBtn->AddButton( m_sdbSizerBtnOK );
	wxButton * m_sdbSizerBtnCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizerBtn->AddButton( m_sdbSizerBtnCancel );
	m_sdbSizerBtn->Realize();
	bSizerMain->Add( m_sdbSizerBtn, 1, wxEXPAND|wxALL, 5 );

	m_FileBox->SetFocus();

	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
}

wxString FbDataOpenDlg::GetTitle() const
{
	return strProgramName + wxT(" - ") + _("Открыть (создать) коллекцию");
}

void FbDataOpenDlg::OnSelectFileClick( wxCommandEvent& event )
{
	wxFileDialog dlg (
		this,
		_("Выберите имя файла коллекции…"),
		wxEmptyString,
		m_FileBox->GetValue(),
		_("Файл базы данных (*.db)|*.db|Все файлы (*.*)|*.*"),
		wxFD_OPEN,
		wxDefaultPosition
	);

	if (dlg.ShowModal() == wxID_OK) {
		m_FileBox->SetValue(dlg.GetPath());
	}
}