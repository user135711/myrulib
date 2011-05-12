#include "FbWindow.h"
#include "FbParams.h"
#include "FbMainMenu.h"
#include "controls/FbChoiceCtrl.h"
#include <wx/combo.h>
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>

//-----------------------------------------------------------------------------
//  FbDialog
//-----------------------------------------------------------------------------

FbDialog::FbDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
	:wxDialog( parent, id, title, pos, size, style, name )
{
	SetFont( FbParams::GetFont(FB_FONT_DLG) );
}

bool FbDialog::Create( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
	bool res = wxDialog::Create( parent, id, title, pos, size, style, name );
	SetFont( FbParams::GetFont(FB_FONT_DLG) );
	return res;
}

void FbDialog::Assign(long winid, int param, bool write)
{
	wxWindow * window = FindWindowById(winid);
	if (window == NULL) {
		return;
	} else if (wxTextCtrl * control = wxDynamicCast(window, wxTextCtrl)) {
		if (write)
			FbParams::Set(param, control->GetValue());
		else
			control->SetValue(FbParams::GetStr(param));
	} else if (wxCheckBox * control = wxDynamicCast(window, wxCheckBox)) {
		if (write)
			FbParams::Set(param, control->GetValue());
		else
			control->SetValue(FbParams::GetInt(param) != 0);
	} else if (wxRadioBox * control = wxDynamicCast(window, wxRadioBox)) {
		if (write)
			FbParams::Set(param, control->GetSelection());
		else
			control->SetSelection(FbParams::GetInt(param));
	} else if (wxComboBox * control = wxDynamicCast(window, wxComboBox)) {
		if (write)
			FbParams::Set(param, control->GetValue());
		else
			control->SetValue(FbParams::GetStr(param));
	} else if (wxComboCtrl * control = wxDynamicCast(window, wxComboCtrl)) {
		if (write)
			FbParams::Set(param, control->GetValue());
		else
			control->SetValue(FbParams::GetStr(param));
	} else if (wxSpinCtrl * control = wxDynamicCast(window, wxSpinCtrl)) {
		if (write)
			FbParams::Set(param, control->GetValue());
		else
			control->SetValue(FbParams::GetInt(param));
	} else if (wxFontPickerCtrl * control = wxDynamicCast(window, wxFontPickerCtrl)) {
		if (write)
			FbParams::Set(param, control->GetSelectedFont().GetNativeFontInfoDesc());
		else
			control->SetSelectedFont(FbParams::GetFont(param) );
	} else if (wxColourPickerCtrl * control = wxDynamicCast(window, wxColourPickerCtrl)) {
		if (write)
			FbParams::Set(param, control->GetColour().GetAsString(wxC2S_HTML_SYNTAX));
		else
			control->SetColour(FbParams::GetColour(param));
	} else if (FbChoiceInt * control = wxDynamicCast(window, FbChoiceInt)) {
		if (write) {
			int format = control->GetCurrentData();
			FbParams::Set(param, format);
		} else {
			int format = FbParams::GetInt(param);
			size_t count = control->GetCount();
			for (size_t i = 0; i <= count; i++)
				if (control->GetClientData(i) == format) control->SetSelection(i);
		}
	}
}

