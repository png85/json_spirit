Introduction
===========
JSON is a text file format similar to XML, but less verbose. It has been called "XML lite". This article describes
JSON Spirit, a C++ library that reads and writes JSON files or streams. It is written using the Boost Spirit parser
generator. If you are already using Boost, you can use JSON Spirit without any additional dependencies.

Key features:
* supports ASCII or Unicode
* ```std::vector``` or ```std::map``` implementations for JSON Objects
* object library or header file only use


Using the Code [![Build Status](https://travis-ci.org/png85/json_spirit.png?branch=master)](https://travis-ci.org/png85/json_spirit)
===========
The JSON Spirit source code is available as a Microsoft Visual Studio 2005 C++ "solution". However, it should
compile and work on any platform compatible with Boost. JSON Spirit has been built and tested with Visual C++
2005, 2008, 2010, and G++ version 4.2.3 on Linux. It has been tested with Visual C++ using Boost versions 1.34.0,
1.37.0, 1.39.0, and 1.42.0. It has also been tested with STLPort.

Platform independent CMake files are included, kindly supplied by Uwe Arzt, with CPack declarations for packaging
and a "make install" target supplied by Amzlkej.

The Visual C++ solution consists of five projects:
* The JSON Spirit library and header files
* An application running the library's unit tests
* Three small programs demonstrating how to use JSON Spirit


JSON Spirit Value
-------------
A JSON value can hold either a JSON ```array```, JSON ```object```, ```string```, ```unsigned integer```, ```integer```, ```double```,
```bool```, or ```null```. The interface of the JSON Spirit ```Value``` class is shown below. The Value class for
Unicode is analogous; for details, see the section on Unicode support.
```cpp
enum Value_type{ obj_type, array_type, str_type,
     bool_type, int_type, real_type, null_type };

class Value
{
    public:

        Value();  // creates null value

        Value( const char*          value );
        Value( const std::string&   value );
        Value( const Object&        value );
        Value( const Array&         value );
        Value( bool                 value );
        Value( int                  value );
        Value( unsigned int         value );
        Value_impl( boost::int64_t  value );
        Value_impl( boost::uint64_t value );
        Value( double               value );

        bool operator==( const Value& lhs ) const;

        Value_type type() const;

        const std::string& get_str()    const;
        const Object&      get_obj()    const;
        const Array&       get_array()  const;
        bool               get_bool()   const;
        int                get_int()    const;
        unsigned int       get_uint()   const;
        boost::int64_t     get_int64()  const;
        boost::uint64_t    get_uint64() const;
        double             get_real()   const;

        Object& get_obj();
        Array&  get_array();

        template< typename > T get_value() const;

        bool is_uint64() const;
        bool is_null() const;

        static const Value null;

    private:

        //...
};
```

You obtain the Value's type by calling ```Value::type()```. You can then call the appropriate getter function.
Generally, you will know a file's format, so you will know what type the JSON values should have. A
```std::runtime_error``` exception is thrown if you try to get a value of the wrong type, for example, if you try
to extract a ```string``` from a value containing an integer.

The template getter function ```get_value()``` is an alternative to ```get_int()```, ```get_real()```, etc. Example
usage would be:
```cpp
int    i = value_1.get_value< int >();
double d = value_2.get_value< double >();
```

A top level ```Value``` read from a file or ```stream``` normally contains an ```Array``` or an ```Object```. An
```Array``` is a ```std::vector``` of values. An ```Object``` is, by default, a ```std::vector``` of JSON pairs.
```cpp
typedef std::vector< Pair > Object;
typedef std::vector< Value > Array;
```

A ```Pair``` is a structure that holds a ```std::string``` and a ```Value```.
```cpp
struct Pair
{
    Pair( const std::string& name, const Value& value );

    bool operator==( const Pair& lhs ) const;

    std::string name_;
    Value value_;
};
```

JSON ```Arrays``` and ```Objects``` can themselves contain other ```Arrays``` or ```Objects```, forming a tree.

Note, JSON Spirit provides an alternative ```std::map``` based ```Object```; see the Map Implementation section
below. In this case, a ```Pair``` type is not needed as an ```mObject``` is a ```std::map``` of names to values.
```cpp
typedef std::map< std::string, mValue > mObject;
```


Reading JSON
-------------

You can read JSON data from a ```stream``` or a ```string```:
```cpp
bool read( const std::string &s, Value& value );
bool read( std::istream &is,     Value& value );
```

For example:
```cpp
ifstream is( "json.txt" );
Value value;
read( is, value );
```

You can also read JSON data by supplying a pair of ```string``` iterators.
```cpp
bool read( std::string::const_iterator &begin,
           std::string::const_iterator  end, Value& value );
```

After a successful read, the iterator "```begin```" will point one past the last character of the text for the
value just read. This allows the decoding of a string containing multiple top level values. A subsequent call to
read will read the next value in the string.

Similarly the ```stream``` reading functions now allow a sequence of top-level values to be read one at a time.
Before version 3.0, a ```stream``` was converted to a ```string``` before being parsed. This was fine for files,
but not if, for example, you wanted to read multiple JSON values from a socket.


Writing JSON
-------------

To output JSON, you first create a ```Value``` object containing your data, then write the created ```Value``` to
a ```stream``` or ```string```. For example, the following code will create a small JSON file containing an object
with three members:
```cpp
Object addr_obj;

addr_obj.push_back( Pair( "house_number", 42 ) );
addr_obj.push_back( Pair( "road",         "East Street" ) );
addr_obj.push_back( Pair( "town",         "Newtown" ) );

ofstream os( "address.txt" );

write( addr_obj, os, pretty_print );

os.close();
```

The object addr_obj is automatically converted into a ```Value``` as it is passed to the write function. The file
address.txt will contain:
```cpp
{
    "house_number" : 42,
    "road" : "East Street",
    "town" : "Newtown"
}
```

There are two versions of each function, one to write to strings, the other to write to files:
```cpp
std::string write( const Value&  value, unsigned int options = 0 );
void write( const Value& value, std::ostream&  os, unsigned int options = 0 );
```

The ```options``` parameter controls how the data is written
```cpp
enum Output_options
{ 
    pretty_print = 0x01, 
    raw_utf8 = 0x02, 
    remove_trailing_zeros = 0x04,
    single_line_arrays = 0x08,
    always_escape_nonascii = 0x10,
    no_quote_strings = 0x20
};
```

The ```pretty_print``` option causes white-space and line breaks to be added to the JSON text.

The ```raw_utf8``` option is an extension to the JSON standard. It disables the escaping of non-printable
characters, allowing UTF-8 sequences held in 8 bit char strings to pass through unaltered.

The ```remove_trailing_zeros``` option removes trailing zeros when outputting double precision floating point
numbers; e.g., without the option, 1.2 will be written as "1.200000000000000"; with the option, it will be written
as "1.2".

The ```single_line_arrays``` option has the same effect as the pretty printing option except that arrays printed
on single lines unless they contain composite elements, i.e. objects or arrays. This produced output like:
```js
{
    "1" : [ 0, 0, 0, 0, 0 ],
    "2" : [
        [ 0, 0, 0, 0, 0 ],
        [ 0, 1, 2, 3, 4 ],
        [ 0, 2, 4, 6, 8 ],
        [ 0, 3, 6, 9, 12 ],
        [ 0, 4, 8, 12, 16 ]
    ]
}
```

The ```always_escape_nonascii``` option escapes all unicode wide characters, i.e. outputed as "\uXXXX" even if they
are printable under the current locale, ascii printable chars are not escaped.

You can apply more than one option by using the OR operator, i.e.:
```cpp
write( addr_obj, os, pretty_print | raw_utf8 );
```

The default is to write the JSON text without any white-space and to escape non-printable characters. There is
also a function called ```write_formatted```. This is equivalent to:

```cpp
write( addr_obj, os, pretty_print );
```


Error Detection
-------------

From version 3.00, JSON Spirit provides functions that report the position of format errors in the text being
parsed. These functions are identical to the normal read functions except that instead of returning ```false```
if an error is found, they throw a ```json_spirit::Error_position``` exception. Note, these functions run about
three times slower than the normal read functions.

The ```Error_position``` structure holds the line and column number where the first error was found.
```cpp
struct Error_position
{
    ...
    unsigned int line_;
    unsigned int column_;
    std::string reason_;
};
```


Unicode Support
-------------

Unicode support is provided by ```std::wstring``` versions of the JSON Spirit ```Value```, ```Array```,
```Object```, and ```Pair``` types. These are called ```wValue```, ```wArray```, ```wObject```, and ```wPair```.
There are also std::wstring versions of each reader and writer function.

To enable Unicode support set the ```JSON_SPIRIT_WVALUE_ENABLED``` and/or ```JSON_SPIRIT_WMVALUE_ENABLED``` cmake options.

Note that there is no support for reading Unicode files and converting them to ```wstrings``` as this is not a task
specific to JSON.

The ```Value``` and ```wValue``` classes are actually instantiations of the template class ```Value_impl```.


```Std::map``` Implementation
-------------

Before version 4.00, the JSON Spirit ```Object``` type was a ```std::vector``` of name/value ```Pairs```. You now
have the option of using ```mObject``` which is a name/value ```std::map```. For the ```std::map``` version, use
```mValue``` instead of ```Value```, ```mObject``` instead of ```Object```, and ```mArray``` instead of
```Array```. For the Unicode map version, use ```wmValue```, ```wmObject```, and ```wmArray```.

To enable map support set the ```JSON_SPIRIT_MVALUE_ENABLED``` and optionally set ```JSON_SPIRIT_WMVALUE_ENABLED```
cmake options.

The following table shows the time in seconds it takes on my PC to extract the data from a single object of
varying sizes. The methods used are as per the demo programs. The vector version is faster until the number of
object members reach around 10, but then gets exponentially slower.

| size    | vector       | map          |
|:------- |:------------ |:------------ |
| 2       | 2.03253e-007 | 3.24672e-007 |
| 5       |	7.63788e-007 | 9.59516e-007 |
| 10      |	2.26948e-006 | 2.00929e-006 |
| 15      |	4.68965e-006 | 3.28509e-006 |
| 20      |	8.19667e-006 | 4.75871e-006 |
| 30      |	1.72695e-005 | 7.64189e-006 |
| 50      |	4.63171e-005 | 1.39316e-005 |
| 75      |	0.000102418  | 2.27205e-005 |
| 100     |	0.000179923  | 3.17732e-005 |
| 200     |	0.000709335  | 7.3061e-005  |
| 500     |	0.00440368   | 0.00022076   |
| 1000    |	0.0175385    | 0.000495554  |
| 10000   |	1.76533      | 0.00658268   |
| 100000  |	178.718      | 0.127325     |
| 1000000 |	17800.718    | 1.99467      |

Note: with a vector, object members will be written out in the same order they were read in. A map will sort
members alphabetically. A vector object also allows members to have duplicate names. This might be useful in some
circumstances but would be non-standard.


Stream_reader Class
-------------

There is a ```Stream_reader``` class to work around a bug that prevents multiple top level values that are not
separated by white space from being read from a stream. The standard stream reading functions would fail in this
case.
```cpp
istringstream is( "[1][1,2][1,2,3]" );  // no white space separating arrays

Stream_reader< istringstream, Value > reader( is );

Value value;

const bool ok = reader.read_next( value ); // read first array
reader.read_next( value );                 // read second array
reader.read_next( value );                 // read third array
```

I originally thought that this was caused by a bug in the ```boost.multi_pass``` iterator. However, I now realise
that it basically results from the intrinsic behaviour of the ```std::istream_iterator``` constructor in
immediately reading a character from its stream.


Compiling and linking
===========

There are two ways to use the library:
* Build and link in the JSON Spirit an object library.
* Just include the relevant header files, i.e., "header only" use.

Linking to the object library has the advantage that the heavily templated code only has to be compiled once.
Compiling the code can take some time. If you just include the header file implementation, the code will be
compiled each time it is included. The use of precompiled headers should help, but I have not investigated this.

The include files needed to read JSON text using the object library are *json_spirit_reader.h* and
*json_spirit_value.h*. To generate JSON text, you need *json_spirit_writer.h* and *json_spirit_value.h*.
Alternately, you can include *json_spirit.h*, which includes all three of the above.

The include files needed when using the header only implementation are *json_spirit_reader_template.h* and
*json_spirit_writer_template.h*.

All JSON Spirit declarations are in the namespace ```json_spirit```


Reducing Build Times
-------------

As already described, you can choose between four different types of JSON value classes: ```Value```, ```mValue```,
```wValue``` and ```wmValue```. You would normally chose a single type and stick with it, however the compiler will
process the templates to generate sets of classes for all four types. This results in longer than necessary build
times and larger intermediate files. You can disable value types you don't want by commenting out the relevant
lines in *json_spirit_value.h* below:
```cpp
#define JSON_SPIRIT_VALUE_ENABLED
#define JSON_SPIRIT_WVALUE_ENABLED
#define JSON_SPIRIT_MVALUE_ENABLED
#define JSON_SPIRIT_WMVALUE_ENABLED
```


Using JSON Spirit with Multiple Threads
-------------

If you intend to use JSON Spirit in more than one thread, you will need to uncomment the following line near the
top of *json_spirit_reader.cpp*.
```cpp
//#define BOOST_SPIRIT_THREADSAFE
```

In this case, Boost Spirit will require you to link against Boost Threads.


Advanced
===========

Container Constructor
-------------

An advanced feature introduced in version 4.05 is a constructor in the ```Value``` classes for containers. A
container is passed in as an iterator range. This allows you to create an ```Array``` from a container such as an
```std::vector```. For example, the following code creates and outputs the array ```[1,2,3]```:
```cpp
std::vector< int > int_vect;

int_vect.push_back( 1 );
int_vect.push_back( 2 );
int_vect.push_back( 3 );

const Value val( int_vect.begin(), int_vect.end() );

cout << write( val );
```

Any compatible container type can be used. The following code creates and outputs the array ```[1.0,2.0,3.0]```:
```cpp
std::list< float > float_list;

double_vect.push_back( 1.0 );
double_vect.push_back( 2.0 );
double_vect.push_back( 3.0 );

const Value val( double_vect.begin(), double_vect.end() );

cout << write( val, remove_trailing_zeros );
```


Variant Constructor
-------------

Another advanced feature introduced in version 4.05 is a constructor in the ```Value``` classes for ```boost::variant``` objects. Any compatible variant type can be used. For example:
```cpp
boost::variant< int, string, std::vector< bool > > var;

var = 1;
Value val( var );
cout << write( val ) << endl;

var = string( "hello" );
val = var;
cout << write( val ) << endl;

std::vector< bool > bool_vect;
bool_vect.push_back( true );
bool_vect.push_back( false );
bool_vect.push_back( true );
var = bool_vect;
val = var;
cout << write( val ) << endl;
```

Output:
```
1
"hello"
[true,false,true]
```
