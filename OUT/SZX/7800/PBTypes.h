/**@file  PBTypes.h
* @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
* @brief  回放模块中用到的类型的统一定义
*
* @author yangjw
* @date   2013/03/07
*/
#pragma once

#include <Windows.h>
#include <bitset>
#include <vector>
#include <string>
#include <map>

////////////////////////////////////////////////////////////////////////// 以下为自定义类型
typedef long PB_RET_TYPE; // 回放模块的返回值类型
typedef long PBMSG_ID_TYPE; // 回放模块的消息类型
typedef int WND_INDEX; // 窗口序号(0-based，从左到右，从上到下递增)

#define SNAP_FLAG_MANULA 0x00000001     //手动抓图
#define SNAP_FLAG_AUTO   0x00000002     //自动抓图

////////////////////////////////////////////////////////////////////////// 以下为常用的函数宏
// 删除对象指针
#define SAFE_DELETE(ptr) if ((ptr) != NULL)\
{\
    delete (ptr);\
    (ptr) = NULL;\
}
// 删除数组
#define SAFE_DELETE_ARRAY(ptr) if ((ptr) != NULL)\
{\
    delete[] (ptr);\
    (ptr) = NULL;\
}
// 删除窗口对象指针
#define SAFE_DELETE_WND_PTR(ptr) if ((ptr) != NULL)\
{\
    if ((ptr)->GetHWND() != NULL)\
    {\
        (ptr)->DestroyWindow();\
    }\
    delete (ptr);\
    (ptr) = NULL;\
}


////////////////////////////////////////////////////////////////////////// 以下为常量
/**@enum RECORD_TYPE
* @brief 录像类型枚举
*/
enum RECORD_TYPE
{
    RT_UNKNOWN = 0,     // 未知
    RT_PLAN = 0x01,     // 计划录像
    RT_MOVE = 0x02,     // 移动录像
    RT_ALARM = 0x04,    // 告警录像
    RT_MANUAL = 0x10,   // 手动录像
    RT_ALL = 0xFF,      // 全部类型
};

enum Label_Change
{
    Label_Change_Null = 0x00,
    Label_Change_Add = 0x01,
    Label_Change_Del  = 0x02,
    Label_Change_Mod = 0x03
};

/** @enum PB_STREAM_MODE
* @brief 取流模式
*/
enum PB_STREAM_MODE
{
    PBSTRM_NONE = 0,         // 没有任何控制
    // bit16~bit31，扩展模式，可相互组合
    PBSTRM_BUFFER = 0x10000, // bit16 过本地缓冲(1)不过缓冲(0)
    PBSTRM_DOWNLOAD = 0x20000, // bit17 下载(1)回放(0)
    // 默认：取流路径自动检测&本地缓冲
    PBSTRM_DEFAULT = PBSTRM_BUFFER,
};

/** @enum PB_STREAM_DATATYPE
* @brief 回放码流的数据类型
*/
enum PB_STREAM_DATATYPE
{
    // 底层库会直接回调上来的标识
    PBDT_FORWARD = 1, // 正放头标记
    PBDT_DATA = 2, // 码流数据
    PBDT_END = 100, // 结束标记(回放、下载或倒放结束)

    // 客户端自己加的额外标记
    PBDT_BACKWARD, // 倒放头标记(正放切换倒放标识)
    PBDT_SEEK_FINISHED, // 定位完成标记

    // 注：切换片段时回调中的长度参数转义为切换片段的开始时间，便于上层定位片段
    PBDT_SWITCH_TO_NEXT, // 切换到下个片段
    PBDT_SWITCH_TO_NEXT_FAIL, // 切换到下个片段失败

    PBDT_DRY_UP, // 码流断绝的标记
    PBDT_FILTER_NULL, // 过滤类型后无可用数据
    PBDT_CLOUDDOWNLOAD_FILESIZE, //云存储录像文件大小
};

/**@enum PB_STREAM_MSG_ID
* @brief 回放取流的消息定义
*/
enum PB_STREAM_MSG_ID
{
    MSG_SEEK_FAILED, // 定位失败
    MSG_SEEK_RETURN_FAILED, // 定位失败后返回原位也失败
    MSG_SEEK_RETURN_FINISHED, // 定位失败后返回了原位
    MSG_SEEK_FINISHED, // 定位成功完成
};

/** @enum PLAYBACK_SPEED
* @brief 回放速度
*/
enum PLAYBACK_SPEED
{
    PB_SPEED_MIN = -4, // 最小速度
    PB_SPEED_1_16 = -4, // 1/16倍速
    PB_SPEED_1_8 = -3, // 1/8倍速
    PB_SPEED_1_4 = -2, // 1/4倍速
    PB_SPEED_1_2 = -1, // 1/2倍速
    PB_SPEED_1_1 = 0, // 1倍速
    PB_SPEED_2_1 = 1, // 2倍速
    PB_SPEED_4_1 = 2, // 4倍速
    PB_SPEED_8_1 = 3, // 8倍速
    PB_SPEED_16_1 = 4, // 16倍速(8倍速倒放要保证GOP完整，可能要突进到16倍速全帧取流)
    PB_SPEED_MAX = 4, // 最大速度
    PB_SPEED_INVALID = 100, // 无效值
};

/*
工具条按钮
*/
enum MAINTOOLBAR_BTN_ID
{
	MAINTOOLBAR_BTN_ID_ALL = 0xff,			//全部
	MAINTOOLBAR_BTN_ID_NULL = 0x00,		//非法字段
	MAINTOOLBAR_BTN_ID_CONFIG = 0x03,  //配置按钮
    MAINTOOLBAR_BTN_ID_FULLSCREEN = 0x04,  //全屏按钮
    MAINTOOLBAR_BTN_ID_LAYOUT = 0x05, //窗口布局
};

/*
#define CFG_SNAP_FORMAT_NAME_TIME 1   //{监控点名称}_{时间}
#define CFG_SNAP_FORMAT_TIME      2   //{时间}
#define CFG_SNAP_FORMAT_TIME_NAME 3   //{时间}_{监控点名称}
*/
enum PB_KEYWORD_CFG
{
    KEYWORD_CAMNAME_TIME = 1,   //{监控点名称}_{时间}
    KEYWORD_TIME = 2,           //{时间}
    KEYWORD_TIME_CAMNAME = 3,   //{时间}_{监控点名称}
};

