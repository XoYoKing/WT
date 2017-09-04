/**@file  XmlParseUtilities.h
* @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
* @brief  XML解析的实用类
*
* @author yangjw
* @date   2013/04/24
*/
#pragma once
#include <tinyxml/tinyxml.h>

//forward declaration
class TiXmlElement;

class CXmlParseUtilities
{
public:
    CXmlParseUtilities();
    ~CXmlParseUtilities();

public:
    // 将string时间转为time_t时间，参数形如： 2013-04-11T15:00:25.000Z
    static time_t TimeStringToNumber(const char* szTime);
    // 获取time_t数值
    static int GetTimetValue(TiXmlElement* pElm, time_t& retVal);
    // 获取Int数值
    static int GetIntValue(TiXmlElement* pElm, int& retVal);
    // 获取float数值
    static int GetFloatValue(TiXmlElement* pElm, float& retVal);
    // 获取ULONG数值
    static int GetULongValue(TiXmlElement* pElm, unsigned long& retVal);
    // 获取ULONGLONG数值
    static int GetULonglongValue(TiXmlElement* pElm, unsigned long long& retVal);
    // 获取string数值
    static int GetStringValue(TiXmlElement* pElm, std::string& retVal);
    // 获取字符串数值
    static int GetCharArrayValue(TiXmlElement* pElm, char retVal[], const size_t nSize);
};
