/**   Copyright 2018 Elliot Haisley Brown
 *
 *  Licensed under the (modified) Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://github.com/Apache-HB/CTULib/blob/master/LICENSE
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "Meta/Aliases.h"
#include "Meta/Macros.h"

#include "Core/Types/Lambda.h"

#ifdef __OBJC__
@class NSString;
#endif

#pragma once
//TODO more detailed docs on all functions
namespace Cthulhu
{

//Forward declaration to prevent looping includes and reduce compile times
template<typename T>
class Array;

template<typename TKey, typename TVal>
class Map;

template<typename T>
class Optional;

/**Dynamically sized string class
 * This class is a wrapper for a raw `char*` "character pointer"
 * It features a very similar frontend to java's String or C#'s String classes
 * 
 * @code{.cpp}
 * 
 * String S = "Content";
 * 
 * @endcode
 * 
 * @see operator*
 * @see Format
 */
class String
{
    /**The raw C-String this string wraps around
     * 
     */
    char* Real;
public:

    /**Default constructor
     * sets the content to \0
     */
    String();

    /**String constructor
     * sets the content to a copy of the input
     * The input is duplicated and is not owned by the string class
     * so if it was allocated dynamically with `malloc` or `new char[]`
     * you will have to `free` or `delete[]` it yourself
     * 
     * @code{.cpp}
     * 
     * char* C = "Bob";
     * //Statically allocated, dont need to free
     * 
     * String CS = String(C);
     * //creates a string with "Bob" as its contents
     * 
     * char* D = (char*)malloc(sizeof(char) * 25);
     * 
     * memset(D, '-', 5);
     * D[5] = '\0';
     * 
     * String DS = String(D);
     * //creates a string with the content "-----"
     * //this was allocated dynamically so must be free'd to prevent leaks
     * 
     * free((void*)D);
     * 
     * char* E = new char[25];
     * 
     * memset(E, '#', 6);
     * E[6] = '\0';
     * 
     * String ES = String(E);
     * //creates a string with the content "######"
     * //this was allocated with new[] so must be delete[]'d to prevent leaks
     * 
     * delete[] E;
     * 
     * // CS, DS, and ES all exit scope and delete their associated memory
     * // no leaks happen when a String goes out of scope
     * 
     * @endcode
     * 
     * @param Content   the content to copy
     */
    String(const char* Content);

    /**Reference copy constructor
     * sets the content to a copy of the other classes content
     * Performs a deep copy of the content so the new string can
     * be modified without editing the old string
     * 
     * @code{.cpp}
     * 
     * String S = String("Some random content");
     * 
     * String J = String(S);
     * 
     * S += " More Content";
     * 
     * //S = "Some random content More Content"
     * 
     * //J = "Some random content"
     * 
     * @endcode
     * 
     * @param Other the string to copy
     */
    String(const String& Other);

    /**pointer copy constructor
     * copys the content from a pointer to a string
     * performs a deep copy of the other strings content, 
     * is not nullptr safe
     * 
     * @code{.cpp}
     * 
     * String* S = new String("Some content");
     * 
     * String D = String(S);
     * 
     * //D = "Some content"
     * 
     * String E = String(nullptr);
     * 
     * //BANG!
     * //segmentation fault 11
     * 
     * @endcode
     * 
     * @param Other the pointer to copy from
     */
    String(const String* Other);

#ifdef __OBJC__
    String(const NSString* Other);
#endif

    /**Assignment operator overload
     * copys the content from the other string to this string
     * 
     * @code{.cpp}
     * 
     * String S = String("Name jeff");
     * 
     * String J = S;
     * 
     * //S = "Name jeff"
     * //J = "Name jeff"
     * 
     * @endcode
     * 
     * @param Other the string to copy from
     * 
     * @return      itself
     */
    String& operator=(const String& Other);

    /**destructor
     * 
     */
    ~String();

    /**get the strings length, not including null terminator (\0)
     * 
     * @return the length of this string
     */
    ALWAYSINLINE int Len() const;

    /**check if the string is empty
     * equivilent to String.Len() == 0;
     * 
     * @code{.cpp}
     * 
     * @endcode
     * 
     * @return if the string is empty or not
     */
    ALWAYSINLINE bool IsEmpty() const;

    /**Overloaded bool for string 
     * equivilent to String.IsEmpty(); or String.Len() == 0;
     * 
     * @code{.cpp}
     * 
     * @endcode
     * 
     * @return if the string is empty or not
     */
    ALWAYSINLINE operator bool() const;

