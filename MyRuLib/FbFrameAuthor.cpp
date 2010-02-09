#include "FbFrameAuthor.h"
#include <wx/artprov.h>
#include <wx/splitter.h>
#include "FbConst.h"
#include "InfoCash.h"
#include "FbClientData.h"
#include "ExternalDlg.h"
#include "FbMainMenu.h"
#include "FbWindow.h"
#include "FbAuthorThread.h"
#include "FbAuthorDlg.h"
#include "FbReplaceDlg.h"
#include "FbUpdateThread.h"
#include "FbMasterList.h"

BEGIN_EVENT_TABLE(FbFrameAuthor, FbFrameBase)
	EVT_TREE_SEL_CHANGED(ID_MASTER_LIST, FbFrameAuthor::OnAuthorSelected)
    EVT_LIST_COL_CLICK(ID_MASTER_LIST, FbFrameAuthor::OnColClick)
	EVT_MENU(wxID_SAVE, FbFrameAuthor::OnExternal)
	EVT_KEY_UP(FbFrameAuthor::OnCharEvent)
	EVT_COMMAND(ID_BOOKS_COUNT, fbEVT_BOOK_ACTION, FbFrameAuthor::OnBooksCount)
	EVT_TREE_ITEM_MENU(ID_MASTER_LIST, FbFrameAuthor::OnContextMenu)
	EVT_MENU(ID_LETTER_ALL, FbFrameAuthor::OnAllClicked)
	EVT_MENU(ID_MASTER_APPEND, FbFrameAuthor::OnMasterAppend)
	EVT_MENU(ID_MASTER_MODIFY, FbFrameAuthor::OnMasterModify)
	EVT_MENU(ID_MASTER_REPLACE, FbFrameAuthor::OnMasterReplace)
	EVT_MENU(ID_MASTER_DELETE, FbFrameAuthor::OnMasterDelete)
	EVT_MENU(ID_MASTER_PAGE, FbFrameAuthor::OnMasterPage)
	EVT_MENU(ID_ALPHABET_RU, FbFrameAuthor::OnViewAlphavet)
	EVT_MENU(ID_ALPHABET_EN, FbFrameAuthor::OnViewAlphavet)
	EVT_UPDATE_UI(ID_ALPHABET_RU, FbFrameAuthor::OnViewAlphavetUpdateUI)
	EVT_UPDATE_UI(ID_ALPHABET_EN, FbFrameAuthor::OnViewAlphavetUpdateUI)
	EVT_UPDATE_UI(ID_MASTER_PAGE, FbFrameAuthor::OnMasterPageUpdateUI)
END_EVENT_TABLE()

FbFrameAuthor::FbFrameAuthor(wxAuiMDIParentFrame * parent)
	:FbFrameBase(parent, ID_FRAME_AUTHOR, _("Авторы"))
{
	CreateControls();
}

void FbFrameAuthor::CreateControls()
{
	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	sizer->Add(m_RuAlphabar = CreateAlphaBar(this, ID_ALPHABET_RU, alphabetRu, ID_LETTER_RU, wxTB_NODIVIDER), 0, wxEXPAND, 5);
	sizer->Add(m_EnAlphabar = CreateAlphaBar(this, ID_ALPHABET_EN, alphabetEn, ID_LETTER_EN, wxTB_NODIVIDER), 0, wxEXPAND, 5);

	wxFont font = FbParams::GetFont(FB_FONT_TOOL);
	m_RuAlphabar->SetFont(font);
	m_EnAlphabar->SetFont(font);

	wxSplitterWindow * splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxSP_NOBORDER);
	splitter->SetMinimumPaneSize(50);
	splitter->SetSashGravity(0.33);
	sizer->Add(splitter, 1, wxEXPAND);

	m_MasterList = new FbMasterList(splitter, ID_MASTER_LIST);
	m_MasterList->AddColumn(_("Автор"), 40, wxALIGN_LEFT);
	m_MasterList->AddColumn(_("Кол."), 10, wxALIGN_RIGHT);
	m_MasterList->SetFocus();
	m_MasterList->SetSortedColumn(1);

	long substyle = wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT | wxTR_COLUMN_LINES | wxTR_MULTIPLE | wxSUNKEN_BORDER;
	CreateBooksPanel(splitter, substyle);
	splitter->SplitVertically(m_MasterList, m_BooksPanel, 160);

	FbFrameBase::CreateControls();

	m_RuAlphabar->Show( FbParams::GetValue(FB_ALPHABET_RU) );
	m_EnAlphabar->Show( FbParams::GetValue(FB_ALPHABET_EN) );
}

