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

#include <string>
#include <vector>

#include <google/gtest/gtest.h>

#include "azriel/cppmicroservices/core/include/usModuleRegistry.h"
#include <azriel/cppmicroservices/core/include/usModule.h>
#include <azriel/cppmicroservices/core/include/usModuleContext.h>

#ifdef US_BUILD_SHARED_LIBS
#include "azriel/usbundleloader/BundleLoader.h"
#else
#include "azriel/cppmicroservices/core/include/usModuleImport.h"
#endif

#include "fenix/wxwidgets/wx/wxprec.h"
#ifndef WX_PRECOMP
	#include "fenix/wxwidgets/wx/wx.h"
#endif

#include "slDesktopDemoWxTestConfig.h"
#include "../BlankDisplayService.h"

US_USE_NAMESPACE

#ifdef US_PLATFORM_WINDOWS
	static const std::string LIB_PATH = US_RUNTIME_OUTPUT_DIRECTORY;
#else
	static const std::string LIB_PATH = US_LIBRARY_OUTPUT_DIRECTORY;
#endif

#ifndef US_BUILD_SHARED_LIBS
US_IMPORT_MODULE(CppMicroServices)
US_IMPORT_MODULE(slDesktopDemoWx)
#endif

TEST(SlDesktopDemoWxBundle, DisplaysWindow) {
	try {
#ifdef US_BUILD_SHARED_LIBS
		BundleLoader bundleLoader;
		bundleLoader.load(LIB_PATH + LIB_NAME);
#endif

		const Module* const demoWxModule = ModuleRegistry::GetModule("slDesktopDemoWx");
		EXPECT_TRUE(demoWxModule != NULL);

		auto demoWxModuleContext = demoWxModule->GetModuleContext();
		auto const blankWindowServiceReference = demoWxModuleContext->GetServiceReference<sl::desktop::demo::wx::BlankDisplayService>();
		auto const service = demoWxModuleContext->GetService(blankWindowServiceReference);

		char* argv[] = { 0 };
		service->openWindow(0, argv);
		service->saveScreenshot("before.png");

		// TODO send event that closes the main window
		service->closeWindow();
		// service->saveScreenshot("after.png");
	} catch (const std::exception& e) {
		FAIL() << e.what();
	}
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
