/********************************************************************
	Copyright:  2012-2013 Hikvision Digital Technology Co.,  Ltd. 
	created:	2012/12/05
	filename: 	AlarmType
	file ext:	h
	author:		bianyu
	purpose:	报警类型添加
*********************************************************************/
#pragma once
using namespace std;
//报警类型的cms定义，64位。客户端这边为了操作方便，重新定义报警类型,定义为32位，
//方便报警定义的按位操作，高3个字节表示报警主类型，最后一个字节表示报警类型细分
//这样一共可以表示24种主类型报警，每种类型下可以表示256种细分报警

//报警类型客户端定义
namespace Alr_CCType
{
//报警主类型
    const UINT ALRCCTYPE_MAIN_CAMALR     = 0x00020000;  //监控点报警
    const UINT ALRCCTYPE_MAIN_IOALR      = 0x00090000;  //IO报警
    const UINT ALRCCTYPE_MAIN_ACALR      = 0x00030000;  //门禁报警
    const UINT ALRCCTYPE_MAIN_PATROL     = 0x00040000;  //巡查报警
    const UINT ALRCCTYPE_MAIN_ALRHOST    = 0x00050000;  //报警主机报警
    const UINT ALRCCTYPE_MAIN_FIRE       = 0x00060000;  //消防报警
    const UINT ALRCCTYPE_MAIN_DEALR      = 0x00070000;  //动环报警
    const UINT ALRCCTYPE_MAIN_PARK       = 0x00080000;  //停车场报警
    const UINT ALRCCTYPE_MAIN_EXCEPTION  = 0x00010000;  //异常报警
    const UINT ALRCCTYPE_MAIN_MANUAL     = 0x000A0000;  //手动报警

//报警子类型
    //监控点报警
    const UINT ALRCCTYPE_SUB_CAM_LOST         = 0x00020101;   //视频丢失
    const UINT ALRCCTYPE_SUB_CAM_COVER        = 0x00020102;   //视频遮挡
    const UINT ALRCCTYPE_SUB_CAM_MOVING       = 0x00020103;   //移动侦测
    const UINT ALRCCTYPE_SUB_CAM_CROSS        = 0x00020201;   //穿越警戒面
    const UINT ALRCCTYPE_SUB_CAM_ENTER        = 0x00020202;   //进入区域
    const UINT ALRCCTYPE_SUB_CAM_LEAVE        = 0x00020203;   //离开区域
    const UINT ALRCCTYPE_SUB_CAM_INVADE       = 0x00020204;   //区域入侵
    const UINT ALRCCTYPE_SUB_CAM_TAKEANDPLACE = 0x00020205;   //物品拿取放置
    const UINT ALRCCTYPE_SUB_CAM_LINGER       = 0x00020206;   //徘徊
    const UINT ALRCCTYPE_SUB_CAM_PARKING      = 0x00020207;   //停车
    const UINT ALRCCTYPE_SUB_CAM_FASTMOVE     = 0x00020208;   //快速移动
    const UINT ALRCCTYPE_SUB_CAM_GATHER       = 0x00020209;   //人员聚集
    const UINT ALRCCTYPE_SUB_CAM_LEFT         = 0x0002020A;   //物品遗留
    const UINT ALRCCTYPE_SUB_CAM_TAKE         = 0x0002020B;   //物品拿取 
    const UINT ALRCCTYPE_SUB_CAM_CHANGE       = 0x0002020C;   //场景突变

    //IO报警
    const UINT ALRCCTYPE_SUB_IO = 0x00090001;   

