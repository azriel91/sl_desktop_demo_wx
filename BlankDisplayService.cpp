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

BlankDisplayService::BlankDisplayService() :
		wxApplicationIsScheduled(false),
		wxApplicationIsRunning(false),
		wxRunningCond(new std::condition_variable()),
		wxMutex(new std::mutex()),
		uiThread(nullptr),
		application(new BlankApplication()) {
}

BlankDisplayService::~BlankDisplayService() {
	// The application is deleted by wx when it exits
	// delete this->application;
	delete this->wxMutex;
	delete this->wxRunningCond;
}

void BlankDisplayService::openWindow(int argc, char** argv) {
	std::unique_lock<std::mutex> lock(*this->wxMutex);

	// if wx is not already being started, we start it
	if (!this->wxApplicationIsScheduled) {

		// track that there is a thread that is starting the wx application
		this->wxApplicationIsScheduled = true;

		wxApp::SetInstance(this->application);
		this->uiThread = new std::thread(BlankDisplayService::wxEntry, this, argc, argv);
	}

	// wait until the application is running before returning
	while (!this->wxApplicationIsRunning) {
		this->wxRunningCond->wait(lock);
	}
}

void BlankDisplayService::closeWindow() {
	std::unique_lock<std::mutex> lock(*this->wxMutex);
	while (!this->wxApplicationIsRunning) {
		this->wxRunningCond->wait(lock);
	}

	auto const window = this->application->GetTopWindow();
	window->Close();

	this->uiThread->join();
	delete this->uiThread;
	this->uiThread = nullptr;
}

void BlankDisplayService::saveScreenshot(const std::string fileName) const {
	std::unique_lock<std::mutex> lock(*this->wxMutex);
	while (!this->wxApplicationIsRunning) {
		this->wxRunningCond->wait(lock);
	}

	ScreenshotEvent screenshotEvent(SL_DESKTOP_DEMO_WX_SCREENSHOT, ScreenshotEvent::Command::ID_CAPTURE, fileName);
	auto const window = wxTheApp->GetTopWindow();

	// asynchronous call
	wxPostEvent(window, screenshotEvent);

	// We cannot call window->ProcessWindowEvent(...) as this function is not called by the UI thread
	// We cannot call this->application->ProcessPendingEvents() without waiting as the event loop may not have started
	// Perhaps we should override OnEventLoopEnter in the wxApp and let the application class take in an arbitrary function to run
	// @see http://docs.wxwidgets.org/3.0/classwx_app_console.html#aa116701a3bd7700fe6979117e53ae999
}

void BlankDisplayService::wxEntry(BlankDisplayService* const service, int argc, char** argv) {
	{
		std::unique_lock<std::mutex> lock(*service->wxMutex);
	
		wxEntryStart(argc, argv);
		wxTheApp->CallOnInit();

		// after initialization, the application should be running
		service->wxApplicationIsRunning = true;
		service->wxRunningCond->notify_all();

		// unlock the mutex by destroying the lock
	}

	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
}

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