    /**Check if an integer is inside the strings range
     * 
     * @param Index the index to search for
     * 
     * @return if the index is inside the string or not
     */
    ALWAYSINLINE bool ValidIndex(int Index) const;

    /**checks if the content of thise string equals another
     * 
     * @param Other the string to compare to
     * 
     * @return if the strings are equal or not
     */
    bool operator==(const String& Other) const;

    /**copares two strings to check content equality
     * 
     * @param Other the string to compare to
     * 
     * @return if the strings are not equal or are equal
     */
    bool operator!=(const String& Other) const;

    /**Adds one string to this string and returns the content in a copy
     * 
     * @param Other the string to concat onto this one
     * 
     * @return a copy of this string with the concat'ed content
     */
    String operator+(const String& Other) const;

    /**Adds a c-string to this string and returns a copy with the concat'ed content
     * 
     * @param Str   the c-string to concat
     * 
     * @return a copy of this string with the concat'ed content
     */
    String operator+(const char* Str) const;

    /**Adds a single character to the string
     * 
     * @param C the character to add
     * 
     * @return a copy of the string with the extra character
     */
    String operator+(const char C) const;
    
    /**Append another string to the current string
     * 
     * @param Other the string to concat to this one
     * 
     * @return itself
     */
    String operator+=(const String& Other);

    /**Append a c-string to this string
     * 
     * @param Str   the string to concat
     * 
     * @return itself
     */
    String operator+=(const char* Str);

    /**Append a single character to the string
     * 
     * @param C the character to append
     * 
     * @return itself
     */
    String operator+=(const char C);

    /**Append an int to the string after converting it to a string
     * 
     * @codeblock{.cpp}
     * 
     * String S = "Some integer: ";
     * 
     * S << 24;
     * 
     * // "Some integer: 24"
     * 
     * @endcode
     * 
     * @param I the int to append
     * 
     * @return itself
     */
    String& operator<<(int64 I);

    /**Append a float to the string after converting it to a string
     * 
     * @code{.cpp}
     * 
     * String F = "Some float: ";
     * 
     * F << 673.342;
     * 
     * // "Some float: 673.342"
     * 
     * @endcode
     * 
     * @param F the float to append
     * 
     * @return itself
     */
    String& operator<<(float F);

    /**Append a bool to the string after converting it to a string
     * 
     * @code{.cpp}
     * 
     * String S = "Some bool: ";
     * 
     * S << true;
     * 
     * // "Some bool: true";
     * 
     * String X = "Another bool: ";
     * 
     * X << false;
     * 
     * // "Another bool: false"
     * 
     * @endcode
     * 
     * @param B the bool to append
     * 
     * @return itself
     */
    String& operator<<(const bool B);

    /**Append a double to the string after converting it to a string
     * 
     * @code{.cpp}
     * 
     * String S = "Some number: ";
     * 
     * S << 5.43;
     * 
     * // "Some number: 5.43"
     * 
     * @endcode
     * 
     * @param D the double to append
     * 
     * @return itself
     */
    String& operator<<(double D);

    /**Append one string to another string using the OS file path seperator
     * 
     * @code{.cpp}
     * 
     * String Path = "Some"/"File"/"Path"/"File.txt";
     * 
     * //On OSX/Unix
     * // "Some/File/Path/File.txt"
     * 
     * //On Windows
     * // "Some\\File\\Path\\File.txt"
     * 
     * @endcode
     * 
     * @param Other the string to append
     * 
     * @return a copy of the string with the seperator and other string
     */
    String operator/(const String& Other) const;

    /**Append a string using the OS file path seperator
     * 
     * @code{.cpp}
     * 
     * String Path = "Some";
     * 
     * Path /= "File";
     * Path /= "Path";
     * Path /= "File.txt";
     * 
     * //On OSX/Unix
     * // "Some/File/Path/File.txt"
     * 
     * //On Windows
     * // "Some\\File\\Path\\File.txt"
     * 
     * @endcode
     * 
     * @param Other the string to append
     * 
     * @return itself
     */
    String& operator/=(const String& Other);

    /**overloaded [] operator
     * returns a char at an index in the string unsafley
     * 
     * @param Index the location to retrive
     * 
     * @return the found char
     */
    ALWAYSINLINE char& operator[](int Index);

    ALWAYSINLINE const char operator[](int Index) const;

    /**Safley return a char at an index in the string
     * 
     * @param Index the index to retrive
     * 
     * @return the found char or \0 if out of range
     */
    char At(int Index) const;

    /**overloaded derefernce operator
     * 
     * @return the raw c-string this string holds
     */
    ALWAYSINLINE const char* operator*() const;