    //门禁报警
    const UINT ALRCCTYPE_SUB_AC_MULTI_CARD       = 0x00030101; //第一张主卡或副卡或双重卡
    const UINT ALRCCTYPE_SUB_AC_DOPEN_CARD       = 0x00030102; //在常开时区刷卡
    const UINT ALRCCTYPE_SUB_AC_TEMP_CARD        = 0x00030103; //临时卡
    const UINT ALRCCTYPE_SUB_AC_CUSTOMER_CARD    = 0x00030104; //来宾卡
    const UINT ALRCCTYPE_SUB_AC_TIME_CARD        = 0x00030105; //考勤卡
    const UINT ALRCCTYPE_SUB_AC_PATROL_CARD      = 0x00030106; //巡逻卡不开门
    const UINT ALRCCTYPE_SUB_AC_CC_CLOSE         = 0x00030107; //刷卡加密码关门
    const UINT ALRCCTYPE_SUB_AC_MASTER_CARD      = 0x00030108; //主卡
    const UINT ALARM_SUB_TYPE_DCLOSE_CARD        = 0x00030109; //常闭状态刷卡
    const UINT ALRCCTYPE_SUB_AC_WRONG_PWD        = 0x00030201; //密码错误
    const UINT ALRCCTYPE_SUB_AC_WRONG_CODE       = 0x00030202; //输入代码错误
    const UINT ALRCCTYPE_SUB_AC_NEED_CARD        = 0x00030203; //需要密码不能输入卡号
    const UINT ALRCCTYPE_SUB_AC_WRONG_AUTH       = 0x00030301; //权限不合
    const UINT ALRCCTYPE_SUB_AC_WHOL_AUTH        = 0x00030302; //假期权限不合
    const UINT ALRCCTYPE_SUB_AC_WMA_AUTH         = 0x00030303; //主副卡权限对比失败
    const UINT ALRCCTYPE_SUB_AC_WDURA_AUTH       = 0x00030304; //双重卡权限对比失败
    const UINT ALRCCTYPE_SUB_AC_WPATROL_AUTH     = 0x00030305; //巡逻卡权限不符
    const UINT ALRCCTYPE_SUB_AC_WCC_AUTH         = 0x00030306; //刷卡加代码权限不符
    const UINT ALRCCTYPE_SUB_AC_WANTI_AUTH       = 0x00030307; //ANTI比对失败
    const UINT ALRCCTYPE_SUB_AC_WTIME_AUTH       = 0x00030308; //时段组错误
    const UINT ALRCCTYPE_SUB_AC_CARD_OUTTIME     = 0x00030401; //卡号时效已过
    const UINT ALRCCTYPE_SUB_AC_CARD_NOTEXIST    = 0x00030402; //无此卡号
    const UINT ALRCCTYPE_SUB_AC_BLACK_LIST       = 0x00030501; //黑名单
    const UINT ALRCCTYPE_SUB_AC_CC_NOPEN         = 0x00030601; //刷卡加代码不开门
    const UINT ALRCCTYPE_SUB_AC_DLOCK_NOPEN      = 0x00030602; //双门互锁中无法开门
    const UINT ALRCCTYPE_SUB_AC_FAIL_LOGIN       = 0x00030603; //有卡片但无法login 成功
    const UINT ALRCCTYPE_SUB_AC_OPEN_OUTOFTIME   = 0x00030700; //开门超时
    const UINT ALRCCTYPE_SUB_AC_ILLEAGAL_OPENGATE= 0x00030801; //非法开门
    const UINT ALRCCTYPE_SUB_AC_GATE_OPEN        = 0x00030901; //开门
    const UINT ALRCCTYPE_SUB_AC_CARD_OPEN        = 0x00030902; //刷卡开门
    const UINT ALRCCTYPE_SUB_AC_CC_OPEN          = 0x00030903; //刷卡加代码开门
    const UINT ALRCCTYPE_SUB_AC_HARD_OPEN        = 0x00030904; //按钮开门
    const UINT ALRCCTYPE_SUB_AC_PATROL_OPEN      = 0x00030906; //巡逻卡开门
    const UINT ALRCCTYPE_SUB_AC_SOFT_OPEN        = 0x00030907; //远程软件开门
    const UINT ALRCCTYPE_SUB_AC_NORMAL_CLOSEGATE = 0x00030A01; //关门
    const UINT ALRCCTYPE_SUB_AC_FORCE_CARD       = 0x00030B01; //胁迫卡
    const UINT ALRCCTYPE_SUB_AC_FORCE_CODE       = 0x00030B02; //胁迫码
    const UINT ALRCCTYPE_SUB_AC_SECRET_ALARM     = 0x00030B03; //门秘密警报
    const UINT ALRCCTYPE_SUB_AC_FORCE_INOUT      = 0x00030B04; //胁迫开门报警
    const UINT ALRCCTYPE_SUB_AC_RELEASE_ARM      = 0x00030C01; //解除警报

