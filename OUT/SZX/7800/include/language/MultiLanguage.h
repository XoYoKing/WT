#pragma once
#include <string>

#ifdef MULTILANGUAGE_EXPORTS  
#define PREDLL_API __declspec(dllexport)  
#else  
#define PREDLL_API __declspec(dllimport)  
#endif  

/** @fn     Init_MultiLanguage
 *  @brief  ���ģ���µ��ã������ļ��ֲ��ڲ�ͬ�ļ���
 *  @param  void
 *  @return void
 */
PREDLL_API void Init_MultiLanguage();

/** @fn     Fnit_MultiLanguage
 *  @brief  ���ģ���µ��ã������ļ��ֲ��ڲ�ͬ�ļ���
 *  @param  void
 *  @return void
 */
PREDLL_API void Fnit_MultiLanguage();

/** @fn      CreateLanguagePort
 *  @brief   ���ģ���µ��ã������ļ��ֲ��ڲ�ͬ�ļ���
 *  @param   strLan:�ļ�·��
 *  @return  ���ض˿�
 */
PREDLL_API int CreateLanguagePort(const char* strLan);

/** @fn      FreeLanguagePort
*  @brief   ���ģ���µ��ã������ļ��ֲ��ڲ�ͬ�ļ��ڣ��ͷŶ˿�
*  @param   nPort:�˿ں�
*  @return  void
*/
PREDLL_API void FreeLanguagePort(int nPort);

/** @fn     MultiLanguage_GetValueEx
 *  @brief  ���ģ���µ��ã���ȡXML����
 *  @param  nPort:�˿ں�
 *          strKey:��ֵ
 *  @return ����ֵ
 */
PREDLL_API std::string MultiLanguage_GetValueEx(int nPort, const char* strKey);

PREDLL_API std::string MultiLanguage_GetValue(const char* strKey);

PREDLL_API bool MultiLanguage_GetValue_C(const char* strKey, char* result, unsigned int len);

PREDLL_API void MultiLanguage_Change(const char* strLan);

PREDLL_API void SetDefaultLanguage(const char* strLan);