wxToolBar * FbFrameAuthor::CreateAlphaBar(wxWindow * parent, wxWindowID id, const wxString & alphabet, const int &toolid, long style)
{
	wxToolBar * toolBar = new wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORZ_TEXT|wxTB_NOICONS|style);
	if (toolid == ID_LETTER_EN) toolBar->AddTool(ID_LETTER_ALL, wxT("*"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, _("Все авторы коллекции"));
	for (size_t i = 0; i<alphabet.Len(); i++) {
		wxString letter = alphabet.Mid(i, 1);
		int btnid = toolid + i;
		toolBar->AddTool(btnid, letter, wxNullBitmap, wxNullBitmap, wxITEM_CHECK);
		this->Connect(btnid, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( FbFrameAuthor::OnLetterClicked ) );
	}
	toolBar->Realize();
	return toolBar;
}

void FbFrameAuthor::ToggleAlphabar(const int &idLetter)
{
	for (size_t i = 0; i<alphabetRu.Len(); i++) {
		int id = ID_LETTER_RU + i;
		m_RuAlphabar->ToggleTool(id, id == idLetter);
	}
	for (size_t i = 0; i<alphabetEn.Len(); i++) {
		int id = ID_LETTER_EN + i;
		m_EnAlphabar->ToggleTool(id, id == idLetter);
	}
	m_EnAlphabar->ToggleTool(ID_LETTER_ALL, ID_LETTER_ALL == idLetter);
}

void FbFrameAuthor::OnLetterClicked( wxCommandEvent& event )
{
	int id = event.GetId();

	wxString alphabet;
	size_t position;

	if (id < ID_LETTER_EN) {
		alphabet = alphabetRu;
		position = id - ID_LETTER_RU;
		FbParams().SetValue(FB_LAST_LETTER, position);
	} else {
		alphabet = alphabetEn;
		position = id - ID_LETTER_EN;
	};

	ToggleAlphabar(id);

	(new FbAuthorThreadChar(m_MasterList, alphabet[position], m_MasterList->GetSortedColumn()))->Execute();
	m_AuthorMode = FB_AUTHOR_MODE_CHAR;
	m_AuthorText = alphabet[position];
}

void FbFrameAuthor::OnAllClicked(wxCommandEvent& event)
{
	wxString text = wxT("*");
	FbFrameAuthor::ToggleAlphabar(ID_LETTER_ALL);
	(new FbAuthorThreadText(m_MasterList, text, m_MasterList->GetSortedColumn()))->Execute();
	m_AuthorMode = FB_AUTHOR_MODE_TEXT;
	m_AuthorText = text;
	FbParams().SetValue(FB_LAST_LETTER, -1);
}

void FbFrameAuthor::SelectFirstAuthor(const int book)
{
	m_BooksPanel->EmptyBooks(book);

	wxTreeItemIdValue cookie;
	wxTreeItemId item = m_MasterList->GetFirstChild(m_MasterList->GetRootItem(), cookie);
	if (item.IsOk()) m_MasterList->SelectItem(item);
}

void FbFrameAuthor::OnAuthorSelected(wxTreeEvent & event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (data) (new AuthorThread(this, m_BooksPanel->GetListMode(), data->GetId()))->Execute();
}

void FbFrameAuthor::ActivateAuthors()
{
	m_MasterList->SetFocus();
}

void FbFrameAuthor::FindAuthor(const wxString &text)
{
	if (text.IsEmpty()) return;
	ToggleAlphabar(0);
	(new FbAuthorThreadText(m_MasterList, text, m_MasterList->GetSortedColumn()))->Execute();
	m_AuthorMode = FB_AUTHOR_MODE_TEXT;
	m_AuthorText = text;
}

void FbFrameAuthor::OpenAuthor(const int author, const int book)
{
	ToggleAlphabar(0);
	(new FbAuthorThreadCode(m_MasterList, author, m_MasterList->GetSortedColumn()))->Execute();
	m_AuthorMode = FB_AUTHOR_MODE_CODE;
	m_AuthorCode = author;
}

void FbFrameAuthor::SelectRandomLetter()
{
	int position = FbParams().GetValue(FB_LAST_LETTER);
	wxCommandEvent event( wxEVT_COMMAND_TOOL_CLICKED, ID_LETTER_RU + position );
	wxPostEvent(this, event);
}

