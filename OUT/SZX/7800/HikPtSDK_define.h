#ifndef __HIKPTSDK_DEFINE_H__
#define __HIKPTSDK_DEFINE_H__

#include <string>
#include<windows.h>

#ifdef __cplusplus
extern "C" {
#endif  //#ifdef __cplusplus


//用户登录信息
typedef struct tagHikLoginInfo
{
    char    szUserName[64];         // 登录名称
    char    szPassword[64];         // 密码
    char    szServerUrl[64];        // CMS服务地址
    unsigned int uServerPort;       // 服务器端口
    int     nErrCode;               // 登入失败错误码
    char    szErrInfo[512];         // 登入失败错误详情
}HikLoginInfo;

//中心
typedef struct tagCellInfo
{
    int     nId;                    // 中心ID
    int     nParentId;              // 父节点ID
    char    szIndexCode[64];        // 索引编号
    char    szCellName[130];        // 中心名称
    char	szRegCode[40];			// 组织编号
    int     nSeqIndex;              // 展示排列序号
    char	szCascCode[40];			// 级联标识，级联平台的编码
    char 	szPinyin[40];		    // 拼音首字节
    bool    bPrivilege;             // 是否有权限
    tagCellInfo* pNext;
}HikCellInfo;

//用户组织
typedef struct tagHikUserOrg
{
    char szOrgName[130]; // 用户组织名称
    char szOrgIndex[64]; // 用户组织indexcode
    int  nParentID;      // 上级ID
    int  nID;            // 用户组织ID
    int  nSeqIndex;      // 排序序号
    bool bPrivilege;     // 是否有权限
    tagHikUserOrg* pNext;       
}HikUserOrg;

//用户信息
typedef struct tagHikPlatformUser
{
    int nId;          // 用户ID
    char szName[130]; // 用户名称
    char szLoginName[130];//登录名称
    int nLevel;       // 用户级别，管理员: 50
    int nStatus;      // 用户状态  正常，过期，禁用等，实际使用过程只需要正常状态。
    int nCellID;      // 所属组织ID
    tagHikPlatformUser* pNext;
}HikPlatformUser;   

//监控点信息
typedef struct tagHikCameraInfo
{
    int nCamId;        //监控点ID
    int nCellId;       //所属组织架构
    int nChannel;       //通道号
    char szDevIndexCode[64];  //所属设备编号
    char szIndexCode[64];  //编号
    char szCameraName[260]; //名称
    int nCameraType;        //摄像机类型枪机、半球等
    char szMatrixCode[64]; //键盘编码
    int nSeqIndex;      // 展示排列序号
    bool bOnlineStatus;  //在线状态
    int nInstallType;   // 安装方式
    int nVideoDevType;  // 机型 标清网络半球  16鱼眼
    char szCascCode[40];				   //级联标识，级联平台的编码
    char szCascDecodeTag[32];              //级联解码标志 hikvision,dahua,db33
    int nPlayParam;	//播放性能参数
    int nSubStream;	//初始码流格式，0~主码流，1~子码流
    int nProtocal;	//传输协议，TCP or UDP
    int nPassage;   //客流属性  1入口，2出口，3出入口
    bool bEzviz;    //是否为萤石云监控点
    tagHikCameraInfo* pNext;
}HikCameraInfo;

//设备信息
typedef struct tagHikDeviceInfo
{
    int nDevId;             //设备ID
    char szDevName[260];    //设备名称
    char szIndexCode[64];   //设备编号
    char szIp[32];          //设备IP
    unsigned int uPort;     //设备端口
    char szUserName[130];   //用户名
    char szPassword[64];    //密码
    int nDevType;           //设备类型，0~海康，1~大华
    int nDomainId;          //设备网域DI
	int nProSeries;	        //产品系列
    int nOrgId;             //组织ID
    char szOrgName[130];    //组织名称
    /*接入协议（全大写）：
    现在有HIKSDK(海康设备)  DAHUASDK（大华设备）  EHOME（EHOME设备）  GB28181(国标设备)  
    如果接入了PISA和ONVIF  那么就会有PISA和ONVIF*/
    char szTreatyType[64];          //用于判断智能分析仪设备仅支持海康SDK(厂商 海康 + 协议类型 SDK) 
    char szDevKey[260];             //设备Key，集成平台判断设备类型及监控点类型最准确的字段
    bool bDevOnline;                //设备在线状态
	/*
	001-7000系列
	002-8000系列
	003-9000系列
	004-7100系列
	005-8100系列
	006-9100系列
	007-车载系列
	008-ATM系列
	009-PCDVR
	010-GB28181系列
	098-其它系列
	101-6000系列
	102-6100系列
	103-9001系列
	104-车牌识别系列
	105-智能分析系列
	106-单兵系列
	107-编码子系统
	201-标清系列
	202-高清系列
	203-标清智能球型系列
	204-高清智能球型系列
	205-智能交通系列
	099-全系列
	*/
    tagHikDeviceInfo* pNext;
}HikDeviceInfo;

//电视墙信息列表
typedef struct tagTvwall
{
    int iTvwallId;					        //电视墙id
    int nCellID;                            //组织ID
    char szIndexCode[64 ];                  //电视墙indexcode
    char szTvwallName[128];                 //电视墙名称
    int iPrivilege;							//权限
    char szVmmIp[32];					    //电视墙服务器ip
    unsigned int uPort;						//电视墙服务器端口
    tagTvwall* pNext;
}HikTvwallInfo;

//获取设备对讲列表
typedef struct tagHikTalkChannel
{
    int nTalkId;       //对讲通道ID
    int nTalkChannelNo;//对讲通道所在通道号
    int nCellId;   //所属组织架构
    char szDevIndexCode[64];  //所属设备编号
    char szIndexCode[64];  //对讲编号
    char szTalkName[260];   //名称
    tagHikTalkChannel* pNext;
}HikTalkChannel;

//IO信息列表
typedef struct tagHikIOInfo
{
    int nId;    //IO资源ID
    int nCellId;   //所属组织架构
    int nType;  //0~IO输入，1~IO输出
    char szDevIndexCode[64];  //所属设备编号
    char szIndexCode[64]; //编号
    char szIoName[260];   //名称
    int iChannalNO;       //IO通道号
    tagHikIOInfo* pNext;
}HikIOInfo;

//抓图参数(预览)
typedef struct _tagHikSnapParam
{
    int nPicType;   // 0 JPG 1BMP
    int nSnapType;  // 0 单张 1多张 (只对预览生效)
    int nMultiType;     //连续抓图方式 按时间 0 ，按帧 1
    int nSpanTime;  //多张时 时间间隔 ms
    int nSnapCount; //连抓张数  
    int Quality; //质量 (只对预览生效)
    char szSaveFolder[256];
    long lOpenFlag;   //打开方式
    int nFormatType;    //格式化方式
}HikSnapParam;

//录像参数配置
typedef struct _tagHikRecordCfgParam
{
    int nType;              // 0按时间分包 1，其他按 大小
    char szFolder[256];     // 录像存储文件夹
    DWORD dwMaxRecordTimes; // 最长录像时长 秒 0 不限制
    DWORD dwTimes;          // 分包大小 按秒
    ULONGLONG dwPackSize;   // 分包大小，0则不分包,单位 字节
    int nFormatType;        // 格式化方式
}HikRecordCfgParam,*LPHikRecordCfgParam;

//告警事件状态(iAlarmStatus) 
#define    HIK_EVENT_STATE_INSTANT   0         /* 瞬时事件 */
#define    HIK_EVENT_STATE_START     1         /* 事件开始 */
#define    HIK_EVENT_STATE_STOP      2         /* 事件结束 */
#define    HIK_EVENT_STATE_PULSE     3         /* 事件脉冲 */

//实时告警事件结构体
typedef struct _tagSubscribeAlarmInfo
{
    char    alarmStarttime[32];             //告警开始时间
    char    alarmStoptime[32];              //告警结束时间
    char    csEventDesc[128];               //告警名称
    char    csLogId[64];                    //告警ID
    char    alarmObjName[256];              //告警源
    char    alarmObjIndexcode[64];          //告警源indexcode
    int     alarmObjType;                   //告警源类型
    int     iEventId;                       //告警事件ID
    int     iAlarmLevel;                    //告警等级 0~低，1~中等，2~高
    int     iAlarmStatus;                   //告警状态，参考HIK_EVENT_STATE_INSTANT宏定义
    char    csPicUrl[256];                  //图片URL
    unsigned int uevent_type;               //事件类型
} ALARMINFO, *LPALARMINFO;

//目标资源列表 
typedef struct HikResource_List
{
    int     iResouceType; //资源类型(暂未使用，默认填)
    int     nResID;       //资源ID(暂未使用，默认填0)
    long    nUserData;    //用户ID(暂未使用，默认填0)
    char    szIndex[64];  //资源索引
    HikResource_List* pNext;
}HIKRESOURCE_LIST,*pHIKRESOURCE_LIST;

//搜索历史告警参数
typedef struct HikSearchAlarmLogParam
{
    int  iAlarmState;        //告警状态 /*增加全部状态字段 0 全部*/
    int  iConfirmState;      //确认状态

    char sObjKeyName[512];   /* 告警对象名称 支持LIKE模糊匹配 增加一个数据库字段*/
    char sEventKeyName[512]; //告警事件查询关键字
    char sBeginTime[65];     //查询告警 发生(开始)时间 起始点/* 格式-01-02 01:00:00 */
    char sEndTime[65];       //查询告警 发生(开始)时间 截止点 

    int  iSortType;          /*结果排序方式 由CMS进行排序,1 升序 2 降序*/
    char szSortName[128];    /*排序字段名称 目前商定仅UI设计的时间、等级、名称、状态升降序排序*/

    int* pEventTypes;        //事件ID数组  移动侦测什么的
    int nEventTypeNum;       //事件ID数组大小

    int* pLevels;          //等级
    int nLevelNum;         //事件等级数组大小

    pHIKRESOURCE_LIST pTarget; //目标列表
    int nTargetLen;            //目标列表长度
}HIKSEARCHALARMLOGPARAM,*pHIKSEARCHALARMLOGPARAM;


/*告警事件等级*/
enum HikAlarmLevel				
{
    HIK_LEVEL_HIGH = 1,    //高
    HIK_LEVEL_MEDIUM = 2,  //中
    HIK_LEVEL_LOW = 3      //低
};

/*告警事件类型*/
enum HikAlarmEventType
{   
    //监控点告警事件
    Hik_AlarmEventType_LOSE = 131329,       /*视频丢失*/
    Hik_AlarmEventType_COVER = 131330,      /*遮挡*/
    Hik_AlarmEventType_MD = 131331,         /*移动侦测*/
    Hik_AlarmEventType_VIDEO_PIR            = 131332,   /* 人体红外报警 */ 
    Hik_AlarmEventType_VIDEO_WIRELESS       = 131333,   /* 无线报警 */ 
    Hik_AlarmEventType_VIDEO_CALLHELP       = 131334,   /* 呼救报警 */

    //报警器告警事件
    Hik_AlarmEventType_IOIN = 589825,   //报警输入

    //智能监控点告警事件
    Hik_AlarmEventType_VCA_TRAVERSE_PLANE   = 131585,   /* 穿越警戒面 */
    Hik_AlarmEventType_VCA_ENTER_AREA       = 131586,   /* 进入区域 */
    Hik_AlarmEventType_VCA_EXIT_AREA        = 131587,   /* 离开区域 */
    Hik_AlarmEventType_VCA_INTRUSION        = 131588,   /* 周界入侵 */
    Hik_AlarmEventType_VCA_LOITER           = 131590,   /* 徘徊 */
    Hik_AlarmEventType_VCA_LEFT_TAKE        = 131589,   /* 物品拿取放置 */
    Hik_AlarmEventType_VCA_PARKING          = 131591,   /* 停车 */
    Hik_AlarmEventType_VCA_RUN              = 131592,   /* 快速移动  */
    Hik_AlarmEventType_VCA_HIGH_DENSITY     = 131593,   /* 人员聚集 */
    Hik_AlarmEventType_VCA_LEFT             = 131594,   /* 物品遗留 */
    Hik_AlarmEventType_VCA_TAKE             = 131595,   /* 物品拿取 */
    Hik_AlarmEventType_VCA_VIOLENT_MOTION   = 131596,   /* 场景突变 */
    Hik_AlarmEventType_VCA_REACH_HIGHT      = 131597,   /* 攀高检测 */
    Hik_AlarmEventType_VCA_GET_UP           = 131598,   /* 起身检测 */
    Hik_AlarmEventType_VCA_HUMAN_ENTER      = 131599,   /* 人靠近ATM  */
    Hik_AlarmEventType_VCA_OVER_TIME        = 131600,   /* 操作超时    */
    Hik_AlarmEventType_VCA_STICK_UP         = 131601,   /* 贴纸条,支持区域规则   */
    Hik_AlarmEventType_VCA_INSTALL_SCANNER  = 131602,   /* 安装读卡器,支持区域规则 */
    Hik_AlarmEventType_VCA_LEAVE_POSITION   = 131603,   /* 离岗 */
    Hik_AlarmEventType_VCA_TRAIL            = 131604,   /* 尾随 */
    Hik_AlarmEventType_VCA_FALL_DOWN        = 131605,   /* 倒地检测 */
    Hik_AlarmEventType_VCA_AUDIO_ABNORMAL   = 131606,   /* 声强突变检测 */
    Hik_AlarmEventType_VCA_ADV_REACH_HEIGHT = 131607,   /* 折线攀高 */
    Hik_AlarmEventType_VCA_TOILET_TARRY     = 131608,   /* 如厕超时  */
    Hik_AlarmEventType_VCA_YARD_TARRY       = 131609,   /* 放风场滞留  */
    Hik_AlarmEventType_VCA_FACE             = 131621,   /* 人脸侦测  */
    Hik_AlarmEventType_VCA_PLATE            = 131622,   /* 车辆侦测  */

    //客流量和人脸识别事件
    Hik_AlarmEventType_VCA_FACESNAP_RESULT  = 131614,   /*人脸识别结果*/
    Hik_AlarmEventType_VCA_FACESNAP_ALARM   = 131615,   /*人脸检测识别报警*/
    Hik_AlarmEventType_VCA_PDC_DATA         = 131616,   /*客流量统计*/
    Hik_AlarmEventType_VCA_PDC_FULL         = 131617,   /* 区域满员 */
    Hik_AlarmEventType_VCA_PDC_FULL_ALARM   = 131618,   /* 区域超员 */

    //门禁事件
    Hik_AlarmEventType_ACCESS_CARD_DOOR     = 198914,   // 刷卡开门
    Hik_AlarmEventType_ACCESS_OUT_DOOR      = 198916,   // 按钮开门
    Hik_AlarmEventType_ACCESS_IGL_DOOR      = 197633,   // 非法卡
    Hik_AlarmEventType_ACCESS_WRONG_PWD     = 197121,   // 刷卡密码错
    Hik_AlarmEventType_ACCESS_DOOR_OPEN     = 198657,   // 非法闯入
    Hik_AlarmEventType_ACCESS_OPEN_TIMEOUT  = 198400,   // 长时间未关门
    Hik_AlarmEventType_ACCESS_FORCE_OPEN    = 199425,   // 胁迫开门
    Hik_AlarmEventType_ACCESS_DOOR_ON       = 198913,   // 门打开
    Hik_AlarmEventType_ACCESS_SUPER_PWD     = 198915,   // 超级密码开门
    Hik_AlarmEventType_ACCESS_OUT_OFF       = 199169,   // 门关闭

    //巡更设备
    AlarmEventType_PATROL_NORMAL             = 262145,   // 正常
    AlarmEventType_PATROL_EARLIER            = 262146,   // 早巡
    AlarmEventType_PATROL_LATER              = 262147,   // 晚巡
    AlarmEventType_PATROL_LEAK               = 262148,   // 漏巡
    AlarmEventType_PATROL_MAKEUP             = 262149,   // 补漏巡
    AlarmEventType_PATROL_ALARM              = 262150,   // 巡更事件

    //动环主机
    Hik_AlarmEventType_ENV_TEMPERATURE           = 459009,   // 温度实时数据
    Hik_AlarmEventType_ENV_HUMIDITY              = 459010,   // 湿度实时数据
    
    // 电网设备    
    Hik_AlarmEventType_ELECNET_NORMAL            = 786433,   // 电网信息
    Hik_AlarmEventType_ELECNET_TOUCHNET          = 786434,   // 触网报警
    Hik_AlarmEventType_ELECNET_SHORTOUT          = 786435,   // 短路报警
    Hik_AlarmEventType_ELECNET_WIREBREAK         = 786436,   // 断线报警
    Hik_AlarmEventType_ELECNET_SENSOR            = 786437,   // 传感报警

    // GPS事件
    Hik_AlarmEventType_GPS           = 851969,   /* GPS告警 */
    Hik_AlarmEventType_GPS_SPEED     = 851970,   /* GPS超速 */
    Hik_AlarmEventType_GPS_OFFSET    = 851971,   /* GPS偏移 */

    // 客户端事件
    Hik_AlarmEventType_MANUAL               = 655361, /* 客户端手动事件 */
    Hik_AlarmEventType_MANUAL_FAULT         = 655362, /* 客户端故障上报 */
};

//////////////////////////////////////////////////////////////////////////
//分页信息
typedef struct PageInfo
{
    int iNum;      //@暂未使用
    int iAllRow;   //@暂未使用
    int iCurPage;  //当前页码
    int iTotalPage; //全部页码
    int iPageSize; //每页包含大小
    int iOffSet;   //@暂未使用
    int iTotalNum; //总大小
}HikPAGEINFO,*pHikPAGEINFO;

/** @enum HIK_STREAM_DATATYPE
* @brief 码流的数据类型
*/
enum HIK_STREAM_DATATYPE
{
    HIK_STREAM_FORWARD = 1, // 正放头标记
    HIK_STREAM_DATA = 2,    // 码流数据
    HIK_STREAM_END = 100,   // 结束标记(回放、下载或倒放结束)
};

/** 
*  @brief 实时告警事件接收回调
*  @param const ALARMINFO* pAlrInfo：实时告警信息
*  @param void* pUser：用户数据
*/
typedef void (__stdcall* pAlarmEventCallback)(const ALARMINFO* pAlrInfo, void* pUser);

/** 
*  @brief 取流回调(包括预览和回放)
*  @param long lSession：取流实例
*  @param int iStreamType：码流的数据类型,详细可参考HIK_STREAM_DATATYPE定义
*  @param const char* data：码流数据字符
*  @param int dataLen：码流数据长度
*  @param void* pUser：用户数据
*/
typedef void (__stdcall *pStreamCallback)(long lSession, int iStreamType, const char* data, int dataLen, void* pUser);

/** 
*  @brief 抓图拍照回调(包括预览和回放)
*  @param long lSession：取流实例
*  @param int nErr：错误码，一般为0，表示成功；其他暂不处理
*  @param const char* picPath：抓图成功后保存的图片全路径
*  @param void* pUser：用户数据
*/
typedef void (__stdcall *pSnapShotCallback)(long lSession,int nErr,const char* picPath,void* pUser);

/** 
*  @brief 预览紧急录像回调
*  @param long lSession：取流实例
*  @param int nErr：错误码，一般不处理
*  @param const char* data：码流数据
*  @param void* pUser：用户数据
*/
typedef void (__stdcall *pPreviewRecordEndCallback)(long lSession,int nErr,const char* data,void* pUser);

/** 
*  @brief MQ消息回调，接收GPS信息
*  @param int nMsgId：消息ID
*  @param int lParam：预留参数
*  @param const char* szInfo：GPS信息
*  @param void* pUser：用户数据
*/
typedef void (__stdcall *pGPSReceiveCallback)(int nMsgId,int lParam,const char* szInfo,void* pUser);

//常用操作权限码
#define HIK_WBS_OPCODE_PLAYVIEW         10001   //实时预览
#define HIK_WBS_OPCODE_PLAYBACK         10006   //录像回放
#define HIK_WBS_OPCODE_IO               40002   //查看告警器
#define HIK_WBS_OPCODE_TALKCHANNEL      90001   //查看对讲通道

//其他操作权限码
#define HIK_WBS_OPCODE_SERVIDEOPARAM    10002   //视频参数调节
#define HIK_WBS_OPCODE_LOCALRECORD      10003   //本地录像
#define HIK_WBS_OPCODE_PTZCONTROL       10004   //云镜控制
#define HIK_WBS_OPCODE_SERPTZ           10005   //云镜配置

//兼容C#以结构体数组形式参数输出资源列表
#define HIK_MAX_SIZE_RES_CELL          10000    //组织列表最大个数
#define HIK_MAX_SIZE_RES_CAMERA        2000     //组织下监控点列表最大个数
#define HIK_MAX_SIZE_RES_IO            2000     //组织下报警器列表最大个数
#define HIK_MAX_SIZE_RES_TALK_CAHNEL   2000     //组织下对讲通道列表最大个数
#define HIK_MAX_SIZE_RES_USER          1000      //组织下用户列表最大个数
#define HIK_MAX_SIZE_RES_TVWALL        200      //电视墙列表最大个数

//中心父节点ID
#define HIK_RS_CELL_PARENT_ID_ALL        -1     //获取全部组织列表

//组织类型
#define HIK_RS_CELL             1000 //组织
#define HIK_RS_USERCELL         3000 //用户组织

//资源信息
#define HIK_RS_CAMERA           10000 //监控点
#define HIK_RS_DEV_CODE         30000 //编码
#define HIK_RS_IO_ALARM         40000 //IO报警
#define HIK_RS_TALK_CHANNEL     90000 //对讲通道
#define HIK_RS_USER             2000  //用户资源

//播放控制
#define PLAY_START			    10001 //开始播放 
#define PLAY_PAUSE			    10002 //暂停播放
#define PLAY_FAST			    10003 //加快播放速度
#define PLAY_SLOW			    10004 //减慢播放速度
#define PLAY_OFFSET			    10005 //播放定位
#define PLAY_ONEFRAMEFORWARD    10006 //单帧进
#define PLAY_OneFRAMEBACKWARD   10007 //单帧退

//云台控制命令
#define PLAT_SET_PRESET	    8	//设置预置位
#define PLAT_CLE_PRESET	    9	//删除预置位
#define PLAT_ZOOM_IN	    11	//镜头拉近
#define PLAT_ZOOM_OUT	    12	//镜头移远
#define PLAT_FOCUS_NEAR	    13	//焦点前调
#define PLAT_FOCUS_FAR	    14	//焦点后调
#define PLAT_IRIS_OPEN	    15 	//光圈扩大
#define PLAT_IRIS_CLOSE	    16 	//光圈缩小
#define PLAT_TILT_UP	    21	//镜头向上
#define PLAT_TILT_DOWN	    22	//镜头向下
#define PLAT_PAN_LEFT	    23	//镜头向左
#define PLAT_PAN_RIGHT	    24	//镜头向右
#define PLAT_UP_LEFT	    25	//云台上仰和左转
#define PLAT_UP_RIGHT	    26	//云台上仰和右转
#define PLAT_DOWN_LEFT	    27	//云台下俯和左转
#define PLAT_DOWN_RIGHT	    28	//云台下俯和右转
#define PLAT_PAN_AUTO		29	//云台左右自动扫描
#define PLAT_FILL_PRE_SEQ	30	//将预置点加入巡航序列
#define PLAT_STA_MEM_CRUISE	34	//开始记录轨迹
#define PLAT_STO_MEM_CRUISE	35	//停止记录轨迹
#define PLAT_RUN_CRUISE		36	//开始轨迹
#define PLAT_RUN_SEQ	    37	//开始巡航
#define PLAT_STOP_SEQ	    38	//停止巡航
#define PLAT_GOTO_PRESET	39	//到达预置位
#define PLAT_CMD_3D_ZOOM    99  //3D放大
#define PLAT_CAMERA_UNLOCK	201	//解除云台锁定


#define PLAT_STATUS_DEFENCE     1   //布防
#define PLAT_STATUS_DISDEFENCE  2   //撤防

#define PLAT_STATUS_IOOPEN      8   //IO打开
#define PLAT_STATUS_IOCLOSE     9   //IO关闭

/* @brief 录像类型枚举
*/
enum HIK_RECORD_TYPE
{
    HIK_RECTYPE_UNKNOWN = 0,     // 未知
    HIK_RECTYPE_PLAN = 0x01,     // 计划录像
    HIK_RECTYPE_MOVE = 0x02,     // 移动录像
    HIK_RECTYPE_ALARM = 0x04,    // 告警录像
    HIK_RECTYPE_MANUAL = 0x10,   // 手动录像
    HIK_RECTYPE_ALL = 0xFF,      // 全部类型
};

#define PLAT_RECORD_RESULT_XML_BUFFER_SIZE   1024 * 200 //录像查询返回片段数据缓冲区大小

#define PLAT_MAX_PAGE_HISTORY_ALARMEVENT    2000        //历史告警日志查询单页最大条数

//错误码宏定义
#define	HIKPT_E_OK						    (0)	                                // 没有错误
#define	HIKPT_E_ERROR						(-1)                                // 其他通用错误

//通用错误码
#define SDK_ERROR_BASE					    (1000)						        ///错误码基数
#define SDK_ERROR_LOGINFAIL				    (SDK_ERROR_BASE+1)					///登录失败
#define SDK_ERROR_CONNECTCMS_FAIL		    (SDK_ERROR_BASE+2)					///连接CMS失败
#define SDK_ERROR_SERVER_FAIL_NAME_PASW	    (SDK_ERROR_BASE+3)					///用户名、密码错误
#define SDK_ERROR_SERVERURL_ERROR           (SDK_ERROR_BASE+4)					///服务器地址为空或者无效无效
#define SDK_ERROR_SERVER_MAIN_KICK_OUT      (SDK_ERROR_BASE+5)                  ///被管理员踢下线
#define SDK_ERROR_PLUG_LOAD                 (SDK_ERROR_BASE+6)                  ///插件加载失败
#define SDK_ERROR_PARA_OVER                 (SDK_ERROR_BASE+7)                  ///输入参数非法
#define SDK_ERROR_NOLOGIN                   (SDK_ERROR_BASE+8)                  ///用户未登录
#define SDK_ERROR_ALREADYLOGIN              (SDK_ERROR_BASE+9)                  ///用户已登录
#define SDK_ERROR_CLIENTFRAME_INIT          (SDK_ERROR_BASE+10)                 ///初始化主框架失败


//预览播放
#define SDK_ERROR_PREVIEW_FAIL	            (SDK_ERROR_BASE+20)					///预览失败
#define SDK_ERROR_PREVIEW_PERMISSION_FAIL   (SDK_ERROR_BASE+21)					///没有该监控点的实时预览权限
#define SDK_ERROR_PREVIEW_OUTOF_RES         (SDK_ERROR_BASE+22)					///播放实时监控视频失败,系统资源不足
#define SDK_ERROR_PREVIEW_MAX_CONN          (SDK_ERROR_BASE+23)					///播放实时监控视频失败,已超过流媒体最大连接数
#define SDK_ERROR_PREVIEW_LINCENE_MAX_CONN  (SDK_ERROR_BASE+24)					///播放实时监控视频失败,已超过Lincene最大连接数
#define SDK_ERROR_PREVIEW_PB_FAILED         (SDK_ERROR_BASE+25)					///保存即时回放录像失败
#define SDK_ERROR_PREVIEW_PB_FAILED_SPACE   (SDK_ERROR_BASE+26)					///保存即时回放录像失败,没有磁盘空间
#define SDK_ERROR_PREVIEW_DOWN              (SDK_ERROR_BASE+27)					///设备已下线

//云台控制
#define SDK_ERROR_PTZ_NET_ERROR             (SDK_ERROR_BASE+40)					///云镜操作失败!请检查网络配置
#define SDK_ERROR_PTZ_OPER_FAILED_LEVEL     (SDK_ERROR_BASE+41)					///云镜操作失败!云镜控制权被用户抢占
#define SDK_ERROR_PTZ_NO_SUPPORT            (SDK_ERROR_BASE+42)					///云镜操作失败!所请求的设备不支持该功能
#define SDK_ERROR_CRUISE_FAILED_TIP         (SDK_ERROR_BASE+43)					///设置巡航路径失败
#define SDK_ERROR_CRUISE_NAME_EXIST         (SDK_ERROR_BASE+44)					///设置巡航路径失败!巡航路径名称已存在
#define SDK_ERROR_CRUISE_NOT_ALL_NUM        (SDK_ERROR_BASE+45)					///巡航路径名称不得全部都是数字
#define SDK_ERROR_CRUISE_NOT_CONTAIN        (SDK_ERROR_BASE+46)					///巡航路径名称不得包含特殊字符
#define SDK_ERROR_PRESET_FAIL               (SDK_ERROR_BASE+50)					///设置预置点失败


//回放
#define SDK_ERROR_SEARCH_RECORD_FAILED      (SDK_ERROR_BASE+80)					///查询录像失败
#define SDK_ERROR_PLAYBACK_FAIL             (SDK_ERROR_BASE+81)					///回放录像失败
#define SDK_ERROR_PLAYBACK_PERMISSION_FAIL	(SDK_ERROR_BASE+82)					///没有回放权限
#define SDK_ERROR_PLAYBACK_CHECKTIME    	(SDK_ERROR_BASE+83)					///录像查询时间不符合规定或者开始时间大于截至时间
#define SDK_ERROR_CURTIME_NO_RECORD    	    (SDK_ERROR_BASE+84)					///当前时间段没有录像文件
#define SDK_ERROR_DOWNLOADFILE_FAIL    	    (SDK_ERROR_BASE+85)					///下载录像文件失败

//资源列表
#define SDK_ERROR_CELLINFO_LIST_CUTOFF           (SDK_ERROR_BASE+101)                ///组织列表被截断
#define SDK_ERROR_USERORG_LIST_CUTOFF            (SDK_ERROR_BASE+102)                ///用户组织列表被截断
#define SDK_ERROR_CAMERAINFO_LIST_CUTOFF         (SDK_ERROR_BASE+103)                ///监控点列表被截断
#define SDK_ERROR_IOINFO_LIST_CUTOFF             (SDK_ERROR_BASE+104)                ///IO列表被截断
#define SDK_ERROR_TALKCHANNEL_LIST_CUTOFF        (SDK_ERROR_BASE+105)                ///对讲通道列表被截断
#define SDK_ERROR_PLATFORMUSER_LIST_CUTOFF       (SDK_ERROR_BASE+106)                ///用户信息列表被截断
#define SDK_ERROR_TVWALL_LIST_CUTOFF             (SDK_ERROR_BASE+107)                ///电视墙信息列表被截断

//插件
#define SDK_ERROR_PLUG_LOAD_GETDATA             (SDK_ERROR_BASE+150)                 ///获取基础数据相关失败
#define SDK_ERROR_PLUG_LOAD_GETPREVIEW          (SDK_ERROR_BASE+151)                 ///获取预览相关失败
#define SDK_ERROR_PLUG_LOAD_GETALARMIMPL        (SDK_ERROR_BASE+152)                 ///获取告警相关失败
#define SDK_ERROR_PLUG_LOAD_GETPTZ              (SDK_ERROR_BASE+153)                 ///获取云镜控制失败
#define SDK_ERROR_PLUG_LOAD_GETAPC              (SDK_ERROR_BASE+154)                 ///获取APC失败
#define SDK_ERROR_PLUG_LOAD_GETAPCNETWORK       (SDK_ERROR_BASE+155)                 ///获取APC网络失败
#define SDK_ERROR_PLUG_LOAD_GETAPCHANDLE        (SDK_ERROR_BASE+156)                 ///获取APC句柄失败
#define SDK_ERROR_PLUG_LOAD_GETNET              (SDK_ERROR_BASE+157)                 ///获取网络失败
#define SDK_ERROR_PLUG_LOAD_GETNETTALK          (SDK_ERROR_BASE+158)                 ///获取对讲相关失败

#define SDK_ERROR_PLUG_NETTALKINIT              (SDK_ERROR_BASE+159)                 ///网络对讲初始化失败
#define SDK_ERROR_PLUG_NETTALKCREATE            (SDK_ERROR_BASE+160)                 ///网络对讲创建失败

#define SDK_ERROR_FILEPATH_NOTEXIST             (SDK_ERROR_BASE+170)                 ///文件目录不存在

//码流类型
enum HIK_STREAM_TYPE
{
    main_stream = 0, //主码流
    sub_stream = 1, //字码流
    third_stream = 2, //第三码流
};

//预置点信息列表
typedef struct tagPresetInfo
{
    int nPresetNo;                              //预置点号，对应于设备中的顺序
    char szPresetName[130];                     //预置点名称
    tagPresetInfo* pNext;
}HikPresetInfo;

//巡航点信息列表
typedef struct tagCruiseInfo
{
    int nPresetNo;                              //预置点号
    int nDwell;                                 //停留时间秒
    int nSpeed;                                 //巡航速度
    tagCruiseInfo* pNext;
}HikCruiseInfo;

#ifdef __cplusplus
}
#endif  //#ifdef __cplusplus


