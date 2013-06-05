CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(json_spirit)
SUBDIRS(json_spirit json_demo json_headers_only_demo json_test)
INCLUDE_DIRECTORIES(json_spirit)

OPTION(JSON_SPIRIT_WVALUE_ENABLED "Build with support for unicode types" OFF)
OPTION(JSON_SPIRIT_MVALUE_ENABLED "Build with support for ascii map types" OFF)
OPTION(JSON_SPIRIT_WMVALUE_ENABLED "Build with support for unicode map types" OFF)

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
