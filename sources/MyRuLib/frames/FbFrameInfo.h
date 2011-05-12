#ifndef __FBFRAMEINFO_H__
#define __FBFRAMEINFO_H__

#include <wx/wx.h>
#include <wx/aui/tabmdi.h>
#include "FbMainMenu.h"
#include "controls/FbHtmlWindow.h"

class FbFrameInfo
	: public FbHtmlWindow
{
	public:
		static void Execute(wxEvtHandler * owner);
		static wxMenuBar * CreateMenuBar();
		FbFrameInfo(wxAuiNotebook * parent);
		virtual wxString GetTitle() const { return _("Information"); };
		void Load(const wxString & html);
		virtual void UpdateFonts(bool refresh = true);
	private:
		void OnSave(wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
		DECLARE_CLASS(FbFrameInfo)
	private:
		class MainMenu: public FbMenuBar
		{
			public:
				MainMenu();
			protected:
				class MenuFile: public FbMenu {
					public: MenuFile();
				};
		};
};

#endif // __FBFRAMEINFO_H__
