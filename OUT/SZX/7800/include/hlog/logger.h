
/** @file   logger.h
 *  @note   Hangzhou Hikvision System Technology Co.,Ltd. All Rights Reserved.
 *  @brief  定义客户端中hlog日志宏
 *
 *  @author huangjunyf2
 *  @date   2012/12/29
 *  
 *  @note   历史记录：
 *  @note   V1.0.0.0 Create
 *
 */
#ifndef _logger_H_
#define _logger_H_

#include "hlog.h"

#if (defined _WIN32 || defined _WIN64)
#define SSO_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "SSO", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SSO_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "SSO", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SSO_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "SSO", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SSO_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "SSO", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SSO_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "SSO", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define SSO_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "SSO", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define SSO_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "SSO", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define SSO_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "SSO", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define SSO_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "SSO", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define SSO_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "SSO", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define CLIENT_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "client", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define CLIENT_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "client", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define CLIENT_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "client", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define CLIENT_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "client", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define CLIENT_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "client", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define CLIENT_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "client", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define CLIENT_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "client", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define CLIENT_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "client", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define CLIENT_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "client", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define CLIENT_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "client", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif


#if (defined _WIN32 || defined _WIN64)
#define IPC_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "ipc", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define IPC_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "ipc", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define IPC_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "ipc", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define IPC_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "ipc", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define IPC_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "ipc", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define IPC_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "ipc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define IPC_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "ipc", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define IPC_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "ipc", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define IPC_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "ipc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define IPC_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "ipc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define APC_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "apc", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define APC_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "apc", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "apc", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "apc", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "apc", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define APC_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "apc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "apc", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "apc", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "apc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "apc", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define APC_REALALARM_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "apcrealalarm", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define APC_REALALARM_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "apcrealalarm", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_REALALARM_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "apcrealalarm", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_REALALARM_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "apcrealalarm", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define APC_REALALARM_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "apcrealalarm", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define APC_REALALARM_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "apcrealalarm", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_REALALARM_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "apcrealalarm", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_REALALARM_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "apcrealalarm", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_REALALARM_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "apcrealalarm", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define APC_REALALARM_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "apcrealalarm", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// 预览模块日志的宏定义
#if (defined _WIN32 || defined _WIN64)
#define PREVIEW_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "preview", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PREVIEW_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "preview", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PREVIEW_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "preview", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PREVIEW_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "preview", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PREVIEW_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "preview", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PREVIEW_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "preview", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PREVIEW_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "preview", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PREVIEW_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "preview", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PREVIEW_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "preview", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PREVIEW_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "preview", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// 回放模块日志的宏定义
#if (defined _WIN32 || defined _WIN64)
#define PLAYBACK_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "playback", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PLAYBACK_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "playback", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PLAYBACK_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "playback", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PLAYBACK_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "playback", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PLAYBACK_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "playback", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PLAYBACK_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "playback", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAYBACK_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "playback", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAYBACK_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "playback", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAYBACK_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "playback", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAYBACK_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "playback", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// 基础网络模块日志的宏定义
#if (defined _WIN32 || defined _WIN64)
#define BASENET_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "basenet", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define BASENET_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "basenet", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define BASENET_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "basenet", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define BASENET_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "basenet", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define BASENET_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "basenet", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define BASENET_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "basenet", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define BASENET_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "basenet", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define BASENET_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "basenet", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define BASENET_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "basenet", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define BASENET_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "basenet", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define DOWNLOAD_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "download", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DOWNLOAD_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "download", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DOWNLOAD_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "download", "<%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DOWNLOAD_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "download", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DOWNLOAD_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "download", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DOWNLOAD_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "download", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DOWNLOAD_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "download", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DOWNLOAD_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "download", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DOWNLOAD_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "download", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DOWNLOAD_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "download", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define ALARMCENTER_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "alarmcenter", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMCENTER_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "alarmcenter", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMCENTER_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "alarmcenter", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMCENTER_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "alarmcenter", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMCENTER_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "alarmcenter", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define ALARMCENTER_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "alarmcenter", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMCENTER_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "alarmcenter", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMCENTER_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "alarmcenter", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMCENTER_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "alarmcenter", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMCENTER_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "alarmcenter", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//设备对讲
#ifdef _WIN32
#define DevTalkVag_ERROR(fmt, ...)          hlog_format(HLOG_LEVEL_ERROR, "DevTalkVag", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DevTalkVag_WARN(fmt, ...)           hlog_format(HLOG_LEVEL_WARN, "DevTalkVag", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define DevTalkVag_INFO(fmt, ...)           hlog_format(HLOG_LEVEL_INFO, "DevTalkVag", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define DevTalkVag_DEBUG(fmt, ...)          hlog_format(HLOG_LEVEL_DEBUG, "DevTalkVag", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define DevTalkVag_TRACE(fmt, ...)          hlog_format(HLOG_LEVEL_TRACE, "DevTalkVag", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define DevTalkVag_ERROR(fmt, args...)      hlog_format(HLOG_LEVEL_ERROR, "DevTalkVag", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DevTalkVag_WARN(fmt, args...)       hlog_format(HLOG_LEVEL_WARN, "DevTalkVag", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DevTalkVag_INFO(fmt, args...)       hlog_format(HLOG_LEVEL_INFO, "DevTalkVag", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DevTalkVag_DEBUG(fmt, args...)      hlog_format(HLOG_LEVEL_DEBUG, "DevTalkVag", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DevTalkVag_TRACE(fmt, args...)      hlog_format(HLOG_LEVEL_TRACE, "DevTalkVag", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// 电视墙模块日志的宏定义
#if (defined _WIN32 || defined _WIN64)
#define TVWALL_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "tvwall", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define TVWALL_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "tvwall", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define TVWALL_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "tvwall", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define TVWALL_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "tvwall", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define TVWALL_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "tvwall", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define TVWALL_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "tvwall", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define TVWALL_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "tvwall", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define TVWALL_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "tvwall", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define TVWALL_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "tvwall", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define TVWALL_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "tvwall", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//智能人脸
#if (defined _WIN32 || defined _WIN64)
#define INTELLIFD_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "INTELLIFD", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define INTELLIFD_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "INTELLIFD", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define INTELLIFD_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "INTELLIFD", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define INTELLIFD_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "INTELLIFD", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define INTELLIFD_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "INTELLIFD", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define INTELLIFD_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "INTELLIFD", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define INTELLIFD_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "INTELLIFD", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define INTELLIFD_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "INTELLIFD", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define INTELLIFD_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "INTELLIFD", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define INTELLIFD_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "INTELLIFD", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//智能事件
#if (defined _WIN32 || defined _WIN64)
#define SMARTEVENT_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "SMARTEVENT", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SMARTEVENT_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "SMARTEVENT", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SMARTEVENT_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "SMARTEVENT", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SMARTEVENT_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "SMARTEVENT", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define SMARTEVENT_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "SMARTEVENT", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define SMARTEVENT_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "SMARTEVENT", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define SMARTEVENT_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "SMARTEVENT", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define SMARTEVENT_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "SMARTEVENT", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define SMARTEVENT_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "SMARTEVENT", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define SMARTEVENT_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "SMARTEVENT", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//KMSTOOL 
#if (defined _WIN32 || defined _WIN64)
#define KMSTOOL_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "KMSTOOL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define KMSTOOL_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "KMSTOOL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define KMSTOOL_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "KMSTOOL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define KMSTOOL_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "KMSTOOL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define KMSTOOL_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "KMSTOOL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define KMSTOOL_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "KMSTOOL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define KMSTOOL_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "KMSTOOL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define KMSTOOL_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "KMSTOOL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define KMSTOOL_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "KMSTOOL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define KMSTOOL_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "KMSTOOL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define PASSANGERFLOW_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "PASSANGERFLOW", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSANGERFLOW_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "PASSANGERFLOW", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSANGERFLOW_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "PASSANGERFLOW", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSANGERFLOW_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "PASSANGERFLOW", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSANGERFLOW_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "PASSANGERFLOW", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PASSANGERFLOW_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "PASSANGERFLOW", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSANGERFLOW_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "PASSANGERFLOW", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSANGERFLOW_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "PASSANGERFLOW", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSANGERFLOW_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "PASSANGERFLOW", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSANGERFLOW_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "PASSANGERFLOW", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//AlarmHost
#if (defined _WIN32 || defined _WIN64)
#define ALARMHOST_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "ALARMHOST", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMHOST_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "ALARMHOST", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMHOST_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "ALARMHOST", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMHOST_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "ALARMHOST", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ALARMHOST_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "ALARMHOST", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define ALARMHOST_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "ALARMHOST", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMHOST_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "ALARMHOST", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMHOST_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "ALARMHOST", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMHOST_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "ALARMHOST", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define ALARMHOST_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "ALARMHOST", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//DevIOCtrl
#if (defined _WIN32 || defined _WIN64)
#define DEVIOCTRL_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "DEVIOCTRL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEVIOCTRL_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "DEVIOCTRL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEVIOCTRL_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "DEVIOCTRL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEVIOCTRL_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "DEVIOCTRL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEVIOCTRL_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "DEVIOCTRL", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DEVIOCTRL_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "DEVIOCTRL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DEVIOCTRL_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "DEVIOCTRL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DEVIOCTRL_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "DEVIOCTRL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define DEVIOCTRL_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "DEVIOCTRL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define DEVIOCTRL_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "DEVIOCTRL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