//函数区
template<class T>
bool copylist(const T* pSrc, T** pDst)
{
    if ((NULL == pSrc)
        || (NULL == pDst)
        )
    {
        return false;
    }
    const T* pTmp = pSrc;
    T* pLast = NULL,*pCur = NULL;
    while (NULL != pTmp)
    {
        pCur = new(std::nothrow)T(*pTmp);
        if (NULL != pCur)
        {
            pCur->pNext = NULL;
            if (NULL == (*pDst))
            {
                *pDst =  pCur;
            }
            if (NULL != pLast)
            {
                pLast->pNext = pCur;
            }
            pLast = pCur;
        }
        pTmp = pTmp->pNext;
    }
    return true;
}

//告警录像信息 告警历史内使用
typedef struct tagHikAlarmRecordLinkInfo
{
    char sLinkCamera[64];          /* 联动录像监控点*/
    char sLinkStaTime[65];         /* 联动录像开始时间*/
    char sLinkStpTime[65];         /* 联动录像结束时间*/
    tagHikAlarmRecordLinkInfo* pNext;
    tagHikAlarmRecordLinkInfo()
    {
        memset(sLinkCamera,0,sizeof(char)*64);
        memset(sLinkStaTime,0,sizeof(char)*65);
        memset(sLinkStpTime,0,sizeof(char)*65);
        pNext = NULL;
    }
    tagHikAlarmRecordLinkInfo(const tagHikAlarmRecordLinkInfo& obj)
    {
        strncpy_s(sLinkStaTime,_countof(sLinkStaTime),obj.sLinkStaTime,_TRUNCATE);
        strncpy_s(sLinkStpTime,_countof(sLinkStpTime),obj.sLinkStpTime,_TRUNCATE);
        strncpy_s(sLinkCamera,_countof(sLinkCamera),obj.sLinkCamera,_TRUNCATE);
        pNext = NULL;
    }
}HikAlarmRecordLinkInfo;

