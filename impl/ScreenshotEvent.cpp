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

#include "ScreenshotEvent.h"

namespace sl {
namespace desktop {
namespace demo {
namespace wx {

wxDEFINE_EVENT(SL_DESKTOP_DEMO_WX_SCREENSHOT, ScreenshotEvent);

ScreenshotEvent::ScreenshotEvent(wxEventType eventType, int id, const string& fileName) : wxCommandEvent(id, eventType), fileName(fileName) {
}

string ScreenshotEvent::GetFileName() const {
	return this->fileName;
}

wxEvent* ScreenshotEvent::Clone() const {
	return new ScreenshotEvent(*this);
}

} /* namespace wx */
} /* namespace demo */
} /* namespace desktop */
} /* namespace sl */