//PassengerWebUI 
#if (defined _WIN32 || defined _WIN64)
#define PASSENGERWEBUI_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "PASSENGERWEBUI", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSENGERWEBUI_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "PASSENGERWEBUI", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSENGERWEBUI_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "PASSENGERWEBUI", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSENGERWEBUI_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "PASSENGERWEBUI", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PASSENGERWEBUI_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "PASSENGERWEBUI", "<[%d] - %s> <"fmt">", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PASSENGERWEBUI_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "PASSENGERWEBUI", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSENGERWEBUI_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "PASSENGERWEBUI", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSENGERWEBUI_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "PASSENGERWEBUI", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSENGERWEBUI_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "PASSENGERWEBUI", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PASSENGERWEBUI_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "PASSENGERWEBUI", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for WebPreviewCtrl
#if (defined _WIN32 || defined _WIN64)
#define WEBPREVIEWCTL_ERROR(fmt, ...)          hlog_format(HLOG_LEVEL_ERROR, "WEBPREVIEWCTL", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define WEBPREVIEWCTL_WARN(fmt, ...)           hlog_format(HLOG_LEVEL_WARN, "WEBPREVIEWCTL", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define WEBPREVIEWCTL_INFO(fmt, ...)           hlog_format(HLOG_LEVEL_INFO, "WEBPREVIEWCTL", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define WEBPREVIEWCTL_DEBUG(fmt, ...)          hlog_format(HLOG_LEVEL_DEBUG, "WEBPREVIEWCTL", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define WEBPREVIEWCTL_TRACE(fmt, ...)          hlog_format(HLOG_LEVEL_TRACE, "WEBPREVIEWCTL", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define WEBPREVIEWCTL_ERROR(fmt, args...)      hlog_format(HLOG_LEVEL_ERROR, "WEBPREVIEWCTL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define WEBPREVIEWCTL_WARN(fmt, args...)       hlog_format(HLOG_LEVEL_WARN, "WEBPREVIEWCTL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define WEBPREVIEWCTL_INFO(fmt, args...)       hlog_format(HLOG_LEVEL_INFO, "WEBPREVIEWCTL", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define WEBPREVIEWCTL_DEBUG(fmt, args...)      hlog_format(HLOG_LEVEL_DEBUG, "WEBPREVIEWCTL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define WEBPREVIEWCTL_TRACE(fmt, args...)      hlog_format(HLOG_LEVEL_TRACE, "WEBPREVIEWCTL", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#endif // _logger_H_