    //巡查报警
    const UINT ALRCCTYPE_SUB_PATROL_EARLY    = 0x00040001;  //早巡
    const UINT ALRCCTYPE_SUB_PATROL_LATE     = 0x00040002;  //晚巡
    const UINT ALRCCTYPE_SUB_PATROL_MISSING  = 0x00040003;  //漏巡

    //报警主机防区
    const UINT ALRCCTYPE_SUB_ARLHOST_AREA    = 0x00050001;  //报警主机防区报警

    //消防报警
    const UINT ALRCCTYPE_SUB_FIRE_FIREALR    = 0x00060001;  //消防报警

    //动环报警
    const UINT ALRCCTYPE_SUB_DE_ENV          = 0x00070101;  //环境量报警

    //停车场报警    
    const UINT ALRCCTYPE_SUB_PARK_ILLCAR     = 0x00080001;  //非法车辆
    const UINT ALRCCTYPE_SUB_PARK_BLACKLIST  = 0x00080002;  //黑名单
    const UINT ALRCCTYPE_SUB_PARK_OWE        = 0x00080003;  //欠费

    //异常报警
    const UINT ALRCCTYPE_SUB_EPT_SVREPT      = 0x00010101;  //服务器异常
    const UINT ALRCCTYPE_SUB_EPT_SVROFFLINE  = 0x00010102;  //服务器掉线
    const UINT ALRCCTYPE_SUB_EPT_DEVOFFLINE  = 0x00010201;  //设备掉线
    const UINT ALRCCTYPE_SUB_EPT_DEVDISFULL  = 0x00010202;  //硬盘满
    const UINT ALRCCTYPE_SUB_EPT_DEVEXPT     = 0x00010203;  //设备异常
    const UINT ALRCCTYPE_SUB_EPT_DESTROY     = 0x00010301; //外力破坏
    const UINT ALRCCTYPE_SUB_EPT_OFFLINE     = 0x00010302; //装置离线
    const UINT ALRCCTYPE_SUB_EPT_BOOT        = 0x00010303; //冷开机
    const UINT ALRCCTYPE_SUB_EPT_REBOOT      = 0x00010304; //重新启动
    const UINT ALRCCTYPE_SUB_EPT_MEMORY_FULL = 0x00010305; //记忆体已满
    const UINT ALRCCTYPE_SUB_EPT_INIT        = 0x00010306; //系统初始化

    const UINT ALRCCTYPE_SUB_EPT_MANUAL      = 0x000A0001;  //手动报警
}


//服务器
const CString ALRNAME_SVR_EXPT      = _T("服务器异常");
const CString ALRNAME_SVR_OFFLINE   = _T("服务器掉线");

//设备
const CString ALRNAME_DEV_OFFLINE   = _T("设备掉线");
const CString ALRNAME_DEV_DISFULL   = _T("设备硬盘满");
const CString ALRNAME_DEV_EXPT      = _T("设备异常");

