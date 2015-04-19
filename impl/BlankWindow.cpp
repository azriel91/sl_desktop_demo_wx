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

#include "BlankWindow.h"

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

wxBEGIN_EVENT_TABLE(sl::desktop::demo::wx::BlankWindow, wxFrame)
	EVT_MENU(ID_Hello,   BlankWindow::OnHello)
	EVT_MENU(wxID_EXIT,  BlankWindow::OnExit)
	EVT_MENU(wxID_ABOUT, BlankWindow::OnAbout)
wxEND_EVENT_TABLE()

BlankWindow::BlankWindow(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText( "Welcome to wxWidgets!" );


	wxPanel* panel = new wxPanel(this, -1);
	panel->SetSize(200, 100);

	st1 = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 10));
	st2 = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 30));

	Connect(wxEVT_MOVE, wxMoveEventHandler(BlankWindow::OnMove));

	Centre();

	//Connect(wxEVT_MENU, wxCommandEventHandler(BlankWindow::OnHello));
}

BlankWindow::~BlankWindow() {
}

void BlankWindow::OnMove(wxMoveEvent& event) {
	wxPoint size = event.GetPosition();
	st1->SetLabel(wxString::Format(wxT("x: %d"), size.x ));
	st2->SetLabel(wxString::Format(wxT("y: %d"), size.y ));
}

void BlankWindow::OnHello(wxCommandEvent& WXUNUSED(event)) {
	wxLogMessage("Hello world from wxWidgets!");
}

void BlankWindow::OnExit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void BlankWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION );
}

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