//告警图片信息 告警历史内使用
typedef struct tagHikAlarmSnapLinkInfo
{
    char sLinkUrl[256];            /* 联动图片Url*/
    char sLinkCamera[64];          /* 联动图片监控点*/
    char sLinkTriggerTime[65];           /* 联动图片开始时间*/
    int nLinkPicRet;                           /* 黑名单图片类型*/
    tagHikAlarmSnapLinkInfo* pNext;
    tagHikAlarmSnapLinkInfo()
    {
        memset(sLinkCamera,0,sizeof(char)*64);
        memset(sLinkUrl,0,sizeof(char)*256);
        memset(sLinkTriggerTime,0,sizeof(char)*65);
        nLinkPicRet = 0;
        pNext = NULL;
    }
    tagHikAlarmSnapLinkInfo(const tagHikAlarmSnapLinkInfo& obj)
    {
        strncpy_s(sLinkUrl,_countof(sLinkUrl),obj.sLinkUrl,_TRUNCATE);
        strncpy_s(sLinkCamera,_countof(sLinkCamera),obj.sLinkCamera,_TRUNCATE);
        strncpy_s(sLinkTriggerTime,_countof(sLinkTriggerTime),obj.sLinkTriggerTime,_TRUNCATE);
        nLinkPicRet = obj.nLinkPicRet;
        pNext = NULL;
    }
}HikAlarmSnapLinkInfo;