void FbFrameAuthor::OnExternal(wxCommandEvent& event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (data) ExternalDlg::Execute(this, m_BooksPanel->m_BookList, data->GetId());
}

FbThreadSkiper FbFrameAuthor::AuthorThread::sm_skiper;

wxString FbFrameAuthor::AuthorThread::GetSQL(const wxString & condition)
{
	wxString sql;
	switch (m_mode) {
		case FB2_MODE_TREE:
			sql = wxT("\
				SELECT DISTINCT (CASE WHEN bookseq.id_seq IS NULL THEN 1 ELSE 0 END) AS key, \
					books.id, books.title, books.file_size, books.file_type, books.lang, GENRE(books.genres) AS genres, books.id_author, \
					states.rating, sequences.value AS sequence, bookseq.number as number\
				FROM books \
					LEFT JOIN bookseq ON bookseq.id_book=books.id \
					LEFT JOIN sequences ON bookseq.id_seq=sequences.id \
					LEFT JOIN states ON books.md5sum=states.md5sum \
				WHERE (%s) \
				ORDER BY key, sequences.value, bookseq.number, books.title \
			");
			break;
		case FB2_MODE_LIST:
			sql = wxT("\
				SELECT DISTINCT\
					books.id as id, books.title as title, books.file_size as file_size, books.file_type as file_type, books.lang as lang, GENRE(books.genres) AS genres, \
					states.rating as rating, books.created as created, AGGREGATE(authors.full_name) as full_name \
				FROM books \
					LEFT JOIN books as sub ON sub.id=books.id \
					LEFT JOIN authors ON sub.id_author = authors.id \
					LEFT JOIN states ON books.md5sum=states.md5sum \
				WHERE (%s) \
				GROUP BY books.id, books.title, books.file_size, books.file_type, states.rating, books.created \
				ORDER BY \
			") + GetOrder();
			break;
	}

	wxString str = wxString::Format(wxT("(%s)%s"), condition.c_str(), m_filter.c_str());
	return wxString::Format(sql, str.c_str());
}

void * FbFrameAuthor::AuthorThread::Entry()
{
	FbCommandEvent(fbEVT_BOOK_ACTION, ID_EMPTY_BOOKS).Post(m_frame);

	wxCriticalSectionLocker locker(sm_queue);

	if (sm_skiper.Skipped(m_number)) return NULL;

	try {
		FbCommonDatabase database;
		InitDatabase(database);

		{
			wxString sql = wxT("SELECT full_name, description FROM authors WHERE id=?");
			wxSQLite3Statement stmt = database.PrepareStatement(sql);
			stmt.Bind(1, m_author);
			wxSQLite3ResultSet result = stmt.ExecuteQuery();
			if (result.NextRow()) {
				if (m_mode == FB2_MODE_TREE) FbCommandEvent(fbEVT_BOOK_ACTION, ID_APPEND_MASTER, m_author, result.GetString(0)).Post(m_frame);
				FbCommandEvent(fbEVT_BOOK_ACTION, ID_AUTHOR_INFO, m_author, result.GetString(1)).Post(m_frame);
			}
		}

		wxString sql = GetSQL(wxT("books.id_author=?"));
		wxSQLite3Statement stmt = database.PrepareStatement(sql);
		stmt.Bind(1, m_author);
		wxSQLite3ResultSet result = stmt.ExecuteQuery();

		if (sm_skiper.Skipped(m_number)) return NULL;
		FillBooks(result);
	}
	catch (wxSQLite3Exception & e) {
		wxLogError(e.GetMessage());
	}

	return NULL;
}

void FbFrameAuthor::AuthorThread::CreateTree(wxSQLite3ResultSet &result)
{
	wxString thisSequence = wxT("@@@");
	while (result.NextRow()) {
		wxString nextSequence = result.GetString(wxT("sequence"));

		if (thisSequence != nextSequence) {
			thisSequence = nextSequence;
			FbCommandEvent(fbEVT_BOOK_ACTION, ID_APPEND_SEQUENCE, thisSequence).Post(m_frame);
		}

		BookTreeItemData data(result);
		FbBookEvent(ID_APPEND_BOOK, &data).Post(m_frame);
	}
	FbCommandEvent(fbEVT_BOOK_ACTION, ID_BOOKS_COUNT).Post(m_frame);
}

