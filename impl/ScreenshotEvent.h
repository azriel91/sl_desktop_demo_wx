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

#ifndef SL_DESKTOP_DEMO_WX_SCREENSHOTEVENT_H_
#define SL_DESKTOP_DEMO_WX_SCREENSHOTEVENT_H_

#include "fenix/wxwidgets/wx/wxprec.h"
#ifndef WX_PRECOMP
	#include "fenix/wxwidgets/wx/wx.h"
#endif

#include <string>

using namespace std;

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

// define a new event class
class ScreenshotEvent: public wxCommandEvent {
public:
	enum Command { ID_CAPTURE = 1 };

private:
	const string fileName;

public:
	ScreenshotEvent(wxEventType eventType, int id, const string& fileName);

	/**
	 * Get the file name to save the screenshot as.
	 */
	string GetFileName() const;
	virtual wxEvent *Clone() const override;
};

wxDECLARE_EVENT(SL_DESKTOP_DEMO_WX_SCREENSHOT, ScreenshotEvent);

typedef void (wxEvtHandler::*ScreenshotEventFunction)(ScreenshotEvent&);
#define ScreenshotEventHandler(func) wxEVENT_HANDLER_CAST(ScreenshotEventFunction, func)
#define EVT_SL_DESKTOP_DEMO_SCREENSHOT(id, func) \
	wx__DECLARE_EVT1(SL_DESKTOP_DEMO_WX_SCREENSHOT, id, ScreenshotEventHandler(func))
#define EVT_SL_DESKTOP_DEMO_SCREENSHOT_RANGE(id1, id2, func) \
	wx__DECLARE_EVT2(SL_DESKTOP_DEMO_WX_SCREENSHOT, id1, id2, ScreenshotEventHandler(func))

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */

#endif /* SL_DESKTOP_DEMO_WX_SCREENSHOTEVENT_H_ */