//告警确认信息 告警历史内使用
typedef struct tagHikAlarmConfrimInfo
{
    int nConfirmer;                                       //确认人
    char sConfirmerUser[130];	                  //确认人用户名 ： 用于级联告警确认显示确认人
    char sConfirmTime[65];				          // 确认时间
    char sConfirmDsc[1028];				              // 确认描述
    tagHikAlarmConfrimInfo()
    {
        nConfirmer = -1;
        memset(sConfirmTime,0,sizeof(char)*65);
        memset(sConfirmDsc,0,sizeof(char)*1028);
        memset(sConfirmerUser,0,sizeof(char)*130);
    }
    tagHikAlarmConfrimInfo(const tagHikAlarmConfrimInfo& obj)
    {
        strncpy_s(sConfirmTime,_countof(sConfirmTime),obj.sConfirmTime,_TRUNCATE);
        strncpy_s(sConfirmDsc,_countof(sConfirmDsc),obj.sConfirmDsc,_TRUNCATE);
        strncpy_s(sConfirmerUser,_countof(sConfirmerUser),obj.sConfirmerUser,_TRUNCATE);
        nConfirmer = obj.nConfirmer;
    }
}HikAlarmConfrimInfo;

//告警源信息 告警历史内使用
typedef struct tagHikAlarmSrcObjInfo
{
    int  iObjType;                                                    //产生告警的对象类型
    char szObjName[128];                     //产生告警的对象名
    char szObjIndex[64];					//产生告警的对象index
    tagHikAlarmSrcObjInfo()
    {
        iObjType = -1;
        memset(szObjName,0,sizeof(char)*128);
        szObjIndex[0] = '\0';
    }
    tagHikAlarmSrcObjInfo(const tagHikAlarmSrcObjInfo& obj)
    {
        strncpy_s(szObjName,_countof(szObjName),obj.szObjName,_TRUNCATE);
        strncpy_s(szObjIndex,_countof(szObjIndex),obj.szObjIndex,_TRUNCATE);
        iObjType = obj.iObjType;
    }
}HikAlarmSrcObjInfo;

