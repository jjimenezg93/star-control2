#ifndef UGINE_STRING_H
#define UGINE_STRING_H

#include "array.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif

#pragma warning(push, 0)
class String {
public:
    String(const char* str = "");
    String(const String& str);
    String(unsigned int length, char c);
    ~String();

    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;
    String operator+(const String& other) const;
    String operator+(char c) const;
    String& operator=(const String& other);
    String& operator=(char c);
    String& operator+=(const String& other);
    String& operator+=(char c);
    char& operator[](unsigned int pos);
    const char& operator[](unsigned int pos) const;

    int Length() const { return length; }

    static String FromInt(int val);
    static String HexFromInt(int val);
    static String FromFloat(float val);

    int ToInt() const;
    float ToFloat() const;
    const char* ToCString() const { return buffer; }

    static String Chr(unsigned char val) { unsigned char c[] = {val, 0}; return String((char*)c); }
    unsigned char Asc() const { return buffer[0]; }

    String Left(int n) const;
    String Right(int n) const;
    String Mid(int ofs, int n);
    String Replace(const String& find, const String& rep) const;
    int Find(const String& str, int ofs) const;

    String Upper() const;
    String Lower() const;
    String LTrim() const;
    String RTrim() const;
    String Trim() const;
    String LSet(int len, const String& c) const;
    String RSet(int len, const String& c) const;

    String StripExt() const;
    String StripDir() const;
    String ExtractExt() const;
    String ExtractDir() const;
    String RealPath() const;

    static String Read(const String& filename);
    void Write(const String& filename, bool append = true) const;

    Array<String> Split(const String& delim) const;
private:
    char* buffer;
    int length;
    int bufferSize;
};

inline String::String(const char* str) {
    length = strlen(str);
    bufferSize = sizeof(char)*(length+1);
    buffer = (char*)malloc(bufferSize);
    strcpy(buffer, str);
}

inline String::String(const String& str) {
    length = str.length;
    bufferSize = sizeof(char)*(length+1);
    buffer = (char*)malloc(bufferSize);
    strcpy(buffer, str.buffer);
}

inline String::String(unsigned int length, char c) {
    this->length = length;
    bufferSize = sizeof(char)*(length+1);
    buffer = (char*)malloc(bufferSize);
    memset(buffer, (int)c, length);
    buffer[length] = '\0';
}

inline String::~String() {
    free(buffer);
}

inline bool String::operator==(const String& other) const {
    return strcmp(buffer, other.buffer) == 0;
}

inline bool String::operator!=(const String& other) const {
    return strcmp(buffer, other.buffer) != 0;
}

inline bool String::operator<(const String& other) const {
    return strcmp(buffer, other.buffer) < 0;
}

inline bool String::operator>(const String& other) const {
    return strcmp(buffer, other.buffer) > 0;
}

inline String String::operator+(const String& other) const {
    char* buf = (char*)malloc(length + other.length + 1);
    strcpy(buf, buffer);
    strcat(buf, other.buffer);
    String str(buf);
    free(buf);
    return str;
}

inline String String::operator+(char c) const {
    char s[2] = {c, '\0'};
    return *this + s;
}

inline String& String::operator=(const String& other) {
    if ( bufferSize < other.length + 1 ) {
        bufferSize = sizeof(char)*(other.length+1);
        free(buffer);
        buffer = (char*)malloc(bufferSize);
    }
    length = other.length;
    strcpy(buffer, other.buffer);
    return *this;
}

inline String& String::operator=(char c) {
    char s[2] = {c, '\0'};
    return *this = s;
}

inline String& String::operator+=(const String& other) {
    return *this = *this + other;
}

inline String& String::operator+=(char c) {
    char s[2] = {c, '\0'};
    return *this += s;
}

inline char& String::operator[](unsigned int pos) {
    return buffer[pos];
}

inline const char& String::operator[](unsigned int pos) const {
    return buffer[pos];
}

inline String String::FromInt(int val) {
    char buf[32];
    sprintf(buf, "%i", val);
    return String(buf);
}

inline String String::HexFromInt(int val) {
    char buf[32];
    sprintf(buf, "%m_x", val);
    return String(buf);
}

inline String String::FromFloat(float val) {
    char buf[32];
    sprintf(buf, "%f", val);
    return String(buf);
}

inline int String::ToInt() const {
    int ret = 0;
    sscanf(buffer, "%i", &ret);
    return ret;
}

inline float String::ToFloat() const {
    float ret = 0;
    sscanf(buffer, "%f", &ret);
    return ret;
}

inline String String::Left(int n) const {
    char* buf = (char*)malloc(n+1);
    strncpy(buf, buffer, n);
    buf[n] = '\0';
    String str(buf);
    free(buf);
    return str;
}

inline String String::Right(int n) const {
    char* buf = (char*)malloc(n+1);
    strncpy(buf, &buffer[length-n], n);
    buf[n] = '\0';
    String str(buf);
    free(buf);
    return str;
}

inline String String::Mid(int ofs, int n) {
    char* buf = (char*)malloc(n+1);
    strncpy(buf, &buffer[ofs], n);
    buf[n] = '\0';
    String str(buf);
    free(buf);
    return str;
}

