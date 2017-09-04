/********************************************************************
	Copyright:  2012-2013 Hikvision Digital Technology Co.,  Ltd. 
	created:	2012/12/05
	filename: 	AlarmType
	file ext:	h
	author:		bianyu
	purpose:	�����������
*********************************************************************/
#pragma once
using namespace std;
//�������͵�cms���壬64λ���ͻ������Ϊ�˲������㣬���¶��屨������,����Ϊ32λ��
//���㱨������İ�λ��������3���ֽڱ�ʾ���������ͣ����һ���ֽڱ�ʾ��������ϸ��
//����һ�����Ա�ʾ24�������ͱ�����ÿ�������¿��Ա�ʾ256��ϸ�ֱ���

//�������Ϳͻ��˶���
namespace Alr_CCType
{
//����������
    const UINT ALRCCTYPE_MAIN_CAMALR     = 0x00020000;  //��ص㱨��
    const UINT ALRCCTYPE_MAIN_IOALR      = 0x00090000;  //IO����
    const UINT ALRCCTYPE_MAIN_ACALR      = 0x00030000;  //�Ž�����
    const UINT ALRCCTYPE_MAIN_PATROL     = 0x00040000;  //Ѳ�鱨��
    const UINT ALRCCTYPE_MAIN_ALRHOST    = 0x00050000;  //������������
    const UINT ALRCCTYPE_MAIN_FIRE       = 0x00060000;  //��������
    const UINT ALRCCTYPE_MAIN_DEALR      = 0x00070000;  //��������
    const UINT ALRCCTYPE_MAIN_PARK       = 0x00080000;  //ͣ��������
    const UINT ALRCCTYPE_MAIN_EXCEPTION  = 0x00010000;  //�쳣����
    const UINT ALRCCTYPE_MAIN_MANUAL     = 0x000A0000;  //�ֶ�����

//����������
    //��ص㱨��
    const UINT ALRCCTYPE_SUB_CAM_LOST         = 0x00020101;   //��Ƶ��ʧ
    const UINT ALRCCTYPE_SUB_CAM_COVER        = 0x00020102;   //��Ƶ�ڵ�
    const UINT ALRCCTYPE_SUB_CAM_MOVING       = 0x00020103;   //�ƶ����
    const UINT ALRCCTYPE_SUB_CAM_CROSS        = 0x00020201;   //��Խ������
    const UINT ALRCCTYPE_SUB_CAM_ENTER        = 0x00020202;   //��������
    const UINT ALRCCTYPE_SUB_CAM_LEAVE        = 0x00020203;   //�뿪����
    const UINT ALRCCTYPE_SUB_CAM_INVADE       = 0x00020204;   //��������
    const UINT ALRCCTYPE_SUB_CAM_TAKEANDPLACE = 0x00020205;   //��Ʒ��ȡ����
    const UINT ALRCCTYPE_SUB_CAM_LINGER       = 0x00020206;   //�ǻ�
    const UINT ALRCCTYPE_SUB_CAM_PARKING      = 0x00020207;   //ͣ��
    const UINT ALRCCTYPE_SUB_CAM_FASTMOVE     = 0x00020208;   //�����ƶ�
    const UINT ALRCCTYPE_SUB_CAM_GATHER       = 0x00020209;   //��Ա�ۼ�
    const UINT ALRCCTYPE_SUB_CAM_LEFT         = 0x0002020A;   //��Ʒ����
    const UINT ALRCCTYPE_SUB_CAM_TAKE         = 0x0002020B;   //��Ʒ��ȡ 
    const UINT ALRCCTYPE_SUB_CAM_CHANGE       = 0x0002020C;   //����ͻ��

    //IO����
    const UINT ALRCCTYPE_SUB_IO = 0x00090001;   

    //�Ž�����
    const UINT ALRCCTYPE_SUB_AC_MULTI_CARD       = 0x00030101; //��һ�������򸱿���˫�ؿ�
    const UINT ALRCCTYPE_SUB_AC_DOPEN_CARD       = 0x00030102; //�ڳ���ʱ��ˢ��
    const UINT ALRCCTYPE_SUB_AC_TEMP_CARD        = 0x00030103; //��ʱ��
    const UINT ALRCCTYPE_SUB_AC_CUSTOMER_CARD    = 0x00030104; //������
    const UINT ALRCCTYPE_SUB_AC_TIME_CARD        = 0x00030105; //���ڿ�
    const UINT ALRCCTYPE_SUB_AC_PATROL_CARD      = 0x00030106; //Ѳ�߿�������
    const UINT ALRCCTYPE_SUB_AC_CC_CLOSE         = 0x00030107; //ˢ�����������
    const UINT ALRCCTYPE_SUB_AC_MASTER_CARD      = 0x00030108; //����
    const UINT ALARM_SUB_TYPE_DCLOSE_CARD        = 0x00030109; //����״̬ˢ��
    const UINT ALRCCTYPE_SUB_AC_WRONG_PWD        = 0x00030201; //�������
    const UINT ALRCCTYPE_SUB_AC_WRONG_CODE       = 0x00030202; //����������
    const UINT ALRCCTYPE_SUB_AC_NEED_CARD        = 0x00030203; //��Ҫ���벻�����뿨��
    const UINT ALRCCTYPE_SUB_AC_WRONG_AUTH       = 0x00030301; //Ȩ�޲���
    const UINT ALRCCTYPE_SUB_AC_WHOL_AUTH        = 0x00030302; //����Ȩ�޲���
    const UINT ALRCCTYPE_SUB_AC_WMA_AUTH         = 0x00030303; //������Ȩ�޶Ա�ʧ��
    const UINT ALRCCTYPE_SUB_AC_WDURA_AUTH       = 0x00030304; //˫�ؿ�Ȩ�޶Ա�ʧ��
    const UINT ALRCCTYPE_SUB_AC_WPATROL_AUTH     = 0x00030305; //Ѳ�߿�Ȩ�޲���
    const UINT ALRCCTYPE_SUB_AC_WCC_AUTH         = 0x00030306; //ˢ���Ӵ���Ȩ�޲���
    const UINT ALRCCTYPE_SUB_AC_WANTI_AUTH       = 0x00030307; //ANTI�ȶ�ʧ��
    const UINT ALRCCTYPE_SUB_AC_WTIME_AUTH       = 0x00030308; //ʱ�������
    const UINT ALRCCTYPE_SUB_AC_CARD_OUTTIME     = 0x00030401; //����ʱЧ�ѹ�
    const UINT ALRCCTYPE_SUB_AC_CARD_NOTEXIST    = 0x00030402; //�޴˿���
    const UINT ALRCCTYPE_SUB_AC_BLACK_LIST       = 0x00030501; //������
    const UINT ALRCCTYPE_SUB_AC_CC_NOPEN         = 0x00030601; //ˢ���Ӵ��벻����
    const UINT ALRCCTYPE_SUB_AC_DLOCK_NOPEN      = 0x00030602; //˫�Ż������޷�����
    const UINT ALRCCTYPE_SUB_AC_FAIL_LOGIN       = 0x00030603; //�п�Ƭ���޷�login �ɹ�
    const UINT ALRCCTYPE_SUB_AC_OPEN_OUTOFTIME   = 0x00030700; //���ų�ʱ
    const UINT ALRCCTYPE_SUB_AC_ILLEAGAL_OPENGATE= 0x00030801; //�Ƿ�����
    const UINT ALRCCTYPE_SUB_AC_GATE_OPEN        = 0x00030901; //����
    const UINT ALRCCTYPE_SUB_AC_CARD_OPEN        = 0x00030902; //ˢ������
    const UINT ALRCCTYPE_SUB_AC_CC_OPEN          = 0x00030903; //ˢ���Ӵ��뿪��
    const UINT ALRCCTYPE_SUB_AC_HARD_OPEN        = 0x00030904; //��ť����
    const UINT ALRCCTYPE_SUB_AC_PATROL_OPEN      = 0x00030906; //Ѳ�߿�����
    const UINT ALRCCTYPE_SUB_AC_SOFT_OPEN        = 0x00030907; //Զ���������
    const UINT ALRCCTYPE_SUB_AC_NORMAL_CLOSEGATE = 0x00030A01; //����
    const UINT ALRCCTYPE_SUB_AC_FORCE_CARD       = 0x00030B01; //в�ȿ�
    const UINT ALRCCTYPE_SUB_AC_FORCE_CODE       = 0x00030B02; //в����
    const UINT ALRCCTYPE_SUB_AC_SECRET_ALARM     = 0x00030B03; //�����ܾ���
    const UINT ALRCCTYPE_SUB_AC_FORCE_INOUT      = 0x00030B04; //в�ȿ��ű���
    const UINT ALRCCTYPE_SUB_AC_RELEASE_ARM      = 0x00030C01; //�������

    //Ѳ�鱨��
    const UINT ALRCCTYPE_SUB_PATROL_EARLY    = 0x00040001;  //��Ѳ
    const UINT ALRCCTYPE_SUB_PATROL_LATE     = 0x00040002;  //��Ѳ
    const UINT ALRCCTYPE_SUB_PATROL_MISSING  = 0x00040003;  //©Ѳ

    //������������
    const UINT ALRCCTYPE_SUB_ARLHOST_AREA    = 0x00050001;  //����������������

    //��������
    const UINT ALRCCTYPE_SUB_FIRE_FIREALR    = 0x00060001;  //��������

    //��������
    const UINT ALRCCTYPE_SUB_DE_ENV          = 0x00070101;  //����������

    //ͣ��������    
    const UINT ALRCCTYPE_SUB_PARK_ILLCAR     = 0x00080001;  //�Ƿ�����
    const UINT ALRCCTYPE_SUB_PARK_BLACKLIST  = 0x00080002;  //������
    const UINT ALRCCTYPE_SUB_PARK_OWE        = 0x00080003;  //Ƿ��

    //�쳣����
    const UINT ALRCCTYPE_SUB_EPT_SVREPT      = 0x00010101;  //�������쳣
    const UINT ALRCCTYPE_SUB_EPT_SVROFFLINE  = 0x00010102;  //����������
    const UINT ALRCCTYPE_SUB_EPT_DEVOFFLINE  = 0x00010201;  //�豸����
    const UINT ALRCCTYPE_SUB_EPT_DEVDISFULL  = 0x00010202;  //Ӳ����
    const UINT ALRCCTYPE_SUB_EPT_DEVEXPT     = 0x00010203;  //�豸�쳣
    const UINT ALRCCTYPE_SUB_EPT_DESTROY     = 0x00010301; //�����ƻ�
    const UINT ALRCCTYPE_SUB_EPT_OFFLINE     = 0x00010302; //װ������
    const UINT ALRCCTYPE_SUB_EPT_BOOT        = 0x00010303; //�俪��
    const UINT ALRCCTYPE_SUB_EPT_REBOOT      = 0x00010304; //��������
    const UINT ALRCCTYPE_SUB_EPT_MEMORY_FULL = 0x00010305; //����������
    const UINT ALRCCTYPE_SUB_EPT_INIT        = 0x00010306; //ϵͳ��ʼ��

    const UINT ALRCCTYPE_SUB_EPT_MANUAL      = 0x000A0001;  //�ֶ�����
}


//������
const CString ALRNAME_SVR_EXPT      = _T("�������쳣");
const CString ALRNAME_SVR_OFFLINE   = _T("����������");

//�豸
const CString ALRNAME_DEV_OFFLINE   = _T("�豸����");
const CString ALRNAME_DEV_DISFULL   = _T("�豸Ӳ����");
const CString ALRNAME_DEV_EXPT      = _T("�豸�쳣");

//�Ž� 
const CString ALRNAME_DEV_AC_DESTROY     = _T("�����ƻ�");
const CString ALRNAME_DEV_AC_OFFLINE     = _T("װ������");
const CString ALRNAME_DEV_AC_BOOT        = _T("�俪��");
const CString ALRNAME_DEV_AC_REBOOT      = _T("��������");
const CString ALRNAME_DEV_AC_MEMORY_FULL = _T("����������");
const CString ALRNAME_DEV_AC_INIT        = _T("ϵͳ��ʼ��");

//��ص�
const CString ALRNAME_CAM_LOST         = _T("��Ƶ��ʧ����");
const CString ALRNAME_CAM_COVER        = _T("��Ƶ�ڵ�����");
const CString ALRNAME_CAM_MOVING       = _T("�ƶ���ⱨ��");
const CString ALRNAME_CAM_CROSS        = _T("��Խ������");
const CString ALRNAME_CAM_ENTER        = _T("��������");
const CString ALRNAME_CAM_LEAVE        = _T("�뿪����");
const CString ALRNAME_CAM_INVADE       = _T("��������");
const CString ALRNAME_CAM_TAKEANDPLACE = _T("��Ʒ��ȡ����");
const CString ALRNAME_CAM_LINGER       = _T("�ǻ�");
const CString ALRNAME_CAM_PARKING      = _T("ͣ��");
const CString ALRNAME_CAM_FASTMOVE     = _T("�����ƶ�");
const CString ALRNAME_CAM_GATHER       = _T("��Ա�ۼ�");
const CString ALRNAME_CAM_LEFT         = _T("��Ʒ����");
const CString ALRNAME_CAM_TAKE         = _T("��Ʒ��ȡ");
const CString ALRNAME_CAM_CHANGE       = _T("����ͻ��");
//IO
const CString ALRNAME_IO_IOINALR       = _T("IO���뱨��");

//�Ž�
const CString ALRNAME_AC_MULTI_CARD       = _T("��һ�������򸱿���˫�ؿ�");
const CString ALRNAME_AC_DOPEN_CARD       = _T("�ڳ���ʱ��ˢ��");
const CString ALRNAME_AC_TEMP_CARD        = _T("��ʱ��");
const CString ALRNAME_AC_CUSTOMER_CARD    = _T("������");
const CString ALRNAME_AC_TIME_CARD        = _T("���ڿ�");
const CString ALRNAME_AC_PATROL_CARD      = _T("Ѳ�߿�������");
const CString ALRNAME_AC_CC_CLOSE         = _T("ˢ�����������");
const CString ALRNAME_AC_MASTER_CARD      = _T("����");
const CString ALRNAME_AC_DCLOSE_CARD      = _T("����״̬ˢ��");
const CString ALRNAME_AC_WRONG_PWD        = _T("�������");
const CString ALRNAME_AC_WRONG_CODE       = _T("����������");
const CString ALRNAME_AC_NEED_CARD        = _T("��Ҫ���벻�����뿨��");
const CString ALRNAME_AC_WRONG_AUTH       = _T("Ȩ�޲���");
const CString ALRNAME_AC_WHOL_AUTH        = _T("����Ȩ�޲���");
const CString ALRNAME_AC_WMA_AUTH         = _T("������Ȩ�޶Ա�ʧ��");
const CString ALRNAME_AC_WDURA_AUTH       = _T("˫�ؿ�Ȩ�޶Ա�ʧ��");
const CString ALRNAME_AC_WPATROL_AUTH     = _T("Ѳ�߿�Ȩ�޲���");
const CString ALRNAME_AC_WCC_AUTH         = _T("ˢ���Ӵ���Ȩ�޲���");
const CString ALRNAME_AC_WANTI_AUTH       = _T("ANTI�ȶ�ʧ��");
const CString ALRNAME_AC_WTIME_AUTH       = _T("ʱ�������");
const CString ALRNAME_AC_CARD_OUTTIME     = _T("����ʱЧ�ѹ�");
const CString ALRNAME_AC_CARD_NOTEXIST    = _T("�޴˿���");
const CString ALRNAME_AC_BLACK_LIST       = _T("������");
const CString ALRNAME_AC_CC_NOPEN         = _T("ˢ���Ӵ��벻����");
const CString ALRNAME_AC_DLOCK_NOPEN      = _T("˫�Ż������޷�����");
const CString ALRNAME_AC_FAIL_LOGIN       = _T("�޷���½");
const CString ALRNAME_AC_OPEN_OUTOFTIME   = _T("�ų�������");
const CString ALRNAME_AC_ILLEAGAL_OPENGATE= _T("�ű���������");
const CString ALRNAME_AC_GATE_OPEN        = _T("����");
const CString ALRNAME_AC_CARD_OPEN        = _T("ˢ������");
const CString ALRNAME_AC_CC_OPEN          = _T("ˢ���Ӵ��뿪��");
const CString ALRNAME_AC_HARD_OPEN        = _T("��ť����");
const CString ALRNAME_AC_PATROL_OPEN      = _T("Ѳ�߿�����");
const CString ALRNAME_AC_SOFT_OPEN        = _T("Զ���������");
const CString ALRNAME_AC_NORMAL_CLOSEGATE = _T("����");
const CString ALRNAME_AC_FORCE_CARD       = _T("в�ȿ�");
const CString ALRNAME_AC_FORCE_CODE       = _T("в����");
const CString ALRNAME_AC_SECRET_ALARM     = _T("�����ܾ���");
const CString ALRNAME_AC_FORCE_INOUT      = _T("в�ȿ��ű���");
const CString ALRNAME_AC_RELEASE_ARM      = _T("�������");



//Ѳ�鱨��
const CString ALRNAME_PATROL_EARLY    = _T("��Ѳ");
const CString ALRNAME_PATROL_LATE     = _T("��Ѳ");
const CString ALRNAME_PATROL_MISSING  = _T("©Ѳ");

//������������
const CString ALRNAME_ARLHOST_AREA    = _T("��������");

//��������
const CString ALRNAME_FIRE_FIREALR    = _T("��������");

//��������
const CString ALRNAME_DE_ENV          = _T("����������");

//ͣ��������    
const CString ALRNAME_PARK_ILLCAR     = _T("�Ƿ�����");
const CString ALRNAME_PARK_BLACKLIST  = _T("������");
const CString ALRNAME_PARK_OWE        = _T("Ƿ��");

const CString ALRNAME_MANUAL     = _T("�ֶ�����");

typedef struct stu_AlarmInputInfo 
{
    UINT uAlrCCMainType;     //�ͻ��˶��屨������ ������
    UINT uAlrCCSubType;      //�ͻ��˶��屨������ ����ϸ��
    CString strName;      //������������

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
*    Description:   ��ʼ���������ͱ�
*    Input:         
*    Output:         
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
    void __InitAlrType();

/*******************************************************************************
*    Function:      __UnInitAlrType
*    Description:   �ͷű������ͱ�Ŀռ�
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
*    Description:   ���ݱ���������ID��ȡ��������
*    Input:         uTypeID -- ��������ID(CC���������)
*    Output:        strName -- ������������
*    Return:		
*	 author:		bianyu	
*	 Remark: 		    
*******************************************************************************/
    void AlrType_GetTypeNameByTypeID(CString &strName,UINT uTypeID);
};
