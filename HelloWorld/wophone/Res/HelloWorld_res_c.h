//------------------------------------------------------------------------------
//                      HelloWorld_Res_c.h
//              ��Դ������ת���ļ����ݶ����ļ�
//
//
//        Copyright (C) Tranzda CORPORATION
//
//---�ȱ�������Ϣ��---
//   ����������: TR3C.exe 
//   �������汾: TG3 ��Դ������ �汾V1.5  Build 94
//
//---��ע���---
// ���棺δ�������κ��˲�׼�����޸Ĵ��ļ�!!!�������Ը�!
//
//------------------------------------------------------------------------------
#include "helloworld_res_h.h" //���Ͷ���ͷ�ļ� 
#ifndef WIN32 
//#pragma diag_remark 1296 
#endif
#if 11<RES_VERSION 
#error Resource file version too low!Must be compiled with higher version TR3C.
#endif


/************************************************************
*     Language:CHS
*************************************************************/


const ResProjectType  HELLOW_project=
{ 
  320,	//screenWidth 
  480,	//screenHeight 
  16500,	//screenDPI 
};


/*-------------------------------------------------------------
*     IDΪHELLOW_ID_Form1002���������
------------------------------------------------------------*/


/*"Main"*/
const TUChar HELLOW_Form1002TitleStr[]={0x004D,0x0061,0x0069,0x006E,0x0000};

const ResWindowType HELLOW_Form1002 =
{
  {//��Դ����ͷ������
    HELLOW_ID_Form1002,//��ԴID
    RES_CLASS_FORM,//��Դ����ΪFORM(����)����
    sizeof(ResWindowType),//��Դ��С
    -1,//����ԴID(����û�й�Ϊ-1)
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//ControlAttrType����
    0,//Enabled,(nouse here)
    0,//Visibled,(nouse here)
    0,//Ctl3D,,(nouse here)
    0,//TabStop,(nouse here)
    0,//ReadOnly,(nouse here)
    0,//ImeEnable,(nouse here)
    0,//WordWrap,(nouse here)
    0,//TopLeftIsLock,(nouse here)
    0,//Check,(nouse here)
    0,//MultiLine,(nouse here) 
    0,//AutoSize,(nouse here)
    0,//Modal, 
    0,//Numeric ,Field Use
    0,//AutoShift,Field Use
    0,//DynamicSize,Field Use
    0,//UnderLine,Field Use
    1,//BIClose
    0,//HasStatusBar
    0,//BIAction
    0,//BIMaximize
    0,//ForceShowTitle
    0,//Graphical,(nouse here)
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },
  {//PanelAttr
    2,//HScrollMode,0-auto,1-enable,2-disable
    0,//VScrollMode,0-auto,1-enable,2-disable
  },
  0X3, // BackColor
  0X2, // ForeColor
  {{0, 24}, {320, 456}}, // RectangleType windowBounds
  0, // �ؼ�����
  {//ResWindowExAttrType
    0,//closeBtnStyle
    0,//actionBtnStyle
    1,//DisableSystemStatusBar
    1,//fullScreen
    0,//rotateMode
  },
  (TUChar *)HELLOW_Form1002TitleStr, //�����ı�������!��
  NULL, // �رհ�ť���֣���ǰΪ�գ���
  NULL, // action button text = null
  0, //CharSet
  stdFont,//Font
  -1, //MainMenuID(-1Ϊû�����˵�)
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // ��������ģʽ
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // �رն���ģʽ
  NULL, // ָ��ؼ��б�(û�пؼ�������Ϊ�գ�)
  0, // ��ת�ο����������
  NULL // ������ת�ο���(��)
};//����HELLOW_Form1002��Դ���ݳ�������
const ResourceLangRegisterEntry HELLOW_CHS_Resource[] = 
{
  {kProjectRscType,0,(void*)&HELLOW_project,sizeof(HELLOW_project)}   
  ,{kWindowRscType,HELLOW_ID_Form1002,(void*)&HELLOW_Form1002,sizeof(HELLOW_Form1002)}   
};