//TODO:yangjw,2013/10/16, 需改为消息机制，否则会有状态回调截获问题
/**@fn   <PB_STATECHG_CB>
*@brief  <状态改变的的回调定义>
*@param  <userData: 用户数据>
*@param  <idx: 窗口序号>
*@param  <stateIdx: 状态序号>
*@param  <bSet: TRUE表示该位被设置，FALSE表示该位被清空>
*@param  <tPlayTime: 播放时间>
*@return <PB_RET_TYPE: 成功返回HIK_E_OK，失败返回错误码>
*/
typedef PB_RET_TYPE (__stdcall *PB_STATECHG_CB)(void* userData, WND_INDEX idx, int stateIdx, BOOL bSet);

/**@fn   <PB_STATECHG_CB_EX>
*@brief  <状态改变的的回调定义（扩展版本，给电视墙用）>
*@param  <userData: 用户数据>
*@param  <ctrlPtr: 单路控制指针>
*@param  <stateIdx: 状态序号>
*@param  <bSet: TRUE表示该位被设置，FALSE表示该位被清空>
*@return <PB_RET_TYPE: 成功返回HIK_E_OK，失败返回错误码>
*/
typedef PB_RET_TYPE (__stdcall *PB_STATECHG_CB_EX)(void* userData, void* ctrlPtr, int stateIdx, BOOL bSet);

/**@fn   <PB_TOKEN_CB>
*@brief  <获取令牌的回调定义>
*@param  <userData: 用户数据>
*@param  <token: 待获取的令牌>
*@return <PB_RET_TYPE: 成功返回HIK_E_OK，失败返回错误码>
*/
typedef PB_RET_TYPE (__stdcall *PB_TOKEN_CB)(void* userData, WND_INDEX wndIndex, std::string& token);

/**@fn   <PB_FISHEYECFG_CB>
*@brief  <获取监控点鱼眼配置>
*@param  <userData: 用户数据>
*@param  <wndIndex: 窗口序号>
*@param  <pBasicInfo: 监控点基本信息>
*@param  <strCfg: 鱼眼配置>
*@return <PB_RET_TYPE: 成功返回HIK_E_OK，失败返回错误码>
*/
struct SPB_BASIC_INFO;
typedef PB_RET_TYPE (__stdcall *PB_FISHEYECFG_CB)(void* userData, WND_INDEX wndIndex, const SPB_BASIC_INFO* pBasicInfo, std::string& strCfg);

/**@fn   <PB_PLAYWND_DRAW_CB>
*@brief  <播放窗口画图回调>
*@param  <userData: 用户数据>
*@param  <wndIndex: 窗口序号>
*@param  <hDC: 绘图DC>
*@param  <rect：绘图区域>
*@return <void>
*/
typedef void (__stdcall* PB_PLAYWND_DRAW_CB)(void* userData, WND_INDEX wndIndex, HDC hDC, const RECT& rect);

