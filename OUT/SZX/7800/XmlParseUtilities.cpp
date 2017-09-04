/**@file     XmlParseUtilities.cpp
 * @note     HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 * @brief    XmlParseUtilities.cpp : implementation file
 * @history: see XmlParseUtilities.h for details
 */
#include "XmlParseUtilities.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <hpr/HPR_String.h>

namespace
{
    const time_t INVALID_TIME_VALUE = -1;
}

CXmlParseUtilities::CXmlParseUtilities()
{

}

CXmlParseUtilities::~CXmlParseUtilities()
{

}

// 将string时间转为time_t时间，参数形如： 2013-04-11T15:00:25.000Z
time_t CXmlParseUtilities::TimeStringToNumber(const char* szTime)
{
    if (szTime != NULL)
    {
        tm _tm = {0};
        int minsec = 0;
        sscanf_s(szTime, "%d-%d-%dT%d:%d:%d.%dZ", 
            &_tm.tm_year,&_tm.tm_mon,&_tm.tm_mday,
            &_tm.tm_hour,&_tm.tm_min,&_tm.tm_sec, &minsec);
        _tm.tm_year -= 1900;
        _tm.tm_mon -= 1;
        return _mktime64(&_tm);
    }
    return INVALID_TIME_VALUE;
}

// 获取time_t数值
int CXmlParseUtilities::GetTimetValue(TiXmlElement* pElm, time_t& retVal)
{
    time_t tTemp = INVALID_TIME_VALUE;
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            tTemp = TimeStringToNumber(pText);
        }
    }
    if (INVALID_TIME_VALUE == tTemp)
    {
        return -1;
    }
    retVal = tTemp;
    return 0;
}

// 获取Int数值
int CXmlParseUtilities::GetIntValue(TiXmlElement* pElm, int& retVal)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            retVal = HPR_Atoi32(pText);
            return 0;
        }
    }
    return -1;
}

// 获取float数值
int CXmlParseUtilities::GetFloatValue(TiXmlElement* pElm, float& retVal)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            retVal = (float)atof(pText);

            return 0;
        }
    }
    return -1;
}

// 获取ULONG数值
int CXmlParseUtilities::GetULongValue(TiXmlElement* pElm, unsigned long& retVal)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            retVal = static_cast<unsigned long>(HPR_Atoi64(pText));
            return 0;
        }
    }
    return -1;
}
// 获取ULONGLONG数值
int CXmlParseUtilities::GetULonglongValue(TiXmlElement* pElm, unsigned long long& retVal)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            retVal = static_cast<unsigned long long>(HPR_Atoi64(pText));
            return 0;
        }
    }
    return -1;
}
// 获取string数值
int CXmlParseUtilities::GetStringValue(TiXmlElement* pElm, std::string& retVal)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            retVal = pText;
            return 0;
        }
    }
    return -1;
}

// 获取字符串数值
int CXmlParseUtilities::GetCharArrayValue(TiXmlElement* pElm, char retVal[], const size_t nSize)
{
    if (pElm != NULL)
    {
        const char* pText = pElm->GetText();
        if (pText != NULL)
        {
            strcpy_s(retVal, nSize-1, pText);
            return 0;
        }
    }
    return -1;
}