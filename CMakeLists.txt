CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(json_spirit)
SUBDIRS(json_spirit json_demo json_headers_only_demo json_test)
INCLUDE_DIRECTORIES(json_spirit)

OPTION(JSON_SPIRIT_WVALUE_ENABLED "Build with support for unicode types" OFF)
OPTION(JSON_SPIRIT_MVALUE_ENABLED "Build with support for ascii map types" OFF)
OPTION(JSON_SPIRIT_WMVALUE_ENABLED "Build with support for unicode map types" OFF)
OPTION(HAVE_STD11_ENABLED "Build with C++11 enabled" ON)
OPTION(HAVE_STD0X_ENABLED "Build with C++0x enabled" ON)

if(JSON_SPIRIT_CPP11_ENABLED)
  if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x)
  endif(CMAKE_COMPILER_IS_GNUCXX)
endif(JSON_SPIRIT_CPP11_ENABLED)

if(JSON_SPIRIT_WVALUE_ENABLED)
  add_definitions(-DJSON_SPIRIT_WVALUE_ENABLED)
endif(JSON_SPIRIT_WVALUE_ENABLED)

if(JSON_SPIRIT_MVALUE_ENABLED)
  add_definitions(-DJSON_SPIRIT_MVALUE_ENABLED)
  
  # Can only be used when map values are enabled
  ADD_SUBDIRECTORY(json_map_demo)
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
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
  set(CMAKE_CXX_LINK_FLAGS "-std=c++11 -stdlib=libc++")
  message("C++ Flags: ${CMAKE_CXX_FLAGS} link flags: ${CMAKE_CXX_LINK_FLAGS}")
endif()

INSTALL(
  FILES
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_error_position.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_reader.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_reader_template.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_stream_reader.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_utils.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_value.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_writer.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_writer_template.h
  ${CMAKE_SOURCE_DIR}/json_spirit/json_spirit_writer_options.h
  DESTINATION include)

INSTALL(
  FILES
  ${CMAKE_BINARY_DIR}/json_spirit/libjson_spirit.a
  DESTINATION lib)

INCLUDE(CPack)
