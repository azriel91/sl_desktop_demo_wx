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

#include "azriel/cppmicroservices/core/include/usServiceInterface.h"

#ifdef BUILD_SHARED_LIBS
	#ifdef azriel_sl_desktop_demo_wx_EXPORTS
		#define SL_DESKTOP_DEMO_BLANK_DISPLAY_SERVICE_EXPORT US_ABI_EXPORT
	#else
		#define SL_DESKTOP_DEMO_BLANK_DISPLAY_SERVICE_EXPORT US_ABI_IMPORT
	#endif
#else
#define SL_DESKTOP_DEMO_BLANK_DISPLAY_SERVICE_EXPORT US_ABI_EXPORT
#endif

#include <condition_variable>
#include <mutex>
#include <thread>

#include "impl/BlankApplication.h"

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

class SL_DESKTOP_DEMO_BLANK_DISPLAY_SERVICE_EXPORT BlankDisplayService {
private:
	/** Whether there is already a thread starting wx */
	bool wxApplicationIsScheduled;
	/** Whether wx is running */
	bool wxApplicationIsRunning;
	/** The condition variable to wait on when wx is not running */
	std::condition_variable* const wxRunningCond;
	/** Mutex to prevent calls from being made to wx when it isn't running */
	std::mutex* const wxMutex;
	/** UI thread that runs wxWidgets */
	std::thread* uiThread;
	BlankApplication* const application;

public:
	BlankDisplayService();
	virtual ~BlankDisplayService();
	void openWindow(int argc, char** argv);
	void closeWindow();
	void saveScreenshot(const std::string fileName) const;

private:
	static void wxEntry(BlankDisplayService* const service, int argc, char** argv);
};

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
