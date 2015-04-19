project(slDesktopDemoWx)

cmake_minimum_required(VERSION 3.0)

include(biicode/cmake/tools)

# Bii variables
set(BII_LIB_SRC BlankWxWindowActivator.cpp
                BlankDisplayService.cpp
                impl/BlankApplication.cpp
                impl/BlankWindow.cpp)
SET(BII_LIB_DEPS ${BII_LIB_DEPS} azriel_cppmicroservices)
set(BII_test_main_SRC test/main.cpp)

usFunctionGenerateModuleInit(BII_LIB_SRC MODULE_NAME slDesktopDemoWx)

# Actually create targets: executables and libraries.
ADD_BII_TARGETS()

ACTIVATE_CPP11(${BII_LIB_TARGET})
set_property(TARGET ${BII_LIB_TARGET} APPEND PROPERTY COMPILE_DEFINITIONS US_MODULE_NAME=slDesktopDemoWx)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(${BII_LIB_TARGET} PRIVATE US_STATIC_MODULE)
endif()

# For unix, we need to tell wx the libraries it may use
if(UNIX)
  target_compile_definitions(${BII_LIB_TARGET} PRIVATE wxUSE_LIBMSPACK wxUSE_EPOLL_DISPATCHER)
else()
  target_compile_definitions(${BII_LIB_TARGET} PRIVATE wxUSE_SELECT_DISPATCHER)
endif()

# Tests
if(NOT ${BII_IS_DEP})
  # Need to tell GTest not to use std::tuple because CppMicroServices uses its own definition, and it causes a redefinition error
  target_compile_definitions(${BII_test_main_TARGET} PRIVATE GTEST_HAS_TR1_TUPLE=0 GTEST_USE_OWN_TR1_TUPLE=1)

  add_subdirectory(test)
endif()
