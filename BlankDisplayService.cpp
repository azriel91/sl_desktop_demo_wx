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

#include "BlankDisplayService.h"

#include "impl/BlankApplication.h"
#include "impl/ScreenshotEvent.h"

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

BlankDisplayService::BlankDisplayService() : uiThread(nullptr), application(new BlankApplication()) {
}

BlankDisplayService::~BlankDisplayService() {
	// The application is deleted by wx when it exits
	// delete this->application;
}

void BlankDisplayService::openWindow(int argc, char** argv) {
	wxApp::SetInstance(this->application);
	this->uiThread = new std::thread(BlankDisplayService::wxEntry, argc, argv);
}

void BlankDisplayService::closeWindow() {
	this->uiThread->join();
	delete this->uiThread;
	this->uiThread = nullptr;
}

void BlankDisplayService::saveScreenshot(const std::string fileName) const {
	ScreenshotEvent* const screenshotEvent = new ScreenshotEvent(SL_DESKTOP_DEMO_WX_SCREENSHOT, ScreenshotEvent::Command::ID_CAPTURE, fileName);
	this->application->QueueEvent(screenshotEvent); // Unfortunately this doesn't appear to work
}

void BlankDisplayService::wxEntry(int argc, char** argv) {
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
}

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