//告警配置信息
typedef struct tagHikAlarmCfgInfo
{
    int   iAlarmType;                                                 //告警事件类型
    int   iAlarmEventlevel;                                        //告警等级      
    char  szAlarmEventCfgID[128];      //配置ID
    char  sAlarmEventname[1024];   //告警事件名字
    tagHikAlarmCfgInfo()
    {
        iAlarmType = -1;
        iAlarmEventlevel = -1;
        memset(sAlarmEventname,0,sizeof(char)*1024);
        memset(szAlarmEventCfgID,0,sizeof(char)*128);
    }
    tagHikAlarmCfgInfo(const tagHikAlarmCfgInfo& obj)
    {
        strncpy_s(sAlarmEventname,_countof(sAlarmEventname),obj.sAlarmEventname,_TRUNCATE);
        strncpy_s(szAlarmEventCfgID,_countof(szAlarmEventCfgID),obj.szAlarmEventCfgID,_TRUNCATE);
        iAlarmEventlevel = obj.iAlarmEventlevel;
        iAlarmType = obj.iAlarmType;
    }
}HikAlarmCfgInfo;

typedef struct tagHikAlarmTime
{
    char sBeginTime[65];                               //开始时间
    char sEndTime[65];                                  //结束时间
    tagHikAlarmTime()
    {
        memset(sBeginTime,0,sizeof(char)*65);
        memset(sEndTime,0,sizeof(char)*65);
    }
    tagHikAlarmTime(const tagHikAlarmTime& obj)
    {
        strncpy_s(sBeginTime,_countof(sBeginTime),obj.sBeginTime,_TRUNCATE);
        strncpy_s(sEndTime,_countof(sEndTime),obj.sEndTime,_TRUNCATE);
    }
}HikAlarmTime;