    /**
     * 
     */
    ALWAYSINLINE const char* Raw() const;

    /**Append another string to this string
     * 
     * @param Other the other string to append
     */
    void Append(const String& Other);

    /**Append a c-string to this string
     * 
     * @param Str   the string to append
     */
    void Append(const char* Str);

    /**Append a single char to this string
     * 
     * @param C the char to append
     */
    void Append(const char C);

    /**Pop off a certain amount of chars from this string and return them
     * 
     * @param Len the amount of chars to pop
     * 
     * @return the popped chars
     */
    String Pop(int Len = 1);

    /**Trim the front and back of this string using a string as a pattern
     * 
     * @param Pattern   the characters to trim
     */
    void Trim(const String& Pattern = " ");

    /**Trim the front of the string of a certain pattern
     * 
     * @param Pattern   the characters to trim
     */
    void TrimFront(const String& Pattern = " ");

    /**Trim the back of the string of a certain pattern
     * 
     * @param Pattern   the characters to trim
     */
    void TrimBack(const String& Pattern = " ");

    /**Take a substring from within the string
     * 
     * @param Start the index to start from
     * @param End   the index to end at
     * 
     * @return      the substring
     */
    String SubStr(int Start, int End) const;

    /**TODO: implement map
     * 
     */
    //String Format(const Map<String, String> Args) const;

    /**TODO: document
     * 
     */
    String Format(const Array<String> Args) const;

    /**
     * 
     */
    String Upper() const;

    /**
     * 
     */
    String Lower() const;

    /**
     * 
     */
    Array<String> Chunked(int Size) const;

    /**
     * 
     */
    Array<String> Split(const String& Delimiter) const;

    /**
     * 
     */
    Optional<int> Find(const String& Pattern) const;

    /**
     * 
     */
    bool Has(const String& Pattern) const;

    /**
     * 
     */
    void Replace(const String& Search, const String& Substitute);
    
    /**
     * 
     */
    bool StartsWith(const String& Other) const;

    /**
     * 
     */
    bool EndsWith(const String& Other) const;

    /**
     * 
     */
    String Map(Lambda<const char(const char)> Transform) const;

    /**
     * 
     */
    String Filter(Lambda<bool(const char)> Predicate) const;

    /**
     * 
     */
    Array<char> CharArray() const;

    /**
     * 
     */
    Optional<double> ParseFloat() const;

    /**
     * 
     */
    Optional<bool> ParseBool() const;

    /**
     * 
     */
    Optional<int64> ParseInt() const;

    /**
     * 
     */
    static String ToString(bool B);
    
    /**
     * 
     */
    static String ToString(float F);

    /**
     * 
     */
    static String ToString(int64 I);

    /**
     * 
     */
    static String ToString(double D);

    /**
     *
     */
    static ALWAYSINLINE String PathSeperator();

    /**
     * 
     */
    static ALWAYSINLINE String Whitespace();

    /**
     * 
     */
    static ALWAYSINLINE String UpperCase();

    /**
     * 
     */
    static ALWAYSINLINE String LowerCase();

    /**
     * 
     */
    static ALWAYSINLINE String OctDigits();

    /**
     * 
     */
    static ALWAYSINLINE String Digits();

    /**
     * 
     */
    static ALWAYSINLINE String HexDigits();

    /**
     * 
     */
    static ALWAYSINLINE String Chars();

    /**
     * 
     */
    static ALWAYSINLINE char* Strcpy(char* Dest, const char* Source);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strncpy(char* Dest, const char* Source, int Len);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strcat(char* Dest, const char* Source);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strncat(char* Dest, const char* Source, int Len);
    
    /**
     * 
     */
    static ALWAYSINLINE int Strcmp(const char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE int Strncmp(const char* First, const char* Second, int Len);
    
    /**
     * 
     */
    static ALWAYSINLINE const char* Strchr(const char* Source, int Character);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strchr(char* Source, int Character);
    
    /**
     * 
     */
    static ALWAYSINLINE int Strcspn(const char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE const char* Strpbrk(const char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strpbrk(char* First, const char* Second);
    
    /**
     *
     */
    static ALWAYSINLINE const char* Strrchr(const char* First, int Character);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strrchr(char* First, int Character);
    
    /**
     * 
     */
    static ALWAYSINLINE int Strspn(const char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE const char* Strstr(const char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE char* Strstr(char* First, const char* Second);
    
    /**
     * 
     */
    static ALWAYSINLINE int Strlen(const char* Str);

    /**
     * 
     */
    static ALWAYSINLINE char* Strdup(const char* Str);
};

}