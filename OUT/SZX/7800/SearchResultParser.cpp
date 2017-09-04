/**@file     SearchResultParser.cpp
 * @note     HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 * @brief    SearchResultParser.cpp : implementation file
 * @history: see SearchResultParser.h for details
 */
#include "SearchResultParser.h"
#include "XmlParseUtilities.h"

namespace
{
    const char SegmentList[] = "SegmentList";
    const char RecordSegment[] = "RecordSegment";
    const char BeginTime[] = "BeginTime";
    const char EndTime[] = "EndTime";
    const char RecordType[] = "RecordType";
    const char MediaDataLen[] = "MediaDataLen";
    const char IsLocked[] = "IsLocked";
    const char PlayURL[] = "PlayURL";
}

CSearchResultParser::CSearchResultParser()
{

}

CSearchResultParser::~CSearchResultParser()
{

}

// <解析xml>
PB_RET_TYPE CSearchResultParser::Parse(const std::string& xml, RECORD_SEARCH_RESULT_MAP& resultMap)
{
    TiXmlDocument xmlDoc;
    xmlDoc.Parse(xml.c_str(), NULL, TIXML_ENCODING_LEGACY);
    if(xmlDoc.Error())
    {
        return -1;
    }

    TiXmlHandle docHandle(&xmlDoc);
    TiXmlElement* pElemSegment = docHandle.FirstChild(SegmentList).FirstChild(RecordSegment).ToElement();
    if (NULL == pElemSegment)
    {
        pElemSegment = docHandle.FirstChild("QueryResult").FirstChild(SegmentList).FirstChild(RecordSegment).ToElement();
    }
    while (pElemSegment != NULL)
    {
        TiXmlHandle handleSegment(pElemSegment);
        SEGMENT_DETAILED_INFO stSegInfo;
        if (0 != CXmlParseUtilities::GetTimetValue(handleSegment.FirstChild(BeginTime).ToElement(), stSegInfo.stBrief.tBegin))
        {
            //PLAYBACK_WARN("FAILED to parse: BeginTime");
            pElemSegment = pElemSegment->NextSiblingElement(RecordSegment);
            continue;
        }
        if (0 != CXmlParseUtilities::GetTimetValue(handleSegment.FirstChild(EndTime).ToElement(), stSegInfo.stBrief.tEnd))
        {
            //PLAYBACK_WARN("FAILED to parse: EndTime");
            pElemSegment = pElemSegment->NextSiblingElement(RecordSegment);
            continue;
        }
        if (0 != CXmlParseUtilities::GetIntValue(handleSegment.FirstChild(RecordType).ToElement(), stSegInfo.stBrief.recordType))
        {
            //PLAYBACK_WARN("FAILED to parse RecordType");
        }
        if (0 != CXmlParseUtilities::GetULongValue(handleSegment.FirstChild(MediaDataLen).ToElement(), stSegInfo.mediaDataLen))
        {
            //PLAYBACK_WARN("FAILED to parse MediaDataLen");
        }
        if (0 != CXmlParseUtilities::GetIntValue(handleSegment.FirstChild(IsLocked).ToElement(), stSegInfo.bLocked))
        {
            //PLAYBACK_WARN("FAILED to parse Locked");
        }
        if (0 != CXmlParseUtilities::GetStringValue(handleSegment.FirstChild(PlayURL).ToElement(), stSegInfo.stBrief.url))
        {
            //PLAYBACK_WARN("FAILED to parse PlayURL");
            pElemSegment = pElemSegment->NextSiblingElement(RecordSegment);
            continue;
        }
        stSegInfo.tLockBegin = stSegInfo.stBrief.tBegin;
        stSegInfo.tLockEnd = stSegInfo.stBrief.tEnd;

        if (resultMap.find(stSegInfo.stBrief.tBegin) != resultMap.end())
        {
            //PLAYBACK_WARN("Segment beginTime repeat, tBegin=%I64d, tEnd=%I64d", 
            //    stSegInfo.stBrief.tBegin, stSegInfo.stBrief.tEnd);

            time_t tEnd = resultMap[stSegInfo.stBrief.tBegin].stBrief.tEnd;
            if (tEnd < stSegInfo.stBrief.tEnd) // 取较长的那个片段
            {
                resultMap[stSegInfo.stBrief.tBegin] = stSegInfo;
            }
        }
        else
        {
            resultMap[stSegInfo.stBrief.tBegin] = stSegInfo;
        }
        pElemSegment = pElemSegment->NextSiblingElement(RecordSegment);
    }
    return 0;
}
