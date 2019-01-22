#ifndef JSON_SPIRIT_GLOBAL_H
#define JSON_SPIRIT_GLOBAL_H

#if (defined _WIN32) || (defined _WIN64)
    #define DECL_EXPORT __declspec(dllexport)
    #define DECL_IMPORT __declspec(dllimport)
#else
    #define DECL_EXPORT
    #define DECL_IMPORT
#endif

#if defined(json_spirit_EXPORTS)
#  define json_spirit_EXPORT DECL_EXPORT
#else
#  define json_spirit_EXPORT DECL_IMPORT
#endif

#endif