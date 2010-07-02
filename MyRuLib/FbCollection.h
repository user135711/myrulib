#ifndef __FBCOLLECTION_H__
#define __FBCOLLECTION_H__

#include <wx/wx.h>
#include <wx/filename.h>
#include "FbDatabase.h"
#include "FbViewData.h"
#include "FbCacheBook.h"
#include "FbThread.h"

class FbModel;

#define DATA_CACHE_SIZE 128
#define HTML_CACHE_SIZE  16

class FbCacheData: public wxObject
{
	public:
		FbCacheData(wxSQLite3ResultSet &result);
		FbCacheData(int code, wxSQLite3ResultSet &result);
		FbCacheData(int code, const wxString &name = wxEmptyString, int count = 0);
		int GetCode() const { return m_code; }
		wxString GetValue(size_t col) const;
	private:
		int m_code;
		wxString m_name;
		int m_count;
		DECLARE_CLASS(FbCacheData)
};

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(FbCacheData, FbCasheDataArray);

class FbCollection: public wxObject
{
	public:
		static wxString Format(int number);
		FbCollection(const wxString &filename);
		virtual ~FbCollection();
	public:
		static FbCollection * GetCollection();
		static wxString GetSeqn(int code, size_t col);
		static wxString GetAuth(int code, size_t col);
		static wxString GetBook(int code, size_t col);
		static wxString GetBookHTML(const FbViewContext &ctx, const FbCacheBook &book, int code);
		static FbCacheBook GetBookData(int code);
		static void AddSeqn(FbCacheData * data);
		static void AddAuth(FbCacheData * data);
		static void AddInfo(FbViewData * info);
		static void ResetSeqn(int code);
		static void ResetAuth(int code);
		static void ResetInfo(int code);
		static void ResetBook(int code);
		static void ResetBook(const wxArrayInt &books);
		static void ResetDir();
		static void LoadIcon(const wxString &extension);
		static void AddIcon(wxString extension, wxBitmap bitmap);
		static wxFileName FindZip(const wxString &dirname, const wxString &filename);
		static wxString GetIcon(const wxString &extension);
	public:
		void EmptyInfo();
	protected:
		FbCacheData * GetData(int code, FbCasheDataArray &items, const wxString &sql);
		FbCacheData * AddData(FbCasheDataArray &items, FbCacheData * data);
		FbCacheBook * AddBook(FbCacheBook * book);
		void AddBook(FbViewData * info);
		void ResetData(FbCasheDataArray &items, int code);
		void DoResetBook(const wxArrayInt &books);
		void DoResetBook(int code);
		void DoResetInfo(int code);
		void DoResetDir();
		FbCacheBook GetCacheBook(int code);
		FbViewData * GetCacheInfo(int code);
	private:
		static wxArrayString sm_icons;
		static wxArrayString sm_noico;
		static wxCriticalSection sm_section;
		FbCommonDatabase m_database;
		FbAggregateFunction m_aggregate;
		FbCasheDataArray m_auths;
		FbCasheDataArray m_seqns;
		FbCasheBookArray m_books;
		FbViewDataArray m_infos;
		FbThread * m_thread;
		DECLARE_CLASS(FbCollection)
};

#endif // __FBCOLLECTION_H__
