#ifndef JSON_SPIRIT_READER
#define JSON_SPIRIT_READER

//          Copyright John W. Wilkinson 2007 - 2013
// Distributed under the MIT License, see accompanying file LICENSE.txt

// json spirit version 4.06.1
// upstream json spirit version 4.06

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "json_spirit_global.h"
#include "json_spirit_value.h"
#include "json_spirit_error_position.h"
#include <iostream>

namespace json_spirit
{
    // functions to reads a JSON values

#ifdef JSON_SPIRIT_VALUE_ENABLED
    json_spirit_EXPORT bool read( const std::string& s, Value& value );
    json_spirit_EXPORT bool read( std::istream& is,     Value& value );
    json_spirit_EXPORT bool read( std::string::const_iterator& begin, std::string::const_iterator end, Value& value );

    json_spirit_EXPORT void read_or_throw( const std::string& s, Value& value );  
    json_spirit_EXPORT void read_or_throw( std::istream& is,     Value& value );
    json_spirit_EXPORT void read_or_throw( std::string::const_iterator& begin, std::string::const_iterator end, Value& value );
#endif

#if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
    json_spirit_EXPORT bool read( const std::wstring& s, wValue& value );
    json_spirit_EXPORT bool read( std::wistream&  is,    wValue& value );
    json_spirit_EXPORT bool read( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value );    

    json_spirit_EXPORT void read_or_throw( const std::wstring& s, wValue& value );
    json_spirit_EXPORT void read_or_throw( std::wistream& is,     wValue& value );
    json_spirit_EXPORT void read_or_throw( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value );
#endif

#ifdef JSON_SPIRIT_MVALUE_ENABLED
    json_spirit_EXPORT bool read( const std::string& s, mValue& value );
    json_spirit_EXPORT bool read( std::istream& is,     mValue& value );
    json_spirit_EXPORT bool read( std::string::const_iterator& begin, std::string::const_iterator end, mValue& value );

    json_spirit_EXPORT void read_or_throw( const std::string& s, mValue& value );  
    json_spirit_EXPORT void read_or_throw( std::istream& is,     mValue& value );
    json_spirit_EXPORT void read_or_throw( std::string::const_iterator& begin, std::string::const_iterator end, mValue& value );
#endif

#if defined( JSON_SPIRIT_WMVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
    json_spirit_EXPORT bool read( const std::wstring& s, wmValue& value );
    json_spirit_EXPORT bool read( std::wistream& is,     wmValue& value );
    json_spirit_EXPORT bool read( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wmValue& value );    

    json_spirit_EXPORT void read_or_throw( const std::wstring& s, wmValue& value );
    json_spirit_EXPORT void read_or_throw( std::wistream& is,     wmValue& value );
    json_spirit_EXPORT void read_or_throw( std::wstring::const_iterator& begin, std::wstring::const_iterator end, wmValue& value );
#endif
}

#endif
