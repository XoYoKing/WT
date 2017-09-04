/** @file hlog.h
 *  @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief ������־���ģ��
 *
 *  @author     ������
 *  @date       2010/06/28
 */
#ifndef __HLOG_H__
#define __HLOG_H__

#if (defined _WIN32 || defined _WIN64)
#   ifdef HLOG_EXPORTS
#       define HLOG_DECLARE extern "C" __declspec(dllexport)
#   else
#       define HLOG_DECLARE extern "C" __declspec(dllimport)
#   endif
#   define HLOG_API __stdcall
#else
#   ifdef __linux__
#       define HLOG_DECLARE extern "C"
#   else
#       define HLOG_DECLARE
#   endif
#   define HLOG_API
#endif

/** @enum HLOG_LEVEL
 *  @brief ��־����
 */
typedef enum {
    HLOG_LEVEL_OFF    = 7,
    HLOG_LEVEL_FATAL  = 6,
    HLOG_LEVEL_ERROR  = 5,
    HLOG_LEVEL_WARN   = 4,
    HLOG_LEVEL_INFO   = 3,
    HLOG_LEVEL_DEBUG  = 2,
    HLOG_LEVEL_TRACE  = 1,
    HLOG_LEVEL_ALL    = 0
} HLOG_LEVEL;

#ifdef __GNUC__
#define LOG_CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#define CALLBACK
#else
#define LOG_CHECK_FMT(a, b)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn void hlog_init(const char* name, bool async = false)
    *   @brief ��־��Ϣ��ʼ��
    *   @param name ���ƣ���־�ļ���ǰ׺�������ļ�xxx.log4cxx��xxx���֣�Ҳ������log4cxx.properties��log4cxx.xml
    *   @param async �Ƿ������첽д��־����
    */
    HLOG_DECLARE void HLOG_API hlog_init(const char* name, bool async = false);

    /** @fn void hlog_ocx_init(const char* name, const char* path, bool async = false)
    *   @brief ��־��Ϣ��ʼ��
    *   @param name ���ƣ���־�ļ���ǰ׺�������ļ�xxx.log4cxx��xxx���֣�Ҳ������log4cxx.properties��log4cxx.xml
    *   @param path �����ļ�·��,path��󲻱ؼ�"/"
    *   @param async �Ƿ������첽д��־����
    */
    HLOG_DECLARE void HLOG_API hlog_ocx_init(const char* name, const char* path, bool async = false);

    /** @fn void hlog_fini()
    *   @brief ��־ϵͳ����ʼ��
    */
    HLOG_DECLARE void HLOG_API hlog_fini();

    /** @fn void hlog_set_callback(HLOG_CB callback)
    *   @brief ������־�Ļص�����
    *   @param callback ���ڴ�����־��Ϣ�Ļص�����
    */
    HLOG_DECLARE void HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn void hlog_level(HLOG_LEVEL level)
    *   @brief ������־���������
    *   @param level ��־����
    */
    HLOG_DECLARE void HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn void hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
    *   @brief д��־��ʽ������
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param format ��־��ʽ���ַ�������ӿɱ����
    *   @note hlog_format�����hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE void HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn void hlog_message(HLOG_LEVEL level, const char* module, const char* message)
    *   @brief д��־�ַ���
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param message ��־�ַ���
    *   @note hlog_message�������hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE void HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

#ifdef __cplusplus
}
#endif

// ���Ǽ����ԣ�������log_printf_def��log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for defualt module
#if (defined _WIN32 || defined _WIN64)
    #define LOG_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define LOG_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define LOG_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for HPP module
#if (defined _WIN32 || defined _WIN64)
    #define HPP_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define HPP_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "HPP", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "HPP", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define HPP_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for MQ module
#if (defined _WIN32 || defined _WIN64)
    #define MQ_ERROR(fmt, ...)          hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define MQ_WARN(fmt, ...)           hlog_format(HLOG_LEVEL_WARN, "MQ", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_INFO(fmt, ...)           hlog_format(HLOG_LEVEL_INFO, "MQ", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_DEBUG(fmt, ...)          hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_TRACE(fmt, ...)          hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%s [%d] - %s> <"fmt">",  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define MQ_ERROR(fmt, args...)      hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_WARN(fmt, args...)       hlog_format(HLOG_LEVEL_WARN, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_INFO(fmt, args...)       hlog_format(HLOG_LEVEL_INFO, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_DEBUG(fmt, args...)      hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_TRACE(fmt, args...)      hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#endif // __HLOG_H__
