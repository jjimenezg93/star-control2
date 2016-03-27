#ifndef CORE_FILE_H
#define CORE_FILE_H

#include "string.h"
#include <stdio.h>

#define FILE_READ   0
#define FILE_WRITE  1
#define FILE_APPEND 2

class File {
public:
    File(const String& filename, int mode);
    ~File() { Close(); }

    bool IsOpened() const { return handle != 0; }
    void Close() { if ( handle ) fclose(handle); handle = 0; }
    unsigned long Size() const { return size; }
    unsigned long Pos() const { return ftell(handle); }
    void Seek(unsigned long offset) { fseek(handle, offset, SEEK_SET); }
    bool Eof() const { return Pos() == size; }

    signed char ReadInt8();
    signed short ReadInt16();
    signed int ReadInt();
    signed long long ReadInt64();
    unsigned char ReadUInt8();
    unsigned short ReadUInt16();
    unsigned int ReadUInt();
    unsigned long long ReadUInt64();
    float ReadFloat();
    double ReadDouble();
    String ReadCString();
    String ReadCLine();
    unsigned int ReadBytes(void* buffer, unsigned int count) { return fread(buffer, 1, count, handle); }

    void WriteInt8(signed char v) { fwrite(&v, 1, sizeof(char), handle); }
    void WriteInt16(signed short v) { fwrite(&v, 1, sizeof(short), handle); }
    void WriteInt(signed int v) { fwrite(&v, 1, sizeof(int), handle); }
    void WriteInt64(signed long v) { fwrite(&v, 1, sizeof(long), handle); }
    void WriteUInt8(unsigned char v) { fwrite(&v, 1, sizeof(char), handle); }
    void WriteUInt16(unsigned short v) { fwrite(&v, 1, sizeof(short), handle); }
    void WriteUInt(unsigned int v) { fwrite(&v, 1, sizeof(int), handle); }
    void WriteUInt64(unsigned long v) { fwrite(&v, 1, sizeof(long), handle); }
    void WriteFloat(float v) { fwrite(&v, 1, sizeof(float), handle); }
    void WriteDouble(double v) { fwrite(&v, 1, sizeof(double), handle); }
    void WriteCString(const String& v) { fwrite(v.ToCString(), v.Length()+1, sizeof(char), handle); }
    void WriteCLine(const String& v) { String str = v + "\r\n"; fwrite(str.ToCString(), str.Length(), sizeof(char), handle); }
    unsigned int WriteBytes(const void* buffer, unsigned int count) { return fwrite(buffer, 1, count, handle); }
private:
    FILE* handle;
    unsigned long size;
};

inline File::File(const String& filename, int mode) {
    String attr;
    switch ( mode ) {
    case FILE_READ:
        attr = "rb";
        break;
    case FILE_WRITE:
        attr = "wb";
        break;
    case FILE_APPEND:
        attr = "ab";
        break;
    }

    handle = fopen(filename.ToCString(), attr.ToCString());
    size = -1;
    if ( handle && mode == FILE_READ ) {
        fseek(handle, 0, SEEK_END);
        size = ftell(handle);
        fseek(handle, 0, SEEK_SET);
    }
}

inline signed char File::ReadInt8() {
    signed char v;
    fread(&v, 1, sizeof(char), handle);
    return v;
}

inline signed short File::ReadInt16() {
    signed short v;
    fread(&v, 1, sizeof(short), handle);
    return v;
}

inline signed int File::ReadInt() {
    signed int v;
    fread(&v, 1, sizeof(int), handle);
    return v;
}

inline signed long long File::ReadInt64() {
    signed long v;
    fread(&v, 1, sizeof(long), handle);
    return v;
}

inline unsigned char File::ReadUInt8() {
    unsigned char v;
    fread(&v, 1, sizeof(char), handle);
    return v;
}

inline unsigned short File::ReadUInt16() {
    unsigned short v;
    fread(&v, 1, sizeof(short), handle);
    return v;
}

inline unsigned int File::ReadUInt() {
    unsigned int v;
    fread(&v, 1, sizeof(int), handle);
    return v;
}

inline unsigned long long File::ReadUInt64() {
    unsigned long v;
    fread(&v, 1, sizeof(long), handle);
    return v;
}

inline float File::ReadFloat() {
    float v;
    fread(&v, 1, sizeof(float), handle);
    return v;
}

inline double File::ReadDouble() {
    double v;
    fread(&v, 1, sizeof(double), handle);
    return v;
}

inline String File::ReadCString() {
    String str;
    char c = ReadInt8();
    while ( c != 0 ) {
        str += c;
        c = ReadInt8();
    }
    return str;
}

inline String File::ReadCLine() {
    String str;
    char c = ReadInt8();
    while ( c != '\r' && c != '\n' ) {
        str += c;
        if ( !Eof() ) {
            c = ReadInt8();
        } else {
            break;
        }
    }
    if ( c == '\r' && !Eof() ) {
        c = ReadInt8();
        if ( c != '\n' ) Seek(Pos()-1);
    }
    return str;
}

#endif // CORE_FILE_H
