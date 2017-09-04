/**@file  SearchResultParser.h
* @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
* @brief  查询结果XML的解析类
*
* @author yangjw
* @date   2013/04/24
*/
#pragma once
#include "PBTypes.h"

class CSearchResultParser
{
public:
    CSearchResultParser();
    ~CSearchResultParser();

public:
    /**@fn   <Parse>
    *@brief  <解析xml>
    *@param  <xml: xml字符串>
    *@param  <resultMap: 解析获得的查询结果>
    *@return <PB_RET_TYPE: 成功返回0，失败返回错误码>
    */
    static PB_RET_TYPE Parse(const std::string& xml, RECORD_SEARCH_RESULT_MAP& resultMap);
};