const ResourceLangRegisterEntry2  HELLOW_CHS_ResourceEntry = 
{
  tgresource_tag,
  11,//res version
  0,//subVersionValue
  0,//reserved1
  0,//reserved2
  HELLOW_CHS_Resource
};


/************************************************************
*     Language:ENU
*************************************************************/


const ResProjectType  HELLOW_ENU_project=
{ 
  320,	//screenWidth 
  480,	//screenHeight 
  16500,	//screenDPI 
};


/*-------------------------------------------------------------
*     IDΪHELLOW_ID_Form1002���������
------------------------------------------------------------*/


/*"Main"*/
const TUChar HELLOW_ENU_Form1002TitleStr[]={0x004D,0x0061,0x0069,0x006E,0x0000};

const ResWindowType HELLOW_ENU_Form1002 =
{
  {//��Դ����ͷ������
    HELLOW_ID_Form1002,//��ԴID
    RES_CLASS_FORM,//��Դ����ΪFORM(����)����
    sizeof(ResWindowType),//��Դ��С
    -1,//����ԴID(����û�й�Ϊ-1)
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//ControlAttrType����
    0,//Enabled,(nouse here)
    0,//Visibled,(nouse here)
    0,//Ctl3D,,(nouse here)
    0,//TabStop,(nouse here)
    0,//ReadOnly,(nouse here)
    0,//ImeEnable,(nouse here)
    0,//WordWrap,(nouse here)
    0,//TopLeftIsLock,(nouse here)
    0,//Check,(nouse here)
    0,//MultiLine,(nouse here) 
    0,//AutoSize,(nouse here)
    0,//Modal, 
    0,//Numeric ,Field Use
    0,//AutoShift,Field Use
    0,//DynamicSize,Field Use
    0,//UnderLine,Field Use
    1,//BIClose
    0,//HasStatusBar
    0,//BIAction
    0,//BIMaximize
    0,//ForceShowTitle
    0,//Graphical,(nouse here)
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },
  {//PanelAttr
    2,//HScrollMode,0-auto,1-enable,2-disable
    0,//VScrollMode,0-auto,1-enable,2-disable
  },
  0X3, // BackColor
  0X2, // ForeColor
  {{0, 24}, {320, 456}}, // RectangleType windowBounds
  0, // �ؼ�����
  {//ResWindowExAttrType
    0,//closeBtnStyle
    0,//actionBtnStyle
    0,//DisableSystemStatusBar
    1,//fullScreen
    0,//rotateMode
  },
  (TUChar *)HELLOW_ENU_Form1002TitleStr, //�����ı�������!��
  NULL, // �رհ�ť���֣���ǰΪ�գ���
  NULL, // action button text = null
  0, //CharSet
  stdFont,//Font
  -1, //MainMenuID(-1Ϊû�����˵�)
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // ��������ģʽ
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // �رն���ģʽ
  NULL, // ָ��ؼ��б�(û�пؼ�������Ϊ�գ�)
  0, // ��ת�ο����������
  NULL // ������ת�ο���(��)
};//����HELLOW_ENU_Form1002��Դ���ݳ�������
const ResourceLangRegisterEntry HELLOW_ENU_Resource[] = 
{
  {kProjectRscType,0,(void*)&HELLOW_ENU_project,sizeof(HELLOW_ENU_project)}   
  ,{kWindowRscType,HELLOW_ID_Form1002,(void*)&HELLOW_ENU_Form1002,sizeof(HELLOW_ENU_Form1002)}   
};

const ResourceLangRegisterEntry2  HELLOW_ENU_ResourceEntry = 
{
  tgresource_tag,
  11,//res version
  0,//subVersionValue
  0,//reserved1
  0,//reserved2
  HELLOW_ENU_Resource
};

//��Դ����
#define TG_RESOURCE_DEFINE   \
{SYS_LANGUAGE_CHS,sizeof( HELLOW_CHS_Resource )/ sizeof(ResourceLangRegisterEntry), &HELLOW_CHS_ResourceEntry},   \
{SYS_LANGUAGE_ENU,sizeof( HELLOW_ENU_Resource )/ sizeof(ResourceLangRegisterEntry), &HELLOW_ENU_ResourceEntry},   
