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

wxBEGIN_EVENT_TABLE(BlankWindow, wxFrame)
	EVT_SL_DESKTOP_DEMO_SCREENSHOT(ScreenshotEvent::Command::ID_CAPTURE, BlankWindow::takeScreenshot)
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

	// Bind(SL_DESKTOP_DEMO_WX_SCREENSHOT, &BlankWindow::takeScreenshot, this, ScreenshotEvent::Command::ID_CAPTURE);
}

BlankWindow::~BlankWindow() {
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

void BlankWindow::takeScreenshot(ScreenshotEvent& event) {
	wxSize screenSize = wxGetDisplaySize();
	wxBitmap bitmap(screenSize.x, screenSize.y);
	wxScreenDC deviceContext;
	wxMemoryDC memDc;

	memDc.SelectObject(bitmap);
	memDc.Blit(0, 0, screenSize.x, screenSize.y, &deviceContext, 0, 0);
	memDc.SelectObject(wxNullBitmap);

	bitmap.SaveFile(event.GetFileName(), wxBITMAP_TYPE_PNG);
}

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
