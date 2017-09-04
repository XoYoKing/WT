#pragma once
#include "stdafx.h"
#include "stringoperdef.h"
//lint -save -e522
//lint -save -e1055
//lint -save -e550
std::string _Unicode2Asc(const WCHAR *pwchar)
{
    if (pwchar == NULL)
    {
        return std::string("");
    }
    USES_CONVERSION;
    return std::string(W2A(pwchar));
}

std::wstring _Asc2Unicode(const char *pchar)
{
    if (pchar == NULL)
    {
        return std::wstring(L"");
    }
    USES_CONVERSION;
    return std::wstring(A2W(pchar));
}

_stringT _Asc2T(const char *pchar)
{
    if (pchar == NULL)
    {
        return _stringT(_T(""));
    }
#ifdef _UNICODE
    USES_CONVERSION;
    return _stringT((TCHAR*)A2W(pchar));
#else
    return _stringT((TCHAR *)pchar);
#endif
}

_stringT _Unicode2T(const WCHAR *pwchar)
{
    if (pwchar == NULL)
    {
        return _stringT(_T(""));
    }
#ifdef _UNICODE
    return _stringT((TCHAR*)pwchar);
#else
    USES_CONVERSION;
    return _stringT((TCHAR *)W2A(pwchar));
#endif
}

std::string _T2Asc(const TCHAR *ptchar)
{
    if (ptchar == NULL)
    {
        return std::string("");
    }
#ifdef _UNICODE
    return _Unicode2Asc(ptchar);
#else
    return std::string((char *)ptchar);
#endif
}

std::wstring _T2Unicode(const TCHAR *ptchar)
{
    if (ptchar == NULL)
    {
        return std::wstring(L"");
    }
#ifdef _UNICODE
    return std::wstring((WCHAR *)ptchar);
#else
    return _Asc2Unicode(ptchar);
#endif
}

std::string mb2u8(LPCSTR cont)
{
    if (NULL == cont)
    {
        return std::string("");
    }

    int num = MultiByteToWideChar(CP_ACP, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[num];
    MultiByteToWideChar(CP_ACP, NULL, cont, -1, buffw, num);

    int len = WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[len + 1]; 
    WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;

    std::string strRtn;
    strRtn = lpsz;
    delete[] lpsz;

    return strRtn ;
}

std::string u82mb(LPCSTR cont)
{
    if (NULL == cont)
    {
        return std::string("");
    }

    int num = MultiByteToWideChar(CP_UTF8, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[num];
    MultiByteToWideChar(CP_UTF8, NULL, cont, -1, buffw, num);

    int len = WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[len + 1]; 
    WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;

    std::string strRtn;
    strRtn = lpsz;
    delete[] lpsz;

    return strRtn;
}

//lint -restore