//门禁 
const CString ALRNAME_DEV_AC_DESTROY     = _T("外力破坏");
const CString ALRNAME_DEV_AC_OFFLINE     = _T("装置离线");
const CString ALRNAME_DEV_AC_BOOT        = _T("冷开机");
const CString ALRNAME_DEV_AC_REBOOT      = _T("重新启动");
const CString ALRNAME_DEV_AC_MEMORY_FULL = _T("记忆体已满");
const CString ALRNAME_DEV_AC_INIT        = _T("系统初始化");

//监控点
const CString ALRNAME_CAM_LOST         = _T("视频丢失报警");
const CString ALRNAME_CAM_COVER        = _T("视频遮挡报警");
const CString ALRNAME_CAM_MOVING       = _T("移动侦测报警");
const CString ALRNAME_CAM_CROSS        = _T("穿越警戒面");
const CString ALRNAME_CAM_ENTER        = _T("进入区域");
const CString ALRNAME_CAM_LEAVE        = _T("离开区域");
const CString ALRNAME_CAM_INVADE       = _T("区域入侵");
const CString ALRNAME_CAM_TAKEANDPLACE = _T("物品拿取放置");
const CString ALRNAME_CAM_LINGER       = _T("徘徊");
const CString ALRNAME_CAM_PARKING      = _T("停车");
const CString ALRNAME_CAM_FASTMOVE     = _T("快速移动");
const CString ALRNAME_CAM_GATHER       = _T("人员聚集");
const CString ALRNAME_CAM_LEFT         = _T("物品遗留");
const CString ALRNAME_CAM_TAKE         = _T("物品拿取");
const CString ALRNAME_CAM_CHANGE       = _T("场景突变");
//IO
const CString ALRNAME_IO_IOINALR       = _T("IO输入报警");

//门禁
const CString ALRNAME_AC_MULTI_CARD       = _T("第一张主卡或副卡或双重卡");
const CString ALRNAME_AC_DOPEN_CARD       = _T("在常开时区刷卡");
const CString ALRNAME_AC_TEMP_CARD        = _T("临时卡");
const CString ALRNAME_AC_CUSTOMER_CARD    = _T("来宾卡");
const CString ALRNAME_AC_TIME_CARD        = _T("考勤卡");
const CString ALRNAME_AC_PATROL_CARD      = _T("巡逻卡不开门");
const CString ALRNAME_AC_CC_CLOSE         = _T("刷卡加密码关门");
const CString ALRNAME_AC_MASTER_CARD      = _T("主卡");
const CString ALRNAME_AC_DCLOSE_CARD      = _T("常闭状态刷卡");
const CString ALRNAME_AC_WRONG_PWD        = _T("密码错误");
const CString ALRNAME_AC_WRONG_CODE       = _T("输入代码错误");
const CString ALRNAME_AC_NEED_CARD        = _T("需要密码不能输入卡号");
const CString ALRNAME_AC_WRONG_AUTH       = _T("权限不合");
const CString ALRNAME_AC_WHOL_AUTH        = _T("假期权限不合");
const CString ALRNAME_AC_WMA_AUTH         = _T("主副卡权限对比失败");
const CString ALRNAME_AC_WDURA_AUTH       = _T("双重卡权限对比失败");
const CString ALRNAME_AC_WPATROL_AUTH     = _T("巡逻卡权限不符");
const CString ALRNAME_AC_WCC_AUTH         = _T("刷卡加代码权限不符");
const CString ALRNAME_AC_WANTI_AUTH       = _T("ANTI比对失败");
const CString ALRNAME_AC_WTIME_AUTH       = _T("时段组错误");
const CString ALRNAME_AC_CARD_OUTTIME     = _T("卡号时效已过");
const CString ALRNAME_AC_CARD_NOTEXIST    = _T("无此卡号");
const CString ALRNAME_AC_BLACK_LIST       = _T("黑名单");
const CString ALRNAME_AC_CC_NOPEN         = _T("刷卡加代码不开门");
const CString ALRNAME_AC_DLOCK_NOPEN      = _T("双门互锁中无法开门");
const CString ALRNAME_AC_FAIL_LOGIN       = _T("无法登陆");
const CString ALRNAME_AC_OPEN_OUTOFTIME   = _T("门持续开启");
const CString ALRNAME_AC_ILLEAGAL_OPENGATE= _T("门被外力开启");
const CString ALRNAME_AC_GATE_OPEN        = _T("开门");
const CString ALRNAME_AC_CARD_OPEN        = _T("刷卡开门");
const CString ALRNAME_AC_CC_OPEN          = _T("刷卡加代码开门");
const CString ALRNAME_AC_HARD_OPEN        = _T("按钮开门");
const CString ALRNAME_AC_PATROL_OPEN      = _T("巡逻卡开门");
const CString ALRNAME_AC_SOFT_OPEN        = _T("远程软件开门");
const CString ALRNAME_AC_NORMAL_CLOSEGATE = _T("关门");
const CString ALRNAME_AC_FORCE_CARD       = _T("胁迫卡");
const CString ALRNAME_AC_FORCE_CODE       = _T("胁迫码");
const CString ALRNAME_AC_SECRET_ALARM     = _T("门秘密警报");
const CString ALRNAME_AC_FORCE_INOUT      = _T("胁迫开门报警");
const CString ALRNAME_AC_RELEASE_ARM      = _T("解除警报");