void FbFrameAuthor::UpdateBooklist()
{
	m_BooksPanel->EmptyBooks();
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (data) (new AuthorThread(this, m_BooksPanel->GetListMode(), data->GetId()))->Execute();
}

void FbFrameAuthor::OnCharEvent(wxKeyEvent& event)
{
}

void FbFrameAuthor::OnColClick(wxListEvent& event)
{
	int order = m_MasterList->GetSortedColumn();
	FbThread * thread = NULL;
	switch (m_AuthorMode) {
		case FB_AUTHOR_MODE_CHAR: thread = new FbAuthorThreadChar(m_MasterList, m_AuthorText, order); break;
		case FB_AUTHOR_MODE_TEXT: thread = new FbAuthorThreadText(m_MasterList, m_AuthorText, order); break;
		case FB_AUTHOR_MODE_CODE: thread = new FbAuthorThreadCode(m_MasterList, m_AuthorCode, order); break;
	}
	if (thread) thread->Execute();
}

void FbFrameAuthor::OnBooksCount(wxCommandEvent& event)
{
	wxTreeItemId selected = m_MasterList->GetSelection();
	if (selected.IsOk()) m_MasterList->SetItemText(selected, 1, wxString::Format(wxT("%d"), GetBookCount()));
	event.Skip();
}

void FbFrameAuthor::ShowFullScreen(bool show)
{
	if (m_RuAlphabar) m_RuAlphabar->Show(!show && FbParams::GetValue(FB_ALPHABET_RU));
	if (m_EnAlphabar) m_EnAlphabar->Show(!show && FbParams::GetValue(FB_ALPHABET_EN));
	Layout();
}

void FbFrameAuthor::OnContextMenu(wxTreeEvent& event)
{
	wxPoint point = event.GetPoint();
	// If from keyboard
	if (point.x == -1 && point.y == -1) {
		wxSize size = m_MasterList->GetSize();
		point.x = size.x / 3;
		point.y = size.y / 3;
	}
	ShowContextMenu(point, event.GetItem());
}

void FbFrameAuthor::ShowContextMenu(const wxPoint& pos, wxTreeItemId item)
{
	int id = 0;
	if (item.IsOk()) {
		FbMasterData * data = m_MasterList->GetItemData(item);
		if (data) id = data->GetId();
	}
	MasterMenu menu(id);
	PopupMenu(&menu, pos.x, pos.y);
}

void FbFrameAuthor::OnMasterAppend(wxCommandEvent& event)
{
	wxString newname;
	int id = FbAuthorDlg::Append(newname);

	if (id) {
		FbMasterData * data = new FbMasterAuthor(id);
		wxTreeItemId item = m_MasterList->InsertItem(m_MasterList->GetRootItem(), m_MasterList->GetSelection(), newname, -1, -1, data);
		m_MasterList->SelectItem(item);
	}
}

void FbFrameAuthor::OnMasterModify(wxCommandEvent& event)
{
    wxTreeItemId selected = m_MasterList->GetSelection();
	FbMasterData * data = selected.IsOk() ? m_MasterList->GetItemData(selected) : NULL;
	if (data && data->GetId()) {
		wxString newname;
		int old_id = data->GetId();
		int new_id = FbAuthorDlg::Modify(data->GetId(), newname);
		if (new_id) ReplaceData(old_id, new_id, selected, newname);
	}
}

void FbFrameAuthor::OnMasterReplace(wxCommandEvent& event)
{
    wxTreeItemId selected = m_MasterList->GetSelection();
	FbMasterData * data = selected.IsOk() ? m_MasterList->GetItemData(selected) : NULL;
	if (data && data->GetId()) {
		wxString newname;
		int old_id = data->GetId();
		int new_id = FbReplaceDlg::Execute(old_id, newname);
		if (new_id) ReplaceData(old_id, new_id, selected, newname);
	}
}

void FbFrameAuthor::ReplaceData(int old_id, int new_id, wxTreeItemId selected, const wxString &newname)
{
	if (selected.IsOk()) m_MasterList->SetItemText(selected, newname);
	if (old_id != new_id) {
		FbMasterAuthor deleted(new_id);
		m_MasterList->DeleteItem(deleted);
		delete m_MasterList->GetItemData(selected);
		FbMasterData * data = new FbMasterAuthor(new_id);
		m_MasterList->SetItemData(selected, data);
		m_MasterList->SelectItem(selected);
	}
}

