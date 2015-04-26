/*=============================================================================

	Library: Silver

	Copyright (c) Azriel Hoh

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

=============================================================================*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "fenix/wxwidgets/wx/wxprec.h"
#ifndef WX_PRECOMP
	#include "fenix/wxwidgets/wx/wx.h"
#endif

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

class BlankWindow : public wxFrame {
public:
	enum Command {
		ID_Hello = 1
	};

	BlankWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~BlankWindow();

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */