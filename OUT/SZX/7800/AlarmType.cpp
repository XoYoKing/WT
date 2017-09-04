/********************************************************************
	Copyright:  2012-2013 Hikvision Digital Technology Co.,  Ltd. 
	created:	2012/12/05
	filename: 	AlarmType
	file ext:	cpp
	author:		bianyu
	purpose:	报警类型添加
*********************************************************************/

#include "StdAfx.h"
#include "AlarmType.h"
using namespace Alr_CCType;

AlarmType* AlarmType::m_pAlarmTypeInstance = NULL;

AlarmType::AlarmType(void)
{
    __InitAlrType();
}

AlarmType::~AlarmType(void)
{
    try
    {
        __UnInitAlrType();        
    }
    catch(...)
    {
        //
    }
}

AlarmType*  AlarmType::GetInstance()
{
    if(m_pAlarmTypeInstance == NULL)
    {
        try
        {
            m_pAlarmTypeInstance = new AlarmType;
        }
        catch(...)
        {
            m_pAlarmTypeInstance = NULL;
        }
    }

    return m_pAlarmTypeInstance;
}

void AlarmType::DeleteInstance()
{
    delete m_pAlarmTypeInstance;
}

/*******************************************************************************
*    Function:      __InitAlrType
*    Description:   初始化报警类型表
*    Input:         
*    Output:         
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
void AlarmType::__InitAlrType()
{
    PALARMINPUTINFO pTmp = NULL;
    //异常报警

    //服务器异常
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_SVREPT,ALRNAME_SVR_EXPT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_SVREPT,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_SVROFFLINE,ALRNAME_SVR_OFFLINE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_SVROFFLINE,pTmp));
    }

    //设备异常
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_DEVOFFLINE,ALRNAME_DEV_OFFLINE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_DEVOFFLINE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_DEVDISFULL,ALRNAME_DEV_DISFULL);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_DEVDISFULL,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_DEVEXPT,ALRNAME_DEV_EXPT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_DEVEXPT,pTmp));
    }

    //门禁异常
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_DESTROY,ALRNAME_DEV_AC_DESTROY);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_DESTROY,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_OFFLINE,ALRNAME_DEV_AC_OFFLINE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_OFFLINE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_BOOT,ALRNAME_DEV_AC_BOOT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_BOOT,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_REBOOT,ALRNAME_DEV_AC_REBOOT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_REBOOT,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_MEMORY_FULL,ALRNAME_DEV_AC_MEMORY_FULL);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_MEMORY_FULL,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_EXCEPTION,ALRCCTYPE_SUB_EPT_INIT,ALRNAME_DEV_AC_INIT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_INIT,pTmp));
    }


    //监控点报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_LOST,ALRNAME_CAM_LOST);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_LOST,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_COVER,ALRNAME_CAM_COVER);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_COVER,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_MOVING,ALRNAME_CAM_MOVING);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_MOVING,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_CROSS,ALRNAME_CAM_CROSS);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_CROSS,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_ENTER,ALRNAME_CAM_ENTER);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_ENTER,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_LEAVE,ALRNAME_CAM_LEAVE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_LEAVE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_INVADE,ALRNAME_CAM_INVADE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_INVADE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_TAKEANDPLACE,ALRNAME_CAM_TAKEANDPLACE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_TAKEANDPLACE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_LINGER,ALRNAME_CAM_LINGER);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_LINGER,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_PARKING,ALRNAME_CAM_PARKING);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_PARKING,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_FASTMOVE,ALRNAME_CAM_FASTMOVE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_FASTMOVE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_GATHER,ALRNAME_CAM_GATHER);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_GATHER,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_LEFT,ALRNAME_CAM_LEFT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_LEFT,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_TAKE,ALRNAME_CAM_TAKE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_TAKE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_CAMALR,ALRCCTYPE_SUB_CAM_CHANGE,ALRNAME_CAM_CHANGE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_CAM_CHANGE,pTmp));
    }

    //IO报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_IOALR,ALRCCTYPE_SUB_IO,ALRNAME_IO_IOINALR);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_IO,pTmp));
    }

    //门禁类报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_MULTI_CARD,ALRNAME_AC_MULTI_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_MULTI_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_DOPEN_CARD,ALRNAME_AC_DOPEN_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_DOPEN_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_TEMP_CARD,ALRNAME_AC_TEMP_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_TEMP_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CUSTOMER_CARD,ALRNAME_AC_CUSTOMER_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CUSTOMER_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_TIME_CARD,ALRNAME_AC_TIME_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_TIME_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_PATROL_CARD,ALRNAME_AC_PATROL_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_PATROL_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CC_CLOSE,ALRNAME_AC_MASTER_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CC_CLOSE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_MASTER_CARD,ALRNAME_AC_MASTER_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_MASTER_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALARM_SUB_TYPE_DCLOSE_CARD,ALRNAME_AC_DCLOSE_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALARM_SUB_TYPE_DCLOSE_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WRONG_PWD,ALRNAME_AC_WRONG_PWD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WRONG_PWD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WRONG_CODE,ALRNAME_AC_WRONG_CODE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WRONG_CODE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_NEED_CARD,ALRNAME_AC_NEED_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_NEED_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WRONG_AUTH,ALRNAME_AC_WRONG_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WRONG_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WHOL_AUTH,ALRNAME_AC_WHOL_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WHOL_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WMA_AUTH,ALRNAME_AC_WMA_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WMA_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WDURA_AUTH,ALRNAME_AC_WDURA_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WDURA_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WPATROL_AUTH,ALRNAME_AC_WPATROL_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WPATROL_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WCC_AUTH,ALRNAME_AC_WCC_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WCC_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WANTI_AUTH,ALRNAME_AC_WANTI_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WANTI_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_WTIME_AUTH,ALRNAME_AC_WTIME_AUTH);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_WTIME_AUTH,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CARD_OUTTIME,ALRNAME_AC_CARD_OUTTIME);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CARD_OUTTIME,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CARD_NOTEXIST,ALRNAME_AC_CARD_NOTEXIST);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CARD_NOTEXIST,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_BLACK_LIST,ALRNAME_AC_BLACK_LIST);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_BLACK_LIST,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CC_NOPEN,ALRNAME_AC_CC_NOPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CC_NOPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_DLOCK_NOPEN,ALRNAME_AC_DLOCK_NOPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_DLOCK_NOPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_FAIL_LOGIN,ALRNAME_AC_FAIL_LOGIN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_FAIL_LOGIN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_OPEN_OUTOFTIME,ALRNAME_AC_OPEN_OUTOFTIME);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_OPEN_OUTOFTIME,pTmp));
    }
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_ILLEAGAL_OPENGATE,ALRNAME_AC_ILLEAGAL_OPENGATE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_ILLEAGAL_OPENGATE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_GATE_OPEN,ALRNAME_AC_GATE_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_GATE_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CARD_OPEN,ALRNAME_AC_CARD_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CARD_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_CC_OPEN,ALRNAME_AC_CC_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_CC_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_HARD_OPEN,ALRNAME_AC_HARD_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_HARD_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_PATROL_OPEN,ALRNAME_AC_PATROL_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_PATROL_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_SOFT_OPEN,ALRNAME_AC_SOFT_OPEN);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_SOFT_OPEN,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_NORMAL_CLOSEGATE,ALRNAME_AC_NORMAL_CLOSEGATE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_NORMAL_CLOSEGATE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_FORCE_CARD,ALRNAME_AC_FORCE_CARD);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_FORCE_CARD,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_FORCE_CODE,ALRNAME_AC_FORCE_CODE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_FORCE_CODE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_SECRET_ALARM,ALRNAME_AC_SECRET_ALARM);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_SECRET_ALARM,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_SECRET_ALARM,ALRNAME_AC_FORCE_INOUT);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_FORCE_INOUT,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ACALR,ALRCCTYPE_SUB_AC_SECRET_ALARM,ALRNAME_AC_RELEASE_ARM);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_AC_RELEASE_ARM,pTmp));
    }


    //巡查类报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PATROL,ALRCCTYPE_SUB_PATROL_EARLY,ALRNAME_PATROL_EARLY);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PATROL_EARLY,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PATROL,ALRCCTYPE_SUB_PATROL_LATE,ALRNAME_PATROL_LATE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PATROL_LATE,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PATROL,ALRCCTYPE_SUB_PATROL_MISSING,ALRNAME_PATROL_MISSING);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PATROL_MISSING,pTmp));
    }

    //报警主机报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_ALRHOST,ALRCCTYPE_SUB_ARLHOST_AREA,ALRNAME_ARLHOST_AREA);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_ARLHOST_AREA,pTmp));
    }

    //消防报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_FIRE,ALRCCTYPE_SUB_FIRE_FIREALR,ALRNAME_FIRE_FIREALR);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_FIRE_FIREALR,pTmp));
    }

    //动环报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_DEALR,ALRCCTYPE_SUB_DE_ENV,ALRNAME_DE_ENV);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_DE_ENV,pTmp));
    }


    //停车场报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PARK,ALRCCTYPE_SUB_PARK_ILLCAR,ALRNAME_PARK_ILLCAR);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PARK_ILLCAR,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PARK,ALRCCTYPE_SUB_PARK_BLACKLIST,ALRNAME_PARK_BLACKLIST);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PARK_BLACKLIST,pTmp));
    }

    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_PARK,ALRCCTYPE_SUB_PARK_OWE,ALRNAME_PARK_OWE);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_PARK_OWE,pTmp));
    }

    //手动报警
    pTmp = new (std::nothrow)ALARMINPUTINFO(ALRCCTYPE_MAIN_MANUAL,ALRCCTYPE_SUB_EPT_MANUAL,ALRNAME_MANUAL);
    if (pTmp != NULL)
    {
        m_mapAlarmInputInfo.insert(std::make_pair(ALRCCTYPE_SUB_EPT_MANUAL,pTmp));
    }

}

/*******************************************************************************
*    Function:      __UnInitAlrType
*    Description:   释放报警类型表的空间
*    Input:          
*    Output:         
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
void AlarmType::__UnInitAlrType()
{
    std::map<UINT,PALARMINPUTINFO>::iterator it_AlrIpt = m_mapAlarmInputInfo.begin();
    while(it_AlrIpt != m_mapAlarmInputInfo.end())
    {
        delete it_AlrIpt->second;
        ++it_AlrIpt;
    }

    m_mapAlarmInputInfo.clear();
}

/*******************************************************************************
*    Function:      AlrType_GetTypeNameByTypeID
*    Description:   根据报警的类型ID获取类型名称
*    Input:         iTypeID -- 报警类型ID
*    Output:        strName -- 报警类型名称
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
void AlarmType::AlrType_GetTypeNameByTypeID(CString &strName,UINT iTypeID)
{
    std::map<UINT , PALARMINPUTINFO>::iterator it_AlrInpt = m_mapAlarmInputInfo.find(iTypeID);
    if (it_AlrInpt != m_mapAlarmInputInfo.end() && it_AlrInpt->second != NULL)
    {
        strName = it_AlrInpt->second->strName;
    }
}

