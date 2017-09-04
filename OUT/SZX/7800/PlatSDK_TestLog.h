#ifndef __PLAT_SDK_TEST_H__
#define __PLAT_SDK_TEST_H__
#include "hLog.h"

// for VRM
#if (defined _WIN32 || defined _WIN64)
#define PLAT_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "Plat", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define PLAT_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "Plat", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define PLAT_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "Plat", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define PLAT_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "Plat", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#define PLAT_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "Plat", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
#define PLAT_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "VRM", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAT_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "VRM", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAT_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "VRM", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAT_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "VRM", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define PLAT_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "VRM", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#endif