//黑名单信息
typedef struct tagHikAlarmBlackListInfo
{
    int   iBlackListSex;
    int   iBlackListIdType;
    char  szBlackListName[1024];
    char  szBlackListBirth[1024];
    char  szBlackListId[128];
    char  szBlackSimiValue[128];
    tagHikAlarmBlackListInfo()
    {
        iBlackListSex = -1;
        iBlackListIdType = -1;
        memset(szBlackListName,0,sizeof(char)*1024);
        memset(szBlackListBirth,0,sizeof(char)*1024);
        memset(szBlackListId,0,sizeof(char)*128);
        memset(szBlackSimiValue,0,sizeof(char)*128);
    }
    tagHikAlarmBlackListInfo(const tagHikAlarmBlackListInfo& obj)
    {
        iBlackListSex = obj.iBlackListSex;
        iBlackListIdType = obj.iBlackListIdType;
        strncpy_s(szBlackListName,_countof(szBlackListName),obj.szBlackListName,_TRUNCATE);
        strncpy_s(szBlackListBirth,_countof(szBlackListBirth),obj.szBlackListBirth,_TRUNCATE);
        strncpy_s(szBlackListId,_countof(szBlackListId),obj.szBlackListId,_TRUNCATE);
        strncpy_s(szBlackSimiValue,_countof(szBlackSimiValue),obj.szBlackSimiValue,_TRUNCATE);
    }
}HikBlackListInfo;

//搜索日志返回的结果信息
typedef struct tagHikSearchAlarmLogResult
{
    char sAlarmlogid[128];                      //告警日志ID          
    int  iStatus;                                        //告警状态

    char sLogtxt[1024];					             //日志信息	
    char sLogRemark[512];                            //日志备注 
    char sPicUrl[256];                               //图片信息

    bool isRecord;                                       //是否录像
    bool isConfrim;                                      //是否确认
    bool isPicture;                                      //是否有联动图片
    //HikAlarmRecordLinkInfo* pRcInfo;                        //录像信息
    HikAlarmConfrimInfo        confriminfo;                 //确认信息
    HikAlarmSrcObjInfo          objinfo;                    //告警源信息
    HikAlarmCfgInfo               cfginfo;                  //告警配置信息
    HikAlarmTime                   timeinfo;                //告警时间
    //HikAlarmSnapLinkInfo* pSnapInfo;
    HikBlackListInfo      blackListInfo;                         //黑名单信息

    //tagHikSearchAlarmLogResult* pNext;
    tagHikSearchAlarmLogResult()
    {
        sAlarmlogid[0] = '\0';
        iStatus = -1;
        sLogtxt[0] = '\0';
        sLogRemark[0] = '\0';
        sPicUrl[0] = '\0';
        isConfrim = false;
        isPicture = false;
        isRecord = false;
        //pRcInfo = NULL;
        //pSnapInfo = NULL;
        //pNext = NULL;
    }
    tagHikSearchAlarmLogResult(const tagHikSearchAlarmLogResult& obj):
    confriminfo(obj.confriminfo),
        objinfo(obj.objinfo),
        cfginfo(obj.cfginfo),
        timeinfo(obj.timeinfo),
        isConfrim(obj.isConfrim),
        isRecord(obj.isRecord),
        blackListInfo(obj.blackListInfo)
    {
        strncpy_s(sAlarmlogid,_countof(sAlarmlogid),obj.sAlarmlogid,_TRUNCATE);
        strncpy_s(sLogtxt,_countof(sLogtxt),obj.sLogtxt,_TRUNCATE);
        strncpy_s(sLogRemark,_countof(sLogRemark),obj.sLogRemark,_TRUNCATE);
        strncpy_s(sPicUrl,_countof(sPicUrl),obj.sPicUrl,_TRUNCATE);
        isConfrim = obj.isConfrim;
        isRecord = obj.isRecord;
        isPicture = obj.isPicture;
        iStatus = obj.iStatus;
        //pRcInfo = NULL;
        //copylist(obj.pRcInfo,&pRcInfo);
        //copylist(obj.pSnapInfo,&pSnapInfo);
        //pNext = NULL;
    }
}HIKSEARCHALARMLOGRESULT,*pHIKSEARCHALARMLOGRESULT;

#endif