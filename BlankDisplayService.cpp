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

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

BlankDisplayService::BlankDisplayService() : uiThread(nullptr) {
}

BlankDisplayService::~BlankDisplayService() {
}

void BlankDisplayService::openWindow(int argc, char** argv) {
	this->uiThread = new std::thread(BlankDisplayService::wxEntry, argc, argv);
}

void BlankDisplayService::closeWindow() {
	this->uiThread->join();
	delete this->uiThread;
	this->uiThread = nullptr;
}

void BlankDisplayService::wxEntry(int argc, char** argv) {
	wxApp::SetInstance( new BlankApplication() );
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