//巡查报警
const CString ALRNAME_PATROL_EARLY    = _T("早巡");
const CString ALRNAME_PATROL_LATE     = _T("晚巡");
const CString ALRNAME_PATROL_MISSING  = _T("漏巡");

//报警主机防区
const CString ALRNAME_ARLHOST_AREA    = _T("防区报警");

//消防报警
const CString ALRNAME_FIRE_FIREALR    = _T("消防报警");

//动环报警
const CString ALRNAME_DE_ENV          = _T("环境量报警");

//停车场报警    
const CString ALRNAME_PARK_ILLCAR     = _T("非法车辆");
const CString ALRNAME_PARK_BLACKLIST  = _T("黑名单");
const CString ALRNAME_PARK_OWE        = _T("欠费");

const CString ALRNAME_MANUAL     = _T("手动报警");

typedef struct stu_AlarmInputInfo 
{
    UINT uAlrCCMainType;     //客户端定义报警类型 主类型
    UINT uAlrCCSubType;      //客户端定义报警类型 类型细分
    CString strName;      //报警类型名称

	stu_AlarmInputInfo()
	{
        uAlrCCMainType = 0;
        uAlrCCSubType = 0;

    }

	stu_AlarmInputInfo(UINT uParamCCMainType,UINT uParamCCSubType,CString strParamName)
	{
        uAlrCCMainType = uParamCCMainType;
        uAlrCCSubType = uParamCCSubType;
        strName = strParamName;
	}

}ALARMINPUTINFO ,*PALARMINPUTINFO;

class AlarmType
{
public:
    AlarmType(void);
    /*virtual */~AlarmType(void);
private:

	map<UINT , PALARMINPUTINFO>m_mapAlarmInputInfo;
    static AlarmType* m_pAlarmTypeInstance;

public:
    static AlarmType*  GetInstance();
    static void DeleteInstance();

private: 
/*******************************************************************************
*    Function:      __InitAlrType
*    Description:   初始化报警类型表
*    Input:         
*    Output:         
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
    void __InitAlrType();

/*******************************************************************************
*    Function:      __UnInitAlrType
*    Description:   释放报警类型表的空间
*    Input:          
*    Output:         
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
    void __UnInitAlrType();

public:
/*******************************************************************************
*    Function:      AlrType_GetTypeNameByTypeID
*    Description:   根据报警的类型ID获取类型名称
*    Input:         uTypeID -- 报警类型ID(CC定义的类型)
*    Output:        strName -- 报警类型名称
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
    void AlrType_GetTypeNameByTypeID(CString &strName,UINT uTypeID);
};
