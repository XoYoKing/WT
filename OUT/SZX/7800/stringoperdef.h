#pragma once
#include <AtlBase.h>
#include <string>

#ifdef _UNICODE
#define _stringT std::wstring
#else
#define _stringT std::string
#endif

//返回值无需Delete
#define Unicode2Asc(val) ((char *)_Unicode2Asc(val).c_str())
#define Asc2Unicode(val) ((WCHAR*)_Asc2Unicode(val).c_str())
#define Asc2T(val) ((TCHAR*)_Asc2T(val).c_str())
#define Unicode2T(val) ((TCHAR*)_Unicode2T(val).c_str())
#define T2Asc(val) ((char*)_T2Asc(val).c_str())
#define T2Unicode(val) ((WCHAR*)_T2Unicode(val).c_str())

std::string _Unicode2Asc(const WCHAR *pwchar);
std::wstring _Asc2Unicode(const char *pchar);
_stringT _Asc2T(const char *pchar);
_stringT _Unicode2T(const WCHAR *pwchar);

std::string _T2Asc(const TCHAR *ptchar);
std::wstring _T2Unicode(const TCHAR *ptchar);

std::string u82mb(LPCSTR cont);
std::string mb2u8(LPCSTR cont);