#pragma warning(disable: 4706)
inline String String::Replace(const String& find, const String& rep) const {
    String str;

    // If string is not found, return unmodified string
    if ( !strstr(buffer, find.buffer) ) return *this;

    // Replace all ocurrences
    const char* p = NULL;
    const char* lastp = buffer;
    while ( (p = strstr(lastp, find.buffer)) ) {
        // Copy chars until p
        while ( lastp != p ) {
            str += *lastp;
            lastp++;
        }

        // Copy replacement chars
        for ( int i = 0; i < rep.length; i++ ) {
            str += rep.buffer[i];
        }

        // Move lastp to after the replaced string
        lastp += find.length;
    }

    // Copy remaining chars
    while ( *lastp != '\0' ) {
        str += *lastp;
        lastp++;
    }

    return str;
}
#pragma warning(default: 4706)

inline int String::Find(const String& str, int ofs) const {
    const char* p = strstr(&buffer[ofs], str.buffer);
    if ( p == NULL )
        return -1;
    else
        return (p - buffer);
}

inline String String::Upper() const {
    String str;
    for ( int i = 0; i < length; i++ )
        str += toupper(buffer[i]);
    return str;
}

inline String String::Lower() const {
    String str;
    for ( int i = 0; i < length; i++ )
        str += tolower(buffer[i]);
    return str;
}

inline String String::LTrim() const {
    // Count spaces at the beginning
    int i = 0;
    while ( i < length && isspace(buffer[i]) ) i++;

    // Return trimmed string
    return Right(length - i);
}

inline String String::RTrim() const {
    // Look for first non space on the right
    int i = length - 1;
    int pos = -1;
    while ( i > 0 && pos == -1 ) {
        if ( !isspace(buffer[i]) ) pos = i+1;
        i--;
    }

    if ( pos == -1 ) pos = length;

    // Return trimmed string
    return Left(pos);
}

inline String String::Trim() const {
    return LTrim().RTrim();
}

inline String String::LSet(int len, const String& c) const {
    String str;
    for ( int i = 0; i < len - length; i++ )
        str += c.buffer[0];
    str += Left(len);
    return str;
}

inline String String::RSet(int len, const String& c) const {
    String str = Left(len);
    for ( int i = length; i < len; i++)
        str += c.buffer[0];
    return str;
}

inline String String::StripExt() const {
    // Find last "."
    const char* dotp = strrchr(buffer, '.');

    // If it contains no extension, return unmodified filename
    if ( dotp == NULL ) return *this;

    // Copy characters before the last "."
    String str;
    const char* p = buffer;
    while ( p != dotp ) {
        str += *p;
        p++;
    }

    return str;
}

inline String String::StripDir() const {
    // Replace "\" with "/"
    String filename = Replace("\\", "/");

    // Find last "/"
    const char* slashp = strrchr(filename.buffer, '/');

    // If contains no path, return unmodified filename
    if ( slashp == NULL ) return *this;

    // Copy all characters after the last "/"
    String str;
    slashp++;   // Skip "/"
    while ( *slashp != '\0' ) {
        str += *slashp;
        slashp++;
    }

    return str;
}

inline String String::ExtractExt() const {
    // Find last "."
    const char* dotp = strrchr(buffer, '.');

    // If it contains no extension, return empty string
    if ( dotp == NULL ) return "";

    // Copy characters after the last "."
    String str;
    dotp++; // Skip "."
    while ( *dotp != '\0' ) {
        str += *dotp;
        dotp++;
    }

    return str;
}

inline String String::ExtractDir() const {
    // Replace "\" with "/"
    String filename = Replace("\\", "/");

    // Find last "/"
    const char* slashp = strrchr(filename.buffer, '/');

    // If contains no path, return empty string
    if ( slashp == NULL ) return "";

    // Copy all characters before the last "/"
    String str = "";
    const char* p = filename.buffer;
    while ( p != slashp ) {
        str += *p;
        p++;
    }

    return str;
}

inline String String::RealPath() const {
    char path[FILENAME_MAX];
    realpath(buffer, path);
    return String(path);
}

inline String String::Read(const String& filename) {
    // Open file to read
    FILE* f = fopen(filename.buffer, "rb");

    // If it does not exist, return empty string
    if ( f == NULL ) return "";

    // Get file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Allocate contents in a buffer
    char* buf = (char*)malloc(size+1);
    fread(buf, sizeof(char), size, f);
    buf[size] = '\0';

    // Copy buffer into string
    String str = buf;

    // Free buffer
    free(buf);

    // Return string
    return str;
}

inline void String::Write(const String& filename, bool append) const {
    // Open file to write or append
    FILE* f = fopen(filename.buffer, append ? "ab" : "wb");

    // If it could not be opened, return
    if ( f == NULL ) return;

    // Write string buffer
    fwrite(buffer, sizeof(char), length, f);

    // Close file
    fclose(f);
}

inline Array<String> String::Split(const String& delim) const {
    Array<String> arr;

    // Return empty array if length = 0 or delim = 0
    if ( Length() == 0 || delim.buffer[0] == 0) return arr;

    // Fill array
    String str;
    for ( int i = 0; i < Length(); i++ ) {
        char c = buffer[i];
        if ( c == delim.buffer[0] ) {
            arr.Add(str);
            str = "";
        } else {
            str += c;
        }
    }
    arr.Add(str);

    return arr;
}

#pragma warning(pop)
#endif // UGINE_STRING_H
