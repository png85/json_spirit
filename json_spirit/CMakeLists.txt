CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(JSON_SPIRIT_SRCS
  json_spirit_reader.cpp json_spirit_reader.h
  json_spirit_value.cpp json_spirit_value.h
  json_spirit_writer.cpp json_spirit_writer.h
  json_spirit.h
  json_spirit_error_position.h
  json_spirit_reader_template.h
  json_spirit_stream_reader.h
  json_spirit_utils.h
  json_spirit_writer_options.h
  json_spirit_writer_template.h )
 
FIND_PACKAGE(Boost 1.34 REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


OPTION(BUILD_STATIC_LIBS "Build static libraries" OFF)

if(BUILD_STATIC_LIBS)
  ADD_LIBRARY(json_spirit STATIC ${JSON_SPIRIT_SRCS})
  install(TARGETS json_spirit ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
else(BUILD_STATIC_LIBS)
  ADD_LIBRARY(json_spirit SHARED ${JSON_SPIRIT_SRCS})
  install(TARGETS json_spirit LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif(BUILD_STATIC_LIBS)