void FbFrameAuthor::OnMasterDelete(wxCommandEvent& event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (!data) return;
	int id = data->GetId();
	if (!id) return;

	wxString sql = wxT("SELECT count(id) FROM books WHERE id_author=?");
	FbCommonDatabase database;
	wxSQLite3Statement stmt = database.PrepareStatement(sql);
	stmt.Bind(1, id);
	wxSQLite3ResultSet result = stmt.ExecuteQuery();
	int count = result.NextRow() ? result.GetInt(0) : 0;

	wxTreeItemId selected = m_MasterList->GetSelection();
	wxString msg = _("Удалить автора: ") + m_MasterList->GetItemText(selected);
	if (count) msg += wxString::Format(_("\nи все его книги в количестве %d шт.?"), count);
	bool ok = wxMessageBox(msg, _("Удаление"), wxOK | wxCANCEL | wxICON_QUESTION) == wxOK;
	if (ok) {
		wxString sql1 = wxString::Format(wxT("DELETE FROM books WHERE id_author=%d"), id);
		wxString sql2 = wxString::Format(wxT("DELETE FROM authors WHERE id=%d"), id);
		(new FbUpdateThread(sql1, sql2))->Execute();
		m_MasterList->Delete(selected);
	}
}

void FbFrameAuthor::OnMasterPage(wxCommandEvent& event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (data && data->GetId()>0) {
		wxString host = FbParams::GetText(DB_DOWNLOAD_HOST);
		wxString url = wxString::Format(wxT("http://%s/a/%d"), host.c_str(), data->GetId());
		wxLaunchDefaultBrowser(url);
	}
}

FbFrameAuthor::MasterMenu::MasterMenu(int id)
{
	Append(ID_MASTER_APPEND,  _("Добавить"));
	if (id == 0) return;
	Append(ID_MASTER_MODIFY,  _("Изменить"));
	Append(ID_MASTER_REPLACE, _("Заменить"));
	Append(ID_MASTER_DELETE,  _("Удалить"));
	if (id > 0) {
		AppendSeparator();
		Append(ID_MASTER_PAGE, _("Страница автора"));
	}
}

FbFrameAuthor::MenuBar::MenuBar()
{
	Append(new MenuFile,   _("Файл"));
	Append(new MenuLib,    _("Библиотека"));
	Append(new MenuFrame,  _("Картотека"));
	Append(new MenuMaster, _("Авторы"));
	Append(new MenuBook,   _("Книги"));
	Append(new MenuView,   _("Вид"));
	Append(new MenuSetup,  _("Сервис"));
	Append(new MenuWindow, _("Окно"));
	Append(new MenuHelp,   _("?"));
}

FbFrameAuthor::MenuMaster::MenuMaster()
{
	Append(ID_MASTER_APPEND,  _("Добавить"));
	Append(ID_MASTER_MODIFY,  _("Изменить"));
	Append(ID_MASTER_REPLACE, _("Заменить"));
	Append(ID_MASTER_DELETE,  _("Удалить"));
	AppendSeparator();
	Append(ID_MASTER_PAGE, _("Страница автора"));
}

wxMenuBar * FbFrameAuthor::CreateMenuBar()
{
	return new MenuBar;
}

void FbFrameAuthor::OnMasterPageUpdateUI(wxUpdateUIEvent & event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	event.Enable( data && data->GetId()>0 );
}

FbFrameAuthor::MenuBar::MenuView::MenuView()
{
	InsertCheckItem(0, ID_ALPHABET_RU, _("Русский алфавит"));
	InsertCheckItem(1, ID_ALPHABET_EN, _("Английский алфавит"));
	InsertSeparator(2);
}

void FbFrameAuthor::OnViewAlphavet(wxCommandEvent& event)
{
	wxToolBar * control = (wxToolBar*) FindWindowById(event.GetId());
	if (!control) return;

	bool show = ! control->IsShown();
	control->Show(show);
	Layout();

	int key = 0;
	switch ( event.GetId() ) {
		case ID_ALPHABET_RU: key = FB_ALPHABET_RU; break;
		case ID_ALPHABET_EN: key = FB_ALPHABET_EN; break;
	}
	if (key) FbParams().SetValue(key, show);
}

void FbFrameAuthor::OnViewAlphavetUpdateUI(wxUpdateUIEvent & event)
{
	wxToolBar * control = (wxToolBar*) FindWindowById(event.GetId());
	event.Check(control->IsShown());
}