/**@fn   <PB_PLAYWND_MSG_CB>
*@brief  <播放窗口消息回调>
*@param  <userData: 用户数据>
*@param  <wndIndex: 窗口序号>
*@param  <uMsg: 消息码>
*@param  <wParam：参数1>
*@param  <wParam：参数2>
*@return <void>
*/
typedef void (__stdcall* PB_PLAYWND_MSG_CB)(void* userData, WND_INDEX wndIndex, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**@enum SPBS_STATUS_INDEX
* @brief 单路回放各状态位的序号
*/
enum SPBS_STATUS_INDEX
{
    // bit0: 占用状态
    SPBS_INDEX_OCCUPIED = 0,

    // bit1~bit7 查询状态
    SPBS_INDEX_SEARCHING = 1,           // 未查询或已结束
    SPBS_INDEX_SEARCH_SUC,              // 查询成功
    SPBS_INDEX_HASRECORD,               // 有录像

    // bit8~bit15 取流状态
    SPBS_INDEX_STREAM_CONNECTING = 8,   // 正在取流
    SPBS_INDEX_STREAM_CONNECTED,        // 已取到流
    SPBS_INDEX_STREAM_BACKWARD,         // 倒放取流
    SPBS_INDEX_STREAM_DRYUP,            // 取流异常（码流干枯）
    SPBS_INDEX_STREAM_PAUSED,           // 取流暂停
    SPBS_INDEX_STREAM_SEEKING,          // 取流定位

    // bit16~bit31 播放状态
    SPBS_INDEX_PLAY_PLAYING = 16,       // 播放状态
    SPBS_INDEX_PLAY_REVERSE,            // 倒放状态
    SPBS_INDEX_PLAY_SPEED_ON,           // 设置速度（bSet表示速度值）
    SPBS_INDEX_PLAY_SOUNDON,            // 声音打开
    SPBS_INDEX_PLAY_PAUSED,             // 暂停
    SPBS_INDEX_PLAY_FRAME_FORWARD,      // 单帧进
    SPBS_INDEX_PLAY_FRAME_BACKWARD,     // 单帧退
    SPBS_INDEX_PLAY_DIGTAL_ZOOM,        // 电子放大
    SPBS_INDEX_PLAY_ADAPTIVE,           // 画面自适应
    SPBS_INDEX_PLAY_SOUND_ADJUST,       // 音量调节（bSet表示音量值）
    SPBS_INDEX_PLAY_ON_TVWALL,          // 回放上墙
    SPBS_INDEX_PLAY_END,                // 播放结束
    SPBS_INDEX_PLAY_FISHEYE,            // 鱼眼播放
    SPBS_INDEX_EXPAND_CORNER,           // 四角展开
};
typedef std::bitset<32> SPB_STATUS_TYPE; // 单路回放状态的类型

/**@enum SECTION_PLAYBACK_NUM
* @brief 分段回放的分段数
*/
enum SECTION_PLAYBACK_NUM
{
    SECTION_4 = 4, // 四分段
    SECTION_9 = 9, // 九分段
    SECTION_16 = 16, // 十六分段
};

/**@enum PLAYBACK_DISK_OPERATION
* @brief 回放中涉及磁盘的操作
*/
enum PLAYBACK_DISK_OPERATION
{
    PB_DISK_OP_SNAPSHOT, // 抓图
    PB_DISK_OP_CLIP,     // 剪辑
};

/**@enum DISK_SPARE_SPACE_STATE
* @brief 磁盘剩余空间状态的定义
*/
enum DISK_FREE_SPACE_STATE
{
    DFSS_SUFFICIENT, // 空间充足（操作不受影响）
    DFSS_CONSTRAINED, // 空间受限（操作不受影响，但需提示用户）
    DFSS_NOSPACE, // 空间不足（操作无法进行，需提示用户）
    DFSS_NOT_EXIST, // 路径不存在
};

/**@enum PLAY_MSG_ID
* @brief 播放消息ID
*/
enum PLAY_MSG_ID
{
    PLAY_MSG_FINISH_CLIP = 0, // 剪辑正常结束(和RecordCtrl.h中同义字段同值)
    PLAY_MSG_ABORT_CLIP = 2, // 剪辑异常终止(和RecordCtrl.h中同义字段同值)
    PLAY_MSG_SPACE_ERR = 4, // 空间不足或磁盘不存在等异常(和RecordCtrl.h中同义字段同值)
    PLAY_MSG_PLAY_END = 33, // 播放到结尾
    PLAY_MSG_SIZE_CHG, // 图片尺寸变化
    PLAY_MSG_TIME_CHG_AFT_SEEK, // 定位后，获取到的时间戳发生改变（此时才能认为是定位完成）
};

namespace playback
{
    const unsigned long DEFAULT_MEM_BUF_SIZE = 10*1024*1024; // 默认内存缓冲字节数
    const time_t INVALID_TIME_VALUE = -1; // 无效的时间值
    const time_t YEAR_2000_BEGIN = 946656000; // "2000-1-1 0:0:0"
    const time_t YEAR_2030_END = 1924963199; // "2030-12-31 23:59:59"
    const WND_INDEX INVALID_WND_INDEX = -1; // 无效的窗口序号
    const WND_INDEX ALL_WND_INDEX = -1; // 表示“全部窗口”的序号
    const int INVALID_CAMERA_ID = -1; // 无效的监控点ID
    const int INVALID_LABEL_ID = -1; // 无效的标签ID
    const std::string FIRM_OF_RECORD_HIK("hik");
    const std::string FIRM_OF_RECORD_DH("dahua");
    const int DEV_FIRM_HIK = 0; // 厂商类型是海康
    const unsigned int RCD_TYPE_ALL = 0xFF; // 全部录像类型
}

////////////////////////////////////////////////////////////////////////// 以下为自定义数据结构及回调函数
/**@struct RCD_ABILITY
*@brief    录像相关的能力集
*/
struct RCD_ABILITY
{
    // 录像检索与管理能力
    bool CanSearchExit;     // 日历查询（查询是否有录像）
    bool CanBeLocked;       // 锁定解锁
    bool CanEditLabel;      // 标签增删改
    // 取流能力
    bool CanStrmReversed;   // 倒序
    bool CanExtractFrame;   // 抽帧
    bool CanGetKFImg;       // 获取关键帧图片
    bool CanFullSpdDown;    // 全速下载
    bool CanResumeBrkPt;    // 断点续传
    // 播放能力
    bool CanGetPlayTime;    // 获取播放时间

    RCD_ABILITY()
    {
        CanSearchExit = true;
        CanBeLocked = true;
        CanEditLabel = true;
        CanStrmReversed = true;
        CanExtractFrame = true;
        CanGetKFImg = true;
        CanFullSpdDown = true;
        CanResumeBrkPt = true;
        CanGetPlayTime = true;
    }
};

/**@struct PB_CASCADE_INFO
*@brief    回放级联信息
*/
struct PB_CASCADE_INFO
{
    bool bCasc;             // 是否为级联监控点
    int  nCascServerPort;        // 级联服务器端口
    std::string szCascServerIP;  // 级联服务器IP
    std::string szCascDecodeTag; // 级联监控点解码标志
    PB_CASCADE_INFO()
    {
        bCasc = false;
        nCascServerPort = 7099;
        szCascServerIP = "10.64.49.218";
        szCascDecodeTag = "hik";
    }
};

/**@enum RCD_SERVER_TYPE
* @brief 录像服务器类型
*/
enum PB_RCD_SERVER_TYPE
{
    PB_RCD_SERVER_TYPE_VMS,
    PB_RCD_SERVER_TYPE_VRM,
    PB_RCD_SERVER_TYPE_KMS,
};

#define STORE_DEVICE_TYPE_NVR      51     // nvr
#define STORE_DEVICE_TYPE_PCNVR    52     // pcnvr
#define STORE_DEVICE_TYPE_CVR      53     // cvr
#define STORE_DEVICE_TYPE_NVRCM    54     // pcnvr云
#define STORE_DEVICE_TYPE_LAKER    55     // Laker云
#define STORE_DEVICE_TYPE_DVR      57     // dvr，设备存储

/**@struct PB_CAMERA_INFO
*@brief    回放所需的监控点信息
*/
struct PB_CAMERA_INFO
{
    std::string camName;    // 监控点名称
    std::string camIdx;     // 监控点编号
    int storeType;          // 存储方式
    int rcdSvrType;         // 录像服务器类型
    std::string rcdSvrIP;   // VRM地址、KMS地址
    int rcdSvrPort;         // VRM端口、KMS端口
    PB_CAMERA_INFO()
    {
        storeType = 0;
        rcdSvrType = PB_RCD_SERVER_TYPE_VMS;
        rcdSvrPort = 0;
    }
};

/**@struct PB_DEVICE_INFO
*@brief    回放所需的设备信息
*/
struct PB_DEVICE_INFO
{
    std::string devName;        // 设备名称
    std::string devIdx;         // 设备编号
    std::string devIP;          // 设备存储是为设备ip，cvr，pcnvr，云存储时指的是对应服务器的ip
    int devPort;                // 设备存储是为设备端口，cvr，pcnvr，云存储时指的是对应服务器的端口
    std::string userName;       // 设备存储是为设备用户名，cvr，pcnvr，云存储时指的是对应服务器的用户名
    std::string password;       // 设备存储是为设备密码，cvr，pcnvr，云存储时指的是对应服务器的密码
    int channelNo;              // 通道 (仅设备存储和NVR存储时用) 
    std::string linkType;       // 连接类型，包括"VAG"等(仅设备存储时用)。荧石云时这里请填写VAG，目前设计荧石云是必须过vag的。
    int netZone;                // 设备所在网域(仅设备存储时用)
    int installType;            // 安装方式
    int devVideoType;           // 机型 标清网络半球
    int devFirm;                // 设备厂商
    int productSeries;          // 产品系列
    PB_DEVICE_INFO()
    {
        devPort = 0;
        userName = "admin";
        password = "12345";
        channelNo = 0;
        linkType = "VAG";
        netZone = 1;
        installType = 0;
        devVideoType = 0;
        devFirm = playback::DEV_FIRM_HIK;
        productSeries = 0;
    }
    PB_DEVICE_INFO(const PB_DEVICE_INFO& other)
    {
        *this = other;
    }
    PB_DEVICE_INFO& operator=(const PB_DEVICE_INFO& other)
    {
        if (this != &other)
        {
            devName = other.devName;
            devIdx = other.devIdx;
            devIP = other.devIP;
            devPort = other.devPort;
            userName = other.userName;
            password = other.password;
            channelNo = other.channelNo;
            linkType = other.linkType;
            netZone = other.netZone;
            installType = other.installType;
            devVideoType = other.devVideoType;
            devFirm = other.devFirm;
            productSeries = other.productSeries;
        }
        return *this;
    }
};

/**@struct PB_RCD_SVR_INFO
*@brief    录像服务器相关信息
*/
struct PB_RCD_SVR_INFO
{
    std::string rcdMgrSvrIp;    // 录像管理服务器（一般是VRM）的IP
    std::string rcdMgrSvrPort;  // 录像管理服务器（一般是VRM）的端口
    std::string rcdVodIp;       // 录像取流服务器的ip（可不指定）
    std::string rcdVodPort;     // 录像取流服务器的端口（可不指定）
};

/**@struct PB_CU_INFO
*@brief    和回放相关的客户端信息
*/
struct PB_CU_INFO
{
    std::string userName;       // 登录的用户名
    int cuZoneId;               // 客户端的网域
    std::string cmsIp;          // CMS的IP
    int cmsPort;                // CMS端口
    std::string cmsContext;     // CMS上下文
    std::string vmsIp;          // vms的IP
    int vmsPort;                // vms端口
    std::string vmsContext;     // vms上下文
    PB_TOKEN_CB pTokenFun;      // 获取令牌的回调
    void* pTokenUser;           // 获取令牌的用户数据
    PB_CU_INFO()
    {
        cuZoneId = 0;
        cmsPort = 0;
        vmsPort = 0;
        pTokenFun = NULL;
        pTokenUser = NULL;
    }
    ~PB_CU_INFO()
    {
        pTokenFun = NULL;
        pTokenUser = NULL;
    }
    PB_CU_INFO(const PB_CU_INFO& other)
    {
        *this = other;
    }
    PB_CU_INFO& operator=(const PB_CU_INFO& other)
    {
        if (this != &other)
        {
            userName = other.userName;
            cuZoneId = other.cuZoneId;
            cmsIp = other.cmsIp;
            cmsPort = other.cmsPort;
            cmsContext = other.cmsContext;
            vmsIp = other.vmsIp;
            vmsPort = other.vmsPort;
            vmsContext = other.vmsContext;
            pTokenFun = other.pTokenFun;
            pTokenUser = other.pTokenUser;
        }
        return *this;
    }
};

/**@enum SPB_BASIC_INFO
* @brief 单路回放的基本信息
*/
struct SPB_BASIC_INFO
{
    PB_CU_INFO stCuInfo;        // 客户端信息
    PB_CAMERA_INFO stCamera;    // 监控点信息
    PB_DEVICE_INFO stDevice;    // 设备信息
    PB_CASCADE_INFO stCascade;  // 级联信息
    RCD_ABILITY stAbility;      // 能力集(本身支持哪些功能)
    std::string rightCode;      // 权限代码(允许用户使用哪些功能)
    SPB_BASIC_INFO()
    {
        //rightCode = "10022,10027,10028,10029,10032";
    }
};

namespace playback
{
    const int PB_OPCODE_DOWNLOAD = 10014;//下载权限
    const int PB_OPCODE_LABEL = 10020;//添加标签
    const int PB_OPCODE_VOICE = 10022;//打开声音
    const int PB_OPCODE_ONE_SNAP = 10027;//单抓
    const int PB_OPCODE_MULTI_SNAP = 10028;//多抓
    const int PB_OPCODE_TVWALL_BTN = 10029;//上墙
    const int PB_OPCODE_FAIL_REPORT = 10031;//故障上报
    const int PB_OPCODE_SAVE_CLIP = 10032;//录像剪辑
}

//时间跨度 具体时间类型还需要调整
typedef struct TimeSpan
{
    char szStaTime[64];    //UTC时间类型 UI上必须给出UTC类型 底层逻辑不检查有效性
    char szEndTime[64];    //
    TimeSpan()
    {
        memset(szStaTime,0,64);
        memset(szEndTime,0,64);
    }
    ~TimeSpan()
    {
    }
    void reset()
    {
        memset(szStaTime,0,64);
        memset(szEndTime,0,64);
    }

    TimeSpan(const TimeSpan& other)
    {
        strncpy_s(szStaTime, 64, other.szStaTime, _TRUNCATE);
        strncpy_s(szEndTime, 64, other.szEndTime, _TRUNCATE);
    }
    TimeSpan& operator=(const TimeSpan& other)
    {
        if (this != &other)
        {
            reset();
            strncpy_s(szStaTime, 64, other.szStaTime, _TRUNCATE);
            strncpy_s(szEndTime, 64, other.szEndTime, _TRUNCATE);
        }
        return *this;
    }
}TIMESPAN,*pTIMESPAN;

/**@struct RECORD_SEGMENT
*@brief    录像片段信息
*/
struct RECORD_SEGMENT
{
    std::string url; // 片段取流URL
    time_t tBegin; // 片段开始时间
    time_t tEnd; // 片段结束时间
    int recordType; // 录像类型

    RECORD_SEGMENT()
        :url("")
        ,tBegin(0)
        ,tEnd(0)
        ,recordType(RT_UNKNOWN)
    {
    }
};
typedef std::map<time_t, RECORD_SEGMENT> SegmentsMap; // 码流片段信息集合: 开始时间-码流片段信息

/**@struct SEGMENT_DETAILED_INFO
*@brief    录像片段详细信息
*/
struct SEGMENT_DETAILED_INFO
{
    RECORD_SEGMENT stBrief; // 简要信息
    BOOL bLocked; // 是否锁定
    unsigned long mediaDataLen; // 片段的数据长度（字节数）
    /*锁定的时间和片段时间一致，
    但是因为取流或时间轴绘制会截断片段时间，
    因此需要额外保留锁定时间*/
    time_t tLockBegin; // 锁定的开始时间
    time_t tLockEnd; // 锁定的结束时间
    SEGMENT_DETAILED_INFO()
        :bLocked(FALSE)
        ,mediaDataLen(0)
        ,tLockBegin(0)
        ,tLockEnd(0)
    {
    }
};
typedef std::map<time_t, SEGMENT_DETAILED_INFO> RECORD_SEARCH_RESULT_MAP; // 录像片段详细信息集合: 开始时间-录像片段详细信息

/**@struct SEGMENT_DETAILED_INFO
*@brief    录像片段详细信息
*/
typedef struct SectionPlayRecordInfo
{
	time_t tSta;
	time_t tEnd;
	RECORD_SEARCH_RESULT_MAP segs;

	SectionPlayRecordInfo():
	tSta(0),
	tEnd(0)
	{
	}

	SectionPlayRecordInfo(const SectionPlayRecordInfo&obj):
	tSta(obj.tSta),
	tEnd(obj.tEnd),
	segs(obj.segs)
	{
	}
}SECTION_PLAY_RECORDINFO;

/**@struct BRIEF_PLAY_PARAM
*@brief    单路播放的简单参数
*/
struct BRIEF_PLAY_PARAM
{
    std::string manufacturer; // 制造商：目前支持HIKPlay、DHPlay
    time_t tBegin; // 开始播放时间
    time_t tEnd; // 结束播放时间
    BRIEF_PLAY_PARAM()
        :manufacturer("HIKPlay")
        ,tBegin(playback::INVALID_TIME_VALUE)
        ,tEnd(playback::INVALID_TIME_VALUE)
    {
    }
};
typedef std::map<WND_INDEX, BRIEF_PLAY_PARAM> MULTI_PLAY_PARAM; // 多路播放参数： 窗口序号 - 单路播放的简单参数

/**@enum FILE_CATEGORIZE
* @brief 文件归类依据
*/
enum FILE_CATEGORIZE
{
    FILE_CATE_NONE = 0, // 不归类
    FILE_CATE_BY_CAMERA_NAME, // 按监控点名
    FILE_CATE_BY_DATE, // 按日期
};

/**@enum TOOLBAR_SHOW_MODE
* @brief 小窗口工具栏的显示模式
*/
enum TOOLBAR_SHOW_MODE
{
    TBSM_ALWAYS_HIDE = 0, // 0总是隐藏
    TBSM_ALWAYS_SHOW = 1, // 1总是显示
    TBSM_AUTO = 2, // 2自动显隐
};

/**@struct PB_SNAP_CFG
*@brief    回放抓图的配置
*/
struct PB_SNAP_CFG
{
    int fileFormat; // 保存格式：0jpeg，1bmp (参考playstruct.h中的SnapPicType)
    std::string picPath; // 图片保存路径
    int fileCategorization; // 文件归类依据：0不归类，1按监控点名，2按日期（通过配置项）
    int nContinuousNum; // 连续抓图张数[3,6]（抓图模式为连续抓图时此参数有效）
    int nContinuousInterval; // 连续抓图间隔（毫秒）：[200,3000]（连续抓图时此参数有效）
    int nContinuousMode; // 连续抓图模式：1按秒，2按帧 (参考playstruct.h中的SnapMode)
    int fileNameFormat; // 使用表达式自定义文件名 参见 PB_SANPSHOT_NAME
    unsigned long snapMode; // 抓图模式：1手动，2自动 (参考playstruct.h中的SnapPicType)
    std::string picNameKeyword; // 图片名称中的关键字 (由fileNameFormat转换而来，不是直接配置的)

    PB_SNAP_CFG()
        :fileFormat(0)
        ,fileCategorization(FILE_CATE_NONE)
        ,nContinuousNum(0)
        ,nContinuousInterval(0)
        ,nContinuousMode(0)
        ,snapMode(SNAP_FLAG_AUTO)
        ,fileNameFormat(KEYWORD_CAMNAME_TIME)
    {
    }
};


/**@struct PB_SAVE_CLIP_CFG
*@brief    录像剪辑参数
*/
struct PB_CAM_PLAY
{
    std::string CamIndex;     // 保存路径
    time_t nTime;
};

/**@struct PB_SAVE_CLIP_CFG
*@brief    录像剪辑参数
*/
struct PB_SAVE_CLIP_CFG
{
    std::string folder;     // 保存路径
    int fileNameFormat; // 使用表达式自定义文件名 参见 PB_SANPSHOT_NAME
    int packSize;   // 分包大小(MB)
    std::string nameKeyword; // 名称中的关键字 (由fileNameFormat转换而来，不是直接配置的)
    PB_SAVE_CLIP_CFG()
        :fileNameFormat(KEYWORD_CAMNAME_TIME)
        ,packSize(0)
    {
    }
};

/**@struct PB_CONFIGURATION
*@brief    回放的配置项
*/
struct PB_CONFIGURATION
{
    // 小窗口上的工具栏的显示模式：见TOOLBAR_SHOW_MODE
    int toolbarShowMode;
    // 小窗口上的状态栏的显示模式：见TOOLBAR_SHOW_MODE
    int statusbarShowMode;
    // 各个按钮的ID（顺序有意义）
    std::vector<int> toolbarBtns;
    // 抓图参数
    PB_SNAP_CFG snapCfg;
    // 剪辑参数
    PB_SAVE_CLIP_CFG clipCfg;
    // 是否支持鱼眼
    bool bSupportFishEye;
    // 鱼眼播放
    bool bFishEyeMode;

    PB_CONFIGURATION()
        :toolbarShowMode(TBSM_AUTO)
        ,statusbarShowMode(TBSM_AUTO)
        ,bSupportFishEye(true)
        ,bFishEyeMode(false)
    {
    }
};

/**@struct PB_PERFORMACE_PARAM
*@brief    回放性能参数
*@note     后续会拆分为具体细节(DECODE_DETAIL宏的内容)
*/
struct PB_PERFORMACE_PARAM
{
    int decodeEffect;   // 解码性能，从最好流畅到最小内存占用共9级[1,9]
#ifdef DECODE_DETAIL
    int throwBFrameNum; // 丢B帧数量
    unsigned long srcBufSize; // 解码前缓冲，范围200~10240K
    unsigned long displayBufNum; // 解码后缓冲，范围10~50帧
    BOOL decodeIFrameOnly; // 是否只解I帧
#endif // DECODE_DETAIL

    PB_PERFORMACE_PARAM()
        :decodeEffect(5)
#ifdef DECODE_DETAIL
        ,throwBFrameNum(0)
        ,srcBufSize(200)
        ,displayBufNum(10)
        ,decodeIFrameOnly(FALSE)
#endif // DECODE_DETAIL
    {
    }
};

typedef void (__stdcall * PB_DataFun_CB)(unsigned char* pBuf,DWORD dwSize,DWORD dwType,long lUser);
typedef void (__stdcall * PB_MsgFun_CB)(int nMsg,long lUser);

/**@struct PB_STREAM_DETAIL
*@brief    单路回放详细取流参数
*/
struct PB_STREAM_DETAIL
{
    SegmentsMap segments; // 取流片段信息集合
    time_t tBegin; // 播放的开始时间
    time_t tEnd; // 播放的结束时间
    unsigned long uStrmMode; // 取流模式（默认PBSTRM_DEFAULT）
    unsigned long ulDldOffset; // 下载的偏移字节数(uStrmMode含PBSTRM_DOWNLOAD下载模式时有效，是相对于tBegin的偏移）

    PB_DataFun_CB pFunData; // 取流数据回调
    long pDataUserData; // 取流数据回调用户数据
    PB_MsgFun_CB pFunMsg; // 取流消息回调
    long pMsgUserData; // 取流消息回调用户数据
    PB_TOKEN_CB pFunToken; // 获取取流令牌的回调（为空表示不加令牌）
    void* pTokenUserData; // 获取令牌回调用户数据

    PB_STREAM_DETAIL()
        :tBegin(0)
        ,tEnd(0)
        ,uStrmMode(PBSTRM_DEFAULT)
        ,ulDldOffset(0)
        ,pFunData(NULL)
        ,pDataUserData(0)
        ,pFunMsg(NULL)
        ,pMsgUserData(0)
        ,pFunToken(NULL)
        ,pTokenUserData(NULL)
    {
    }

    PB_STREAM_DETAIL& operator=(const PB_STREAM_DETAIL& other)
    {
        if (&other != this)
        {
            segments = other.segments;
            tBegin = other.tBegin;
            tEnd = other.tEnd;
            uStrmMode = other.uStrmMode;
            ulDldOffset = other.ulDldOffset;
            pFunData = other.pFunData;
            pDataUserData = other.pDataUserData;
            pFunMsg = other.pFunMsg;
            pMsgUserData = other.pMsgUserData;
            pFunToken = other.pFunToken;
            pTokenUserData = other.pTokenUserData;
        }
        return *this;
    }

    PB_STREAM_DETAIL(const PB_STREAM_DETAIL& other)
    {
        *this = other;
    }

    ~PB_STREAM_DETAIL()
    {
        pFunData = NULL;
        pDataUserData = 0;
        pFunMsg = NULL;
        pMsgUserData = 0;
        pFunToken = NULL;
        pTokenUserData = NULL;
    }
};

/**@struct PB_STREAM_BREAKPOINT
*@brief    回放取流断点
*/
struct PB_STREAM_BREAKPOINT
{
    time_t tBpBegin;                // 断点所在片段的开始时间
    unsigned long ulOffsetBytes;    // 断点距离其所在片段开始位置的偏移字节数
    PB_STREAM_BREAKPOINT()
        :tBpBegin(0)
        ,ulOffsetBytes(0)
    {
    }
};

/**@struct SIMPLE_LABEL_INFO
*@brief    简单的标签信息
*/
struct SIMPLE_LABEL_INFO
{
    int nLabelID;
    int nLabelVideoType; //标签录像类型 0 常规 1备份
    std::vector<std::string> vCameraIndexcodes;
    std::string strDocId; // 文件编号（KMS中保存的文件有此编号）
    std::string strTimeST; // 开始时间（cms格式）
    std::string strTimeEd; // 结束时间（cms格式）
    std::string strCreateTm;//从创建时间
    std::string strUser;	//创建用户
    std::string strCamsName;//标签对应的监控点名
    std::string strLabelName; // 标签名
    std::string strExternInfo; // 扩展信息(也就是标注的内容)

    SIMPLE_LABEL_INFO()
        :nLabelID(playback::INVALID_LABEL_ID),
        nLabelVideoType(0)
    {
        vCameraIndexcodes.empty();
    }

    SIMPLE_LABEL_INFO(const SIMPLE_LABEL_INFO& obj)
        :nLabelID(obj.nLabelID),
        nLabelVideoType(obj.nLabelVideoType),
        vCameraIndexcodes(obj.vCameraIndexcodes),
        strDocId(obj.strDocId),
        strTimeST(obj.strTimeST),
        strTimeEd(obj.strTimeEd),
        strCreateTm(obj.strCreateTm),
        strUser(obj.strUser),
        strCamsName(obj.strCamsName),
        strLabelName(obj.strLabelName),
        strExternInfo(obj.strExternInfo)
    {
    }
};
typedef std::map<long, SIMPLE_LABEL_INFO> labelMap; // 标签ID-标签简要信息

/**@struct LabelWndParamInfo
*@brief    标签增改参数
*/
struct LabelWndParamInfo
{
    time_t t_sta;       //开始时间 
    time_t t_stp;       //结束时间  cms标准
    std::string strName;          //标签名
    std::string strContent;       //标签内容
    time_t t_exp ;   //锁定过期时间
    bool bLock;            //是否锁定
    int nLabelID;        //
	std::string strUser;
	std::string strCamIdx;

    LabelWndParamInfo()
    {
        bLock = false;
        nLabelID = -1;
        t_sta = 0;
        t_stp = 0;
        t_exp = 0;
    }
};

/**@struct LockWndParamInfo
*@brief    锁定的条件
*/
struct LockWndParamInfo
{
    time_t tmSta_t;
    time_t tmStp_t;
    time_t tmExp_t;
    std::string strUser;
    std::string strCamIdx;

    LockWndParamInfo()
    {
        tmSta_t = 0;
        tmStp_t = 0;
        tmExp_t = 0;
    }
};

/**@struct PBToTvWallParam
*@brief    回放上墙的参数
*/
struct PBToTvWallParam
{
    std::string decoderIp; // 解码器ip
    int decoderPort; // 解码器端口
    std::string decoderUserName; // 解码器用户名
    std::string decoderPassword; // 解码器密码
    int nDecChannel; // 解码通道
};

/**@fn   <PB_KEY_IMG_CB>
*@brief  <获取关键帧截图的回调定义>
*@param  <userData: 用户数据>
*@param  <pBuf: 图片数据>
*@param  <dwSize: 图片长度>
*@param  <timeStamp: 图片时间戳>
*@return <void>
*/
typedef void (__stdcall *PB_KEY_IMG_CB)(long actionId, void* userData, unsigned char* pBuf, unsigned long dwSize, time_t timeStamp);

/**@struct PB_KEY_IMG_PARAM
*@brief    关键帧图片参数
*/
struct PB_KEY_IMG_PARAM
{
    std::string url; // 关键帧所在片段的URL
    time_t tKeyFrame; // 关键帧时间点
    PB_TOKEN_CB pFunToken; // 获取取流令牌的回调（为空表示不加令牌）
    void* pTokenUserData; // 获取令牌回调用户数据
    PB_KEY_IMG_CB pFunData; // 图片数据回调
    void* pDataUserData; // 图片数据回调用户数据
    PB_KEY_IMG_PARAM()
    {
        tKeyFrame = 0;
        pFunToken = NULL;
        pTokenUserData = NULL;
        pFunData = NULL;
        pDataUserData = NULL;
    }
    ~PB_KEY_IMG_PARAM()
    {
        pFunToken = NULL;
        pTokenUserData = NULL;
        pFunData = NULL;
        pDataUserData = NULL;
    }
    PB_KEY_IMG_PARAM(const PB_KEY_IMG_PARAM& other)
    {
        *this = other;
    }
    PB_KEY_IMG_PARAM& operator=(const PB_KEY_IMG_PARAM& other)
    {
        if (this != &other)
        {
            url = other.url;
            tKeyFrame = other.tKeyFrame;
            pFunToken = other.pFunToken;
            pTokenUserData = other.pTokenUserData;
            pFunData = other.pFunData;
            pDataUserData = other.pDataUserData;
        }
        return *this;
    }
};

/**@struct RECORD_STREAM_PACKET
*@brief    录像码流数据包
*/
struct RECORD_STREAM_PACKET
{
    int nDataLen;
    int nDataType;
    unsigned char* pDataBuffer;

    RECORD_STREAM_PACKET()
        :nDataLen(0)
        ,nDataType(PBDT_DATA)
        ,pDataBuffer(NULL)
    {
    }
    RECORD_STREAM_PACKET(int srcSize, int srcType, unsigned char* pSrcBuf)
        :nDataLen(srcSize)
        ,nDataType(srcType)
        ,pDataBuffer(NULL)
    {
        CopyBuf(pSrcBuf);
    }
    RECORD_STREAM_PACKET(const RECORD_STREAM_PACKET& other)
        :nDataLen(0)
        ,nDataType(PBDT_DATA)
        ,pDataBuffer(NULL)
    {
        *this = other;
    }
    RECORD_STREAM_PACKET& operator=(const RECORD_STREAM_PACKET& other)
    {
        if (this != &other)
        {
            nDataLen = other.nDataLen;
            nDataType = other.nDataType;
            CopyBuf(other.pDataBuffer);
        }
        return *this;
    }
    ~RECORD_STREAM_PACKET()
    {
        SAFE_DELETE_ARRAY(pDataBuffer);
    }
    void CopyBuf(unsigned char* pSrcBuf)
    {
        SAFE_DELETE_ARRAY(pDataBuffer);
        if (pSrcBuf != NULL && nDataLen != 0)
        {
            try
            {
                pDataBuffer = new unsigned char[nDataLen];
                memset(pDataBuffer, 0, nDataLen);
                memcpy_s(pDataBuffer, nDataLen, pSrcBuf, nDataLen);
            }
            catch (...)
            {
            }
        }
    }
};

/**@enum PB_ACTION_ID
* @brief 录像回放操作ID
*/
enum PB_ACTION_ID
{
    //------------------ 录像与标签操作（值同 rlMgr::OPERATION_TYPE 的定义）
    PBA_LABEL_ADD = 0x01,      // 标签：增
    PBA_LABEL_DELETE = 0x02,   // 标签：删
    PBA_LABEL_MODIFY = 0x03,   // 标签：改
    PBA_LABEL_SEARCH,          // 标签：查

    // 需记录：录像起止时间 (lDetailA~lDetailB)
    PBA_RECORD_SEARCH,         // 录像：查
    PBA_RECORD_LOCK,           // 录像：锁  需记录：锁定录像起止时间+锁定时长(tPlay)
    PBA_RECORD_UNLOCK,         // 录像：解锁
    PBA_RECORD_IS_EXIST,       // 录像：查存在

    //------------------ 以下取流播放操作日志在操作回调中记录
    // 录像回放，需记录：（开始/停止/暂停/恢复/倍速/倒放/正放/定位）+录像时间
    PBA_PLAY_START,            // 开始： tPlay是开始播放的时间
    PBA_PLAY_STOP,             // 停止
    PBA_PLAY_PAUSE,            // 暂停
    PBA_PLAY_RESUME,           // 恢复
    PBA_PLAY_SPEED,            // 倍速： lDetailA是播放速度值，见PLAYBACK_SPEED
    PBA_PLAY_BACKWARD,         // 倒放
    PBA_PLAY_FORWARD,          // 正放
    PBA_PLAY_SEEK,             // 定位： tPlay是定位到的时间
    // 开闭声音，需记录：开/闭 （lDetailA的1/0）
    PBA_SOUND,
    // 音量控制，需记录： 音量 (lDetailA)
    PBA_VOLUME,

    //------------------ 
    // 抓图操作 (由于连续抓图会产生多次回调，因此操作日志不在回调中记录)
    PBA_SNAPSHOT,
    // 录像剪辑，需记录：起止时间 (rstXml中，格式见SaveClipResult.xml)
    PBA_SAVE_CLIP,

    //------------------ 以下消息在其他模块中处理
    // 回放上墙，需记录：(开始/停止)监视屏组+监视屏号+录像存储方式 (电视墙模块中记录，不在回放模块内部处理)
    PBA_TVWALL,
};

/**@struct PB_ACTION_RESULT
*@brief    回放操作结果
*/
struct PB_ACTION_RESULT
{
    int actionId;       // 操作序号，参见 PB_ACTION_ID
    bool bSuc;          // 操作是否成功
    time_t tPlay;       // 操作对应的录像时间
    long lDetailA;      // 细节信息A (详见各ID的定义)
    long lDetailB;      // 细节信息B (详见各ID的定义)
    std::string rstXml; // 操作结果xml（抓图、剪辑时需要）
    PB_ACTION_RESULT()
    {
        actionId = 0;
        bSuc = false;
        tPlay = 0;
        lDetailA = 0;
        lDetailB = 0;
    }
};

/**@fn   <PB_ACTION_CB>
*@brief  <回放操作回调（一般用于记录操作日志）>
*@param  <userData: 回调用户数据>
*@param  <idx: 操作的监控点的编号>
*@param  <stRst: 回放操作结果信息>
*@return <void>
*/
typedef void (__stdcall *PB_ACTION_CB)(void* userData, WND_INDEX idx, const PB_ACTION_RESULT& stRst);

/**@struct SPB_RCD_SEARCH_RESULT
*@brief    单路回放的查询结果
*/
struct SPB_RCD_SEARCH_RESULT
{
    long actionId;              // 查询操作ID，用于标识一次查询
    int err;                    // 错误码
    time_t tPartBegin;          // 此段结果对应的查询开始时间
    time_t tPartEnd;            // 此段结果对应的查询结束时间
    RECORD_SEARCH_RESULT_MAP rstMap; // 结果集
    std::string rstXml;         // 结果集
    std::string strExtra;       // 额外数据
    SPB_RCD_SEARCH_RESULT()
    {
        actionId = 0;
        err = 0;
        tPartBegin = playback::INVALID_TIME_VALUE;
        tPartEnd = playback::INVALID_TIME_VALUE;
    }
};

/**@fn   <SPB_SEARCH_CB>
*@brief  <单路回放查询回调>
*@param  <userData: 回调用户数据>
*@param  <idx: 操作的监控点的编号>
*@param  <stRst: 回放操作结果信息>
*@return <void>
*/
typedef void (__stdcall *SPB_SEARCH_CB)(void* userData, const SPB_RCD_SEARCH_RESULT& stRst);

/**@struct SPB_RCD_SEARCH_PARAM
*@brief    单路回放查询参数
*/
struct SPB_RCD_SEARCH_PARAM
{
    long actionId;              // 查询操作ID，用于标识一次查询
    time_t tBegin;              // 查询开始时间
    time_t tEnd;                // 查询结束时间
	time_t tPlay;				  //开始播放的时间
    unsigned int rcdType;       // 查询录像类型
    SPB_SEARCH_CB pRcdFun;      // 查询录像回调
    void* pRcdUser;             // 查询录像回调用户数据
    SPB_RCD_SEARCH_PARAM()
    {
        actionId = 0;
        tBegin = playback::INVALID_TIME_VALUE;
        tEnd = playback::INVALID_TIME_VALUE;
		tPlay = playback::INVALID_TIME_VALUE;
        rcdType = playback::RCD_TYPE_ALL;
        pRcdFun = NULL;
        pRcdUser = NULL;
    }
    ~SPB_RCD_SEARCH_PARAM()
    {
        pRcdFun = NULL;
        pRcdUser = NULL;
    }
    SPB_RCD_SEARCH_PARAM& operator=(const SPB_RCD_SEARCH_PARAM& other)
    {
        if (this != &other)
        {
            actionId = other.actionId;
            tBegin = other.tBegin;
            tEnd = other.tEnd;
			tPlay = other.tPlay;
            rcdType = other.rcdType;
            pRcdFun = other.pRcdFun;
            pRcdUser = other.pRcdUser;
        }
        return *this;
    }
    SPB_RCD_SEARCH_PARAM(const SPB_RCD_SEARCH_PARAM& other)
    {
        *this = other;
    }
};
