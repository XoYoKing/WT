#pragma once
#include <string>

#ifdef MULTILANGUAGE_EXPORTS  
#define PREDLL_API __declspec(dllexport)  
#else  
#define PREDLL_API __declspec(dllimport)  
#endif  

/** @fn     Init_MultiLanguage
 *  @brief  多个模块下调用，语言文件分布在不同文件内
 *  @param  void
 *  @return void
 */
PREDLL_API void Init_MultiLanguage();

/** @fn     Fnit_MultiLanguage
 *  @brief  多个模块下调用，语言文件分布在不同文件内
 *  @param  void
 *  @return void
 */
PREDLL_API void Fnit_MultiLanguage();

/** @fn      CreateLanguagePort
 *  @brief   多个模块下调用，语言文件分布在不同文件内
 *  @param   strLan:文件路径
 *  @return  返回端口
 */
PREDLL_API int CreateLanguagePort(const char* strLan);

/** @fn      FreeLanguagePort
*  @brief   多个模块下调用，语言文件分布在不同文件内，释放端口
*  @param   nPort:端口号
*  @return  void
*/
PREDLL_API void FreeLanguagePort(int nPort);

/** @fn     MultiLanguage_GetValueEx
 *  @brief  多个模块下调用，读取XML内容
 *  @param  nPort:端口号
 *          strKey:键值
 *  @return 返回值
 */
PREDLL_API std::string MultiLanguage_GetValueEx(int nPort, const char* strKey);

PREDLL_API std::string MultiLanguage_GetValue(const char* strKey);

PREDLL_API bool MultiLanguage_GetValue_C(const char* strKey, char* result, unsigned int len);

PREDLL_API void MultiLanguage_Change(const char* strLan);

PREDLL_API void SetDefaultLanguage(const char* strLan);



