/** @file   HikPlatformSDK.h
 *  @note   Hangzhou Hikvision System Technology Co.,Ltd. All Rights Reserved.
 *  @brief  6.4.1平台SDK的函数接口声明
 *
 *  @author 共享平台客户端开发组
 *  @date     2016/02/04
 *  
 *  @note     历史记录: V1.0.0
 *  @note   
 *
 *  @warning  
 */

#ifndef HikPlatformSDK_h__
#define HikPlatformSDK_h__

#include "HikPtSDK_define.h"

#ifdef HIKPT_EXPORTS
    #define HIKPT_EXTERN    __declspec(dllexport)
#else
    #define HIKPT_EXTERN    __declspec(dllimport)
#endif

#if (defined(_WIN32) || defined(_WIN64))
    #define HIKPT_API __stdcall
#elif defined(__linux__)
    #define HIKPT_API
#else
    #define HIKPT_API
#endif

#ifdef __cplusplus
extern "C" {
#endif  //#ifdef __cplusplus

    /***************************************     库初始化接口 begin       ***************************************/
    /** @fn       int HikPt_Init()
    *   @brief    <初始化接口,支持多次初始化>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_Init();

    /** @fn       int HikPt_Uninit()
    *   @brief    <资源释放接口>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_Uninit();

    /** @fn       int HikPt_Login()
    *   @brief    <用户登录>
    *   @param    <pLoginInfo  (IN)用户登录信息>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_Login(HikLoginInfo* pLoginInfo);

    /** @fn       int HikPt_Logout()
    *   @brief    <用户注销>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_Logout();

    /** @fn       unsigned int HikPt_GetVersion()
    *   @brief    <获取软件版本号>
    *   @return   返回版本号(注: 前4位表示主版本号,其后4位表示子版本号,再其后4位表示修正版本号,最后20位表示svn版本号)
    */
    HIKPT_EXTERN unsigned int HIKPT_API HikPt_GetVersion();

        /** @fn       long HikPt_GetLastError(char* szErrorMsg,int nSize)
    *   @brief    <获取错误信息>
    *   @param    <szErrorMsg  (IN)返回错误描述(保留字段)>
    *   @param    <nSize  (IN)保存错误描述的长度(保留字段)>
    *   @return   成功时返回0; 失败时返回错误码
    */
    HIKPT_EXTERN long HIKPT_API HikPt_GetLastError(char* szErrorMsg=NULL,int nSize=512);
    /***************************************     库初始化接口 end        ***************************************


    /***************************************    获取平台资源接口 begin   ****************************************/
    /** @fn       int HikPt_GetResCellList(HikCellInfo* pResCellList,int& nListSize,int nResPrivilege,int nParentCellId)
    *   @brief    <获取资源组织树列表>
    *   @param    <pResCellList     (IN)返回资源组织树列表>
    *   @param    <nListSize        (IN)返回实际获取资源组织树列表的大小>
    *   @param    <nResPrivilege    (IN)操作权限码(默认为HIK_WBS_OPCODE_PLAYVIEW,表示实时预览),具体定义请见HikPtSDK_define.h>
    *   @param    <nParentCellId    (IN)父组织结点ID(默认为HIK_RS_CELL_PARENT_ID_ALL,表示获取所有层级的组织树列表)>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetResCellList(HikCellInfo* pResCellList,int& nListSize,int nResPrivilege = HIK_WBS_OPCODE_PLAYVIEW,int nParentCellId = HIK_RS_CELL_PARENT_ID_ALL);
    
    /** @fn       int HikPt_GetUserCellList(HikUserOrg* pUserCellList,int& nListSize,int nParentCellId)
    *   @brief    <获取用户组织树列表信息>
    *   @param    <pUserCellList    (IN)返回用户组织树列表>
    *   @param    <nListSize        (IN)返回实际获取用户组织树列表的大小>
    *   @param    <nParentCellId    (IN)父组织结点ID(默认为HIK_RS_CELL_PARENT_ID_ALL,表示获取所有层级的组织树列表)>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetUserCellList(HikUserOrg* pUserCellList,int& nListSize,int nParentCellId = HIK_RS_CELL_PARENT_ID_ALL);

    /** @fn       int HikPt_GetCameraListByCellId(HikCameraInfo* pCameraList,int& nListSize,int nCellId,int nPrivilege)
    *   @brief    <获取监控点列表>
    *   @param    <pCameraList      (IN)返回监控点列表>
    *   @param    <nListSize        (IN)返回实际获取监控点列表的大小>
    *   @param    <nCellId          (IN)组织ID>
    *   @param    <nPrivilege       (IN)操作权限码(默认为HIK_WBS_OPCODE_PLAYVIEW,表示实时预览),具体定义请见HikPtSDK_define.h>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetCameraListByCellId(HikCameraInfo* pCameraList,int& nListSize,int nCellId,int nPrivilege = HIK_WBS_OPCODE_PLAYVIEW);
    
    /** @fn       int HikPt_GetIOListByCellId(HikIOInfo* pIOList,int& nListSize,int nCellId)
    *   @brief    <获取IO通道列表>
    *   @param    <pIOList          (IN)返回IO通道列表>
    *   @param    <nListSize        (IN)返回实际获取IO通道列表的大小>
    *   @param    <nCellId          (IN)组织ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetIOListByCellId(HikIOInfo* pIOList,int& nListSize,int nCellId);
    
    /** @fn       int HikPt_GetTalkChannelListByCellId(HikTalkChannel* pTalkChanList,int& nListSize,int nCellId)
    *   @brief    <获取对讲通道列表>
    *   @param    <pTalkChanList    (IN)返回对讲通道列表>
    *   @param    <nListSize        (IN)返回实际获取对讲通道列表的大小>
    *   @param    <nCellId          (IN)组织ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetTalkChannelListByCellId(HikTalkChannel* pTalkChanList,int& nListSize,int nCellId);
    
    /** @fn       int HikPt_GetUserListByCellId(HikPlatformUser* pUserList,int& nListSize,int nCellId)
    *   @brief    <获取用户列表>
    *   @param    <pUserList        (IN)返回用户列表>
    *   @param    <nListSize        (IN)返回实际获取用户列表的大小>
    *   @param    <nCellId          (IN)组织ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetUserListByCellId(HikPlatformUser* pUserList,int& nListSize,int nCellId);

    /** @fn      int HikPt_GetCameraListByIndexCodes(HikCameraInfo* pCameraList,int& nListSize)
    *   @brief   <批量获取监控点列表>
    *   @param   <pCameraList       (IN)返回监控点列表>
    *   @param   <nListSize         (IN)返回实际获取监控点列表的大小>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetCameraListByIndexCodes(HikCameraInfo* pCameraList,int& nListSize);
    
    /** @fn       int HikPt_GetIOListByIndexCodes(HikIOInfo* pIOList,int& nListSize)
    *   @brief    <批量获取IO通道列表>
    *   @param    <pIOList          (IN)返回IO通道列表>
    *   @param    <nListSize        (IN)返回实际获取IO通道列表的大小>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetIOListByIndexCodes(HikIOInfo* pIOList,int& nListSize);
    
    /** @fn       int HikPt_GetTalkChannelListByIndexCodes(HikTalkChannel* pTalkChanList, int& nListSize)
    *   @brief    <批量获取对讲通道列表>
    *   @param    <pTalkChanList    (IN)返回对讲通道列表>
    *   @param    <nListSize        (IN)返回实际获取对讲通道列表的大小>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetTalkChannelListByIndexCodes(HikTalkChannel* pTalkChanList, int& nListSize);
    
    /** @fn       int HikPt_GetDeviceListByIndexCodes(HikDeviceInfo* pDeviceList, int& nListSize)
    *   @brief    <批量获取编码设备列表>
    *   @param    <pDeviceList      (IN)返回编码设备列表>
    *   @param    <nListSize        (IN)返回实际获取编码设备列表的大小>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetDeviceListByIndexCodes(HikDeviceInfo* pDeviceList, int& nListSize);

    /** @fn       int HikPt_GetTvwallList(HikTvwallInfo* pTvwallInfo, int& nListSize)
    *   @brief    <获取电视墙列表>
    *   @param    <pTvwallInfo      (IN)返回电视墙信息列表>
    *   @param    <nListSize        (IN)返回实际获取电视墙信息列表的大小>
    *   @param    成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetTvwallList(HikTvwallInfo* pTvwallInfo, int& nListSize);
    /***************************************    获取平台资源接口 end     ****************************************/


    /***************************************     实时预览接口 begin      ****************************************/
    /** @fn       long HikPt_StartPlayView(const char* szCameraIndexCode, void* hWnd, pStreamCallback pFun, void* pUserData, HIK_STREAM_TYPE nStream)
    *   @brief    <开始实时预览(可选择码流类型)>
    *   @param    <szCameraIndexCode(IN)监控点编号>
    *   @param    <hWnd             (IN)播放窗口句柄>
    *   @param    <pFun             (IN)预览取流回调函数>
    *   @param    <pUserData        (IN)用户数据>
    *   @param    <nStream          (IN)码流类型(具体见HikPtSDK_define.h定义)>
    *   @return long 预览实例会话ID
    */
    HIKPT_EXTERN long HIKPT_API HikPt_StartPlayView(const char* szCameraIndexCode, void* hWnd, pStreamCallback pFun, void* pUserData, HIK_STREAM_TYPE nStream = main_stream);

    /** @fn       int HikPt_StopPlayView(long lSession)
    *   @brief    <停止实时预览>
    *   @param    <lSession  (IN)HikPt_StartPlayView返回的实例会话ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopPlayView(long lSession);

    /** @fn       int HikPt_StartRecord(long lSession, HikRecordCfgParam* pRecordParam, pPreviewRecordEndCallback pfunrecord,void* pUserData)
    *   @brief    <开始预览本地录像>
    *   @param    <lSession      (IN)HikPt_StartPlayView返回的实例会话ID>
    *   @param    <pRecordParam  (IN)录像参数配置>
    *   @param    <pfunrecord    (IN)预览紧急录像回调函数(注:调用HikPt_StopRecord时触发该回调)>
    *   @param    <pUserData     (IN)用户数据>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StartRecord(long lSession, HikRecordCfgParam* pRecordParam, pPreviewRecordEndCallback pfunrecord,void* pUserData);

    /** @fn       int HikPt_StopRecord(long lSession)
    *   @brief     <停止预览本地录像>
    *   @param     <lSession  (IN)HikPt_StartPlayView返回的实例会话ID>
    *   @return    成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopRecord(long lSession);

    /** @fn       int HikPt_PreviewSnapShot(long lSession, HikSnapParam* pSnapParam, pSnapShotCallback pfunsnap, void* pUserData)
    *   @brief    <预览视频抓图>
    *   @param    <lSession         (IN)HikPt_StartPlayView返回的实例会话ID>
    *   @param    <pSnapParam       (IN)抓图配置参数>
    *   @param    <pfunsnap         (IN)预览抓图回调函数>
    *   @param    <pUserData        (IN)用户数据>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PreviewSnapShot(long lSession, HikSnapParam* pSnapParam, pSnapShotCallback pfunsnap, void* pUserData);

    /** @fn       int HikPt_StartPreviewToWall(int nTvwallId, int nWndId, const char* szCameraIndexCode)
    *   @brief    <开始预览上墙>
    *   @param    <nTvwallId        (IN)电视墙id>
    *   @param    <nWndId           (IN)上墙窗口id>
    *   @param    <szIndexCode      (IN)监控点编号>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StartPreviewToWall(int nTvwallId, int nWndId, const char* szIndexCode);

    /** @fn       int HikPt_StopPreviewToWall(int nTvwallId,int nWndId)
    *   @brief    <停止预览上墙>
    *   @param    <nTvwallId        (IN)电视墙id>
    *   @param    <nWndId           (IN)上墙窗口id>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopPreviewToWall(int nTvwallId, int nWndId);
    /***************************************     实时预览接口 end        ****************************************/


    /***************************************     云台控制接口 begin      ****************************************/
    /** @fn       int HikPt_PtzControl(const char* szCameraIndexCode,int nPtzCommand,int nAction,int nParam,int nSpeed)
    *   @brief    <云台控制>
    *   @param    <szCameraIndexCode  (IN)监控点编号>
    *   @param    <nPtzCommand        (IN)云台控制的命令号>
    *   @param    <nAction            (IN)云台控制的开始或停止>
    *   @param    <nParam             (IN)云台控制参数>
    *   @param    <nSpeed             (IN)云台控制的速度>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PtzControl(const char* szCameraIndexCode,int nPtzCommand,BOOL bAction,int nParam,int nSpeed);

    /** @fn      int HikPt_GetPresetInfo(const char* szCameraIndexCode, HikPresetInfo* pPresetInfo, int& nListSize)
    *   @brief   <获取预置点信息列表>
    *   @param   <szCameraIndexCode  (IN)监控点编号>
    *   @param   <pPresetInfo        (IN)返回预置点信息列表,具体见HikPtSDK_define.h定义>
    *   @param   <nListSize          (IN)返回列表的大小>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetPresetInfo(const char* szCameraIndexCode, HikPresetInfo* pPresetInfo, int& nListSize);

    /** @fn      int HikPt_SetPresetInfo(const char* szCameraIndexCode, const HikPresetInfo* pPresetInfo)
    *   @brief   <设置预置点信息>
    *   @param   <szCameraIndexCode  (IN)监控点编号>
    *   @param   <pPresetInfo        (IN)返回预置点信息列表,具体见HikPtSDK_define.h定义>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_SetPresetInfo(const char* szCameraIndexCode, const HikPresetInfo* pPresetInfo);

    /** @fn      int HikPt_GetCruiseInfo(const char* szCameraIndexCode,int nCruiseNo,HikCruiseInfo* _pInfo, int& nListSize)
    *   @brief   <获取某条巡航路径的巡航点列表>
    *   @param   <szCameraIndexCode  (IN)监控点编号>
    *   @param   <nCruiseNo          (IN)巡航路径编号>
    *   @param   <pCruiseInfo        (IN)返回巡航点信息列表,具体见HikPtSDK_define.h定义>
    *   @param   <nListSize          (IN)返回列表的大小>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_GetCruiseInfo(const char* szCameraIndexCode, int nCruiseNo, HikCruiseInfo* pCruiseInfo, int& nListSize);

    /** @fn      int HikPt_SetCruiseInfo(const char* szCameraIndexCode, int nCruiseNo, HikCruiseInfo* pCruiseInfo)
    *   @brief   <设置某条巡航路径的巡航点列表>
    *   @param   <szCameraIndexCode  (IN)监控点编号>
    *   @param   <nCruiseNo          (IN)巡航路径编号>
    *   @param   <pCruiseInfo        (IN)巡航点信息列表,具体见HikPtSDK_define.h定义>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_SetCruiseInfo(const char* szCameraIndexCode, int nCruiseNo, const HikCruiseInfo* pCruiseInfo);

    /** @fn       int HikPt_PtzLock(const char* szCameraIndexCode,int nLockSec)
    *   @brief    <云台锁定>
    *   @param    <szCameraIndexCode  (IN)监控点编号>
    *   @param    <nLockSec           (IN)云台锁定的时间(单位: 秒)>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PtzLock(const char* szCameraIndexCode,int nLockSec);

    /** @fn       int HikPt_PtzUnLock(const char* szCameraIndexCode)
    *   @brief    <云台解锁>
    *   @param    <szCameraIndexCode  (IN)监控点编号>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PtzUnLock(const char* szCameraIndexCode);
    /***************************************     云台控制接口 end        ****************************************/


    /***************************************     录像回放接口 begin      ****************************************/
    /** @fn       long HikPt_QueryRecord(const char* szCameraIndexCode, const __int64 lStartTime, const __int64 lEndtime, char* szResultXml,int nXmlSize, unsigned int recType = HIK_RECTYPE_ALL)
    *   @brief    <录像查询(注:查询到的结果szResultXml通过HikPt_StartPlayBack进行回放)>
    *   @param    <szCameraIndexCode  (IN)监控点编号>
    *   @param    <lStartTime         (IN)录像开始时间>
    *   @param    <lEndtime           (IN)录像结束时间>
    *   @param    <szResultXml        (IN)录像查询返回结果,其格式请看接口文档>
    *   @param    <nXmlSize           (IN)存放返回结果XML的大小>
    *   @param    <recType            (IN)录像类型,默认为HIK_RECTYPE_ALL(全部),其他值请见HikPtSDK_define.h>
    *   @param    <storeDeviceType    (IN)存储类型,默认为0(中心存储),1(设备存储)
    *   @return   成功时返回录像查询实例ID; 失败时返回-1.
    */
    HIKPT_EXTERN long HIKPT_API HikPt_QueryRecord(const char* szCameraIndexCode, const __int64 lStartTime, const __int64 lEndtime, char* szResultXml,int nXmlSize, unsigned int recType = HIK_RECTYPE_ALL, int storeDeviceType = 0);

    /** @fn       int HikPt_CloseQueryRecord(long lSession)
    *   @brief    <结束录像查询>
    *   @param    <lSession     (IN)HikPt_QueryRecord返回的实例会话ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_CloseQueryRecord(long lSession);

    /** @fn       long HikPt_StartPlayBack(void* hWnd, const char* szResultXml, const __int64 lStartTime, const __int64 lEndtime, pStreamCallback pFun, void* pUserData)
    *   @brief    <开始录像回放>
    *   @param    <hWnd         (IN)播放窗口句柄>
    *   @param    <szResultXml  (IN)HikPt_QueryRecord接口参数中返回的结果XML>
    *   @param    <lStartTime   (IN)开始时间>
    *   @param    <lEndtime     (IN)结束时间>
    *   @param    <pFun         (IN)取流回调函数>
    *   @param    <pUserData    (IN)用户数据>
    *   @return   成功时返回回放实例会话ID; 失败时返回-1.
    */
    HIKPT_EXTERN long HIKPT_API HikPt_StartPlayBack(void* hWnd, const char* szResultXml, const __int64 lStartTime, const __int64 lEndtime, pStreamCallback pFun, void* pUserData);

    /** @fn       int HikPt_StopPlayBack(long lSession)
    *   @brief    <停止录像回放>
    *   @param    <lSession     (IN)HikPt_StartPlayBack返回的实例会话ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopPlayBack(long lSession);

    /** @fn       int HikPt_PlayBackControl(long lSession, int iCommand, const __int64 iParam)
    *   @brief    <回放播放控制>
    *   @param    <lSession     (IN)HikPt_StartPlayBack返回的实例会话ID>
    *   @param    <iCommand     (IN)播放控制命令,具体定义请参照HikPtSDK_define.h>
    *   @param    <iParam       (IN)播放控制参数>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PlayBackControl(long lSession, int iCommand, const __int64 iParam);

    /** @fn       int HikPt_PlaybackSnapShot(long lSession, HikSnapParam* pSnapParam, pSnapShotCallback pfunsnap, void* pUserData)
    *   @brief    <录像回放抓图>
    *   @param    <lSession     (IN)HikPt_StartPlayBack返回的实例会话ID>
    *   @param    <pSnapParam   (IN)抓图配置参数>
    *   @param    <pfunsnap     (IN)回放抓图回调函数>
    *   @param    <pUserData    (IN)用户数据>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_PlaybackSnapShot(long lSession, HikSnapParam* pSnapParam, pSnapShotCallback pfunsnap, void* pUserData);

    /** @fn       long HikPt_StartDownloadRecord(const char* szResultXml, const __int64 lStartTime, const __int64 lEndtime, pStreamCallback pFun, void* pUserData)
    *   @brief    <开始录像下载>
    *   @param    <szResultXml  (IN)HikPt_QueryRecord接口参数中返回的结果XML>
    *   @param    <lStartTime   (IN)开始时间>
    *   @param    <lEndtime     (IN)结束时间>
    *   @param    <pFun         (IN)回放取流回调函数>
    *   @param    <pUserData    (IN)用户数据>
    *   @return   成功时返回录像下载实例会话ID; 失败时返回-1.
    */
    HIKPT_EXTERN long HIKPT_API HikPt_StartDownloadRecord(const char* szResultXml, const __int64 lStartTime, const __int64 lEndtime, pStreamCallback pFun, void* pUserData);
    
    /** @fn      int HikPt_StopDownloadRecord(long lSession)
    *   @brief   <停止录像下载>
    *   @param   <lSession     (IN)HikPt_StartDownloadRecord返回的实例会话ID>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopDownloadRecord(long lSession);
    /***************************************     录像回放接口 end        ****************************************/


    /***************************************     告警事件接口 begin      ****************************************/
    /** @fn      int HikPt_StartRecvRealAlarmEvent(pAlarmEventCallback pfun, void* pUserData)
    *   @brief   <开始接收实时告警事件>
    *   @param   <pfun          (IN)实时告警事件接收回调函数>
    *   @param   <pUserData     (IN)用户数据>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StartRecvRealAlarmEvent(pAlarmEventCallback pfun, void* pUserData);

    /** @fn      int HikPt_StopRecvRealAlarmEvent()
    *   @brief   <停止接收实时告警事件>
    *   @return  成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopRecvRealAlarmEvent();
    
    /** @fn      int HikPt_QueryHistoryAlarmEvent(const pHIKSEARCHALARMLOGPARAM pSearchParam, HikPAGEINFO* pPageInfo, pHIKSEARCHALARMLOGRESULT pEventList,int& nListSize)
    *   @brief   <查询历史告警事件日志>
    *   @param   <pSearchParam  (IN)查询参数>
    *   @param   <pPageInfo     (IN)分页信息>
    *   @param   <pEventList    (OUT)返回历史告警日志列表>
    *   @param   <nListSize     (OUT)返回实际查询历史告警条数>
    *   @return  成功时返回0; 失败时返回-1..
    */
    HIKPT_EXTERN int HIKPT_API HikPt_QueryHistoryAlarmEvent(const pHIKSEARCHALARMLOGPARAM pSearchParam, HikPAGEINFO* pPageInfo, pHIKSEARCHALARMLOGRESULT pEventList, int& nListSize);
    /***************************************     告警事件接口 end        ****************************************/


    /***************************************     网络对讲接口 begin      ****************************************/
    /** @fn       int HikPt_StartTalk(int nTalkId)
    *   @brief    <开始对讲>
    *   @param    <nTalkId  (IN)对讲通道ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StartTalk(int nTalkId);

    /** @fn       int HikPt_StopTalk(int nTalkId)
    *   @brief    <停止对讲>
    *   @param    <nTalkId  (IN)对讲通道ID>
    *   @return   成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StopTalk(int nTalkId);
    /***************************************     网络对讲接口 end        ****************************************/


    /***************************************     GPS信息接口 begin        ****************************************/
    /** @fn       HikPt_StartGPSReceive(pGPSReceiveCallback pGPSReceiveCB,void* pUserData)
    *  @brief     <开始获取GPS信息>
    *  @param     <pGPSReceiveCB  (IN)MQ GPS消息回调函数>
    *  @param     <pUser  (IN)用户数据>
    *  @return    成功时返回0; 失败时返回-1.
    */
    HIKPT_EXTERN int HIKPT_API HikPt_StartGPSReceive(pGPSReceiveCallback pGPSReceiveCB,void* pUserData);

    /** @fn       HikPt_StopGPSReceive()
    *  @brief     停止获取GPS信息
    */
    HIKPT_EXTERN void HIKPT_API HikPt_StopGPSReceive();
    /***************************************     GPS信息接口 end        ****************************************/


#ifdef __cplusplus
}
#endif  //#ifdef __cplusplus

#endif // HikPlatformSDK_h__

