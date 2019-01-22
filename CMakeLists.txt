CMAKE_MINIMUM_REQUIRED(VERSION 2.8.6)

PROJECT(json_spirit)
SUBDIRS(json_spirit)
INCLUDE_DIRECTORIES(json_spirit)

OPTION(BUILD_STATIC_LIBRARIES "Build static libraries" OFF)

OPTION(JSON_SPIRIT_WVALUE_ENABLED "Build with support for unicode types" OFF)
OPTION(JSON_SPIRIT_MVALUE_ENABLED "Build with support for ascii map types" OFF)
OPTION(JSON_SPIRIT_WMVALUE_ENABLED "Build with support for unicode map types" OFF)
OPTION(JSON_SPIRIT_DEMOS "Enable building demos" ON)
OPTION(JSON_SPIRIT_TESTS "Enable building tests" ON)

include(GNUInstallDirs)

if(JSON_SPIRIT_DEMOS)
  ADD_SUBDIRECTORY(json_demo)
  ADD_SUBDIRECTORY(json_headers_only_demo)
endif(JSON_SPIRIT_DEMOS)

if(JSON_SPIRIT_TESTS)
  ADD_SUBDIRECTORY(json_test)
endif(JSON_SPIRIT_TESTS)

if(JSON_SPIRIT_WVALUE_ENABLED)
  add_definitions(-DJSON_SPIRIT_WVALUE_ENABLED)
endif(JSON_SPIRIT_WVALUE_ENABLED)

if(JSON_SPIRIT_MVALUE_ENABLED)
  add_definitions(-DJSON_SPIRIT_MVALUE_ENABLED)
  
  # Can only be used when map values are enabled
  if(JSON_SPIRIT_DEMOS)
    ADD_SUBDIRECTORY(json_map_demo)
  endif(JSON_SPIRIT_DEMOS)
endif(JSON_SPIRIT_MVALUE_ENABLED)

if(JSON_SPIRIT_WMVALUE_ENABLED)
  add_definitions(-DJSON_SPIRIT_WMVALUE_ENABLED)
endif(JSON_SPIRIT_WMVALUE_ENABLED)

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  INCLUDE(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++0x HAVE_STD0X)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)

  if (HAVE_STD11)
    set(CMAKE_CXX_FLAGS -std=c++11)
  elseif (HAVE_STD0X)
    set(CMAKE_CXX_FLAGS -std=c++0x)
  else()
    message(FATAL_ERROR "No advanced standard C++ support (-std=c++0x and -std=c++11 not defined).")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  set(CMAKE_CXX_FLAGS "-std=c++11")
  set(CMAKE_CXX_LINK_FLAGS "-std=c++11")
  message("C++ Flags: ${CMAKE_CXX_FLAGS} link flags: ${CMAKE_CXX_LINK_FLAGS}")
endif()

message(${CMAKE_INSTALL_INCLUDEDIR})


set(CPACK_PACKAGE_VERSION_MAJOR 4)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 8)
set(CPACK_PACKAGE_DESCRIPTION "A C++ JSON Parser/Generator Implemented with Boost Spirit")
include(CPack)

set(EXPORT_HEADERS )
INSTALL(
  FILES
  json_spirit/json_spirit_global.h
  json_spirit/json_spirit.h
  json_spirit/json_spirit_error_position.h
  json_spirit/json_spirit_reader.h
  json_spirit/json_spirit_reader_template.h
  json_spirit/json_spirit_stream_reader.h
  json_spirit/json_spirit_utils.h
  json_spirit/json_spirit_value.h
  json_spirit/json_spirit_writer.h
  json_spirit/json_spirit_writer_template.h
  json_spirit/json_spirit_writer_options.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/json_spirit)

