#include "TypeMeter.h"

//����洢���б��浱ǰ���е�������һ������(ռǰ4ҳ 4*2*128 )
//�͵�ǰ�й����򡢵�ǰ�й����򡢵�ǰ���ڡ�һ����������������������������60���ӡ�120�ֽڣ����ޱ���(��4ҳ 4*2*128)
/***********************************************/

// ��һƬ24C512�д洢�����ݣ�
// 1����ǰ���е�������������������ʱ�䣻
// 2����ʷ���1-12���µ����е�������������������ʱ��
// 3���ڼ��ա������ա����ڡ�ʱ�εȵ�����
// 4��������Ȳ���
#define CMon_EC_Pp0                     0
#define	CMon_EC_Pn0                     CMon_EC_Pp0+5
#define CMon_EC_Qp0                     CMon_EC_Pn0+5
#define CMon_EC_Qn0                     CMon_EC_Qp0+5
#define CMon_EC_Pp1                     CMon_EC_Qn0+5
#define	CMon_EC_Pn1                     CMon_EC_Pp1+5
#define CMon_EC_Qp1                     CMon_EC_Pn1+5
#define CMon_EC_Qn1                     CMon_EC_Qp1+5
#define CMon_EC_Pp2                     CMon_EC_Qn1+5
#define	CMon_EC_Pn2                     CMon_EC_Pp2+5
#define CMon_EC_Qp2                     CMon_EC_Pn2+5
#define CMon_EC_Qn2                     CMon_EC_Qp2+5
#define CMon_EC_Pp3                     CMon_EC_Qn2+5
#define	CMon_EC_Pn3                     CMon_EC_Pp3+5
#define CMon_EC_Qp3                     CMon_EC_Pn3+5
#define CMon_EC_Qn3                     CMon_EC_Qp3+5
#define CMon_EC_Pp4                     CMon_EC_Qn3+5
#define	CMon_EC_Pn4                     CMon_EC_Pp4+5
#define CMon_EC_Qp4                     CMon_EC_Pn4+5
#define CMon_EC_Qn4                     CMon_EC_Qp4+5
#define CMon_EC_Pp5                     CMon_EC_Qn4+5
#define	CMon_EC_Pn5                     CMon_EC_Pp5+5
#define CMon_EC_Qp5                     CMon_EC_Pn5+5
#define CMon_EC_Qn5                     CMon_EC_Qp5+5
#define CMon_EC_Pp6                     CMon_EC_Qn5+5
#define	CMon_EC_Pn6                     CMon_EC_Pp6+5
#define CMon_EC_Qp6                     CMon_EC_Pn6+5
#define CMon_EC_Qn6                     CMon_EC_Qp6+5
#define CMon_EC_Pp7                     CMon_EC_Qn6+5
#define	CMon_EC_Pn7                     CMon_EC_Pp7+5
#define CMon_EC_Qp7                     CMon_EC_Pn7+5
#define CMon_EC_Qn7                     CMon_EC_Qp7+5
#define CMon_EC_Q01                     CMon_EC_Qn7+5
#define	CMon_EC_Q02                     CMon_EC_Q01+5
#define CMon_EC_Q03                     CMon_EC_Q02+5
#define CMon_EC_Q04                     CMon_EC_Q03+5
#define CMon_EC_Q11                     CMon_EC_Q04+5
#define	CMon_EC_Q12                     CMon_EC_Q11+5
#define CMon_EC_Q13                     CMon_EC_Q12+5
#define CMon_EC_Q14                     CMon_EC_Q13+5
#define CMon_EC_Q21                     CMon_EC_Q14+5
#define	CMon_EC_Q22                     CMon_EC_Q21+5
#define CMon_EC_Q23                     CMon_EC_Q22+5
#define CMon_EC_Q24                     CMon_EC_Q23+5
#define CMon_EC_Q31                     CMon_EC_Q24+5
#define	CMon_EC_Q32                     CMon_EC_Q31+5
#define CMon_EC_Q33                     CMon_EC_Q32+5
#define CMon_EC_Q34                     CMon_EC_Q33+5
#define CMon_EC_Q41                     CMon_EC_Q34+5
#define	CMon_EC_Q42                     CMon_EC_Q41+5
#define CMon_EC_Q43                     CMon_EC_Q42+5
#define CMon_EC_Q44                     CMon_EC_Q43+5
#define CMon_EC_Q51                     CMon_EC_Q44+5
#define	CMon_EC_Q52                     CMon_EC_Q51+5
#define CMon_EC_Q53                     CMon_EC_Q52+5
#define CMon_EC_Q54                     CMon_EC_Q53+5
#define CMon_EC_Q61                     CMon_EC_Q54+5
#define	CMon_EC_Q62                     CMon_EC_Q61+5
#define CMon_EC_Q63                     CMon_EC_Q62+5
#define CMon_EC_Q64                     CMon_EC_Q63+5
#define CMon_EC_Q71                     CMon_EC_Q64+5
#define	CMon_EC_Q72                     CMon_EC_Q71+5
#define CMon_EC_Q73                     CMon_EC_Q72+5
#define CMon_EC_Q74                     CMon_EC_Q73+5  //������ַ:0x0140

#define CMon_DAY0                       CMon_EC_Q74+5  
#define CDay_HOUR0                      CMon_DAY0+5
#define CDay_InvertVal0                 CDay_HOUR0+5
#define CDay_InvertTime0                CDay_InvertVal0+5
#define CDay_TrendVal0                  CDay_InvertTime0+5
#define CDay_TrendTime0                 CDay_TrendVal0+5

#define CMon_DAY1                       CDay_TrendTime0+5  
#define CDay_HOUR1                      CMon_DAY1+5
#define CDay_InvertVal1                 CDay_HOUR1+5
#define CDay_InvertTime1                CDay_InvertVal1+5
#define CDay_TrendVal1                  CDay_InvertTime1+5
#define CDay_TrendTime1                 CDay_TrendVal1+5

#define CMon_DAY2                       CDay_TrendTime1+5  
#define CDay_HOUR2                      CMon_DAY2+5
#define CDay_InvertVal2                 CDay_HOUR2+5
#define CDay_InvertTime2                CDay_InvertVal2+5
#define CDay_TrendVal2                  CDay_InvertTime2+5
#define CDay_TrendTime2                 CDay_TrendVal2+5

#define CMon_DAY3                       CDay_TrendTime2+5  
#define CDay_HOUR3                      CMon_DAY3+5
#define CDay_InvertVal3                 CDay_HOUR3+5
#define CDay_InvertTime3                CDay_InvertVal3+5
#define CDay_TrendVal3                  CDay_InvertTime3+5
#define CDay_TrendTime3                 CDay_TrendVal3+5

#define CMon_DAY4                       CDay_TrendTime3+5  
#define CDay_HOUR4                      CMon_DAY4+5
#define CDay_InvertVal4                 CDay_HOUR4+5
#define CDay_InvertTime4                CDay_InvertVal4+5
#define CDay_TrendVal4                  CDay_InvertTime4+5
#define CDay_TrendTime4                 CDay_TrendVal4+5

#define CMon_DAY5                       CDay_TrendTime4+5  
#define CDay_HOUR5                      CMon_DAY5+5
#define CDay_InvertVal5                 CDay_HOUR5+5
#define CDay_InvertTime5                CDay_InvertVal5+5
#define CDay_TrendVal5                  CDay_InvertTime5+5
#define CDay_TrendTime5                 CDay_TrendVal5+5

#define CMon_DAY6                       CDay_TrendTime5+5  
#define CDay_HOUR6                      CMon_DAY6+5
#define CDay_InvertVal6                 CDay_HOUR6+5
#define CDay_InvertTime6                CDay_InvertVal6+5
#define CDay_TrendVal6                  CDay_InvertTime6+5
#define CDay_TrendTime6                 CDay_TrendVal6+5

#define CMon_DAY7                       CDay_TrendTime6+5  
#define CDay_HOUR7                      CMon_DAY7+5
#define CDay_InvertVal7                 CDay_HOUR7+5
#define CDay_InvertTime7                CDay_InvertVal7+5
#define CDay_TrendVal7                  CDay_InvertTime7+5
#define CDay_TrendTime7                 CDay_TrendVal7+5

#define	ClockAdj			CDay_TrendTime7+4	//��2��//������ַ:0x088D

//�¼���������ΪHEX��
#define	EPhFail_Valve		          ClockAdj+6		          //ʧѹ��ʼ��ֵ(3)			yyy.y V 
#define AT7022ChkSum		          EPhFail_Valve+7		//7022У������У���(4)		//ATChk		//V1000
#define AT7022ChkSum2		          AT7022ChkSum+6		//7022eУ������У���2(4)		//ATChk		//V1000

#define IEC_LINK_ADDR                    ClockAdj+6      //2
#define IEC_COMM_ADDR                    IEC_LINK_ADDR+4  //2
#define	LoadRecord_Time		         IEC_COMM_ADDR+4 //����ȥ��ʱ�䣬ָ���¼
#define	RandRecord_Time                  LoadRecord_Time+10 //˲ʱ����
#define	FrzdRecord_Time                  RandRecord_Time+10  //�ն���
#define	ShrpdRecord_Time                 FrzdRecord_Time+10 //���㶳��
#define	MonthdRecord_Time                ShrpdRecord_Time+10  //�����ն���

#define	CH0_PAN_EVT_PT                   MonthdRecord_Time+10
#define	CH0_PBN_EVT_PT                   CH0_PAN_EVT_PT+3
#define	CH0_PCN_EVT_PT                   CH0_PBN_EVT_PT+3
#define	CH0_PTD_EVT_PT                   CH0_PCN_EVT_PT+3
#define	CH0_CLR_EVT_PT                   CH0_PCN_EVT_PT+3

#define	CH1_PAN_EVT_PT                   CH0_CLR_EVT_PT+3
#define	CH1_PBN_EVT_PT                   CH1_PAN_EVT_PT+3
#define	CH1_PCN_EVT_PT                   CH1_PBN_EVT_PT+3
#define	CH1_PTD_EVT_PT                   CH1_PCN_EVT_PT+3
#define	CH1_CLR_EVT_PT                   CH1_PCN_EVT_PT+3

#define	CH2_PAN_EVT_PT                   CH1_CLR_EVT_PT+3
#define	CH2_PBN_EVT_PT                   CH2_PAN_EVT_PT+3
#define	CH2_PCN_EVT_PT                   CH2_PBN_EVT_PT+3
#define	CH2_PTD_EVT_PT                   CH2_PCN_EVT_PT+3
#define	CH2_CLR_EVT_PT                   CH2_PCN_EVT_PT+3

#define	CH3_PAN_EVT_PT                   CH2_CLR_EVT_PT+3
#define	CH3_PBN_EVT_PT                   CH3_PAN_EVT_PT+3
#define	CH3_PCN_EVT_PT                   CH3_PBN_EVT_PT+3
#define	CH3_PTD_EVT_PT                   CH3_PCN_EVT_PT+3
#define	CH3_CLR_EVT_PT                   CH3_PCN_EVT_PT+3

#define	CH4_PAN_EVT_PT                   CH3_CLR_EVT_PT+3
#define	CH4_PBN_EVT_PT                   CH4_PAN_EVT_PT+3
#define	CH4_PCN_EVT_PT                   CH4_PBN_EVT_PT+3
#define	CH4_PTD_EVT_PT                   CH4_PCN_EVT_PT+3
#define	CH4_CLR_EVT_PT                   CH4_PCN_EVT_PT+3

#define	CH5_PAN_EVT_PT                   CH4_CLR_EVT_PT+3
#define	CH5_PBN_EVT_PT                   CH5_PAN_EVT_PT+3
#define	CH5_PCN_EVT_PT                   CH5_PBN_EVT_PT+3
#define	CH5_PTD_EVT_PT                   CH5_PCN_EVT_PT+3
#define	CH5_CLR_EVT_PT                   CH5_PCN_EVT_PT+3

#define	CH6_PAN_EVT_PT                   CH5_CLR_EVT_PT+3
#define	CH6_PBN_EVT_PT                   CH6_PAN_EVT_PT+3
#define	CH6_PCN_EVT_PT                   CH6_PBN_EVT_PT+3
#define	CH6_PTD_EVT_PT                   CH6_PCN_EVT_PT+3
#define	CH6_CLR_EVT_PT                   CH6_PCN_EVT_PT+3

#define	CH7_PAN_EVT_PT                   CH6_CLR_EVT_PT+3
#define	CH7_PBN_EVT_PT                   CH7_PAN_EVT_PT+3
#define	CH7_PCN_EVT_PT                   CH7_PBN_EVT_PT+3
#define	CH7_PTD_EVT_PT                   CH7_PCN_EVT_PT+3
#define	CH7_CLR_EVT_PT                   CH7_PCN_EVT_PT+3

#define ErrorRegAddr			 E2P_PGLEN-0x800

#define E2P_PGLEN		         0x1000//0x0B00//0xAAA//0x1554		//���ݱ���ҳ����

#define E2ONE_RECORD_LEN                 54
#define MONTH_RECORD_NUM                 12
#define E2ONE_RECORD_SIZE                60
#define MONTH_RECORD_SIZE                (MONTH_RECORD_NUM*E2ONE_RECORD_SIZE)

#define RAND_RECORD_NUM                   3
#define RAND_RECORD_SIZE                (RAND_RECORD_NUM*E2ONE_RECORD_SIZE)

#define MONTH_DATA_ADDR                  0
#define RAND_DATA_ADDR                   0x1680

#define CH0_PAN_EVT_ADDR                RAND_DATA_ADDR+0x05A0
#define CH0_PBN_EVT_ADDR                CH0_PAN_EVT_ADDR+840
#define CH0_PCN_EVT_ADDR                CH0_PBN_EVT_ADDR+840
#define CH0_PTD_EVT_ADDR                CH0_PCN_EVT_ADDR+840
#define CH0_CLR_ADDR                    CH0_PTD_EVT_ADDR+440

#define CH1_PAN_EVT_ADDR                CH0_CLR_ADDR+440
#define CH1_PBN_EVT_ADDR                CH1_PAN_EVT_ADDR+840
#define CH1_PCN_EVT_ADDR                CH1_PBN_EVT_ADDR+840
#define CH1_PTD_EVT_ADDR                CH1_PCN_EVT_ADDR+840
#define CH1_CLR_ADDR                    CH1_PTD_EVT_ADDR+440

#define CH2_PAN_EVT_ADDR                CH1_CLR_ADDR+440
#define CH2_PBN_EVT_ADDR                CH2_PAN_EVT_ADDR+840
#define CH2_PCN_EVT_ADDR                CH2_PBN_EVT_ADDR+840
#define CH2_PTD_EVT_ADDR                CH2_PCN_EVT_ADDR+840
#define CH2_CLR_ADDR                    CH2_PTD_EVT_ADDR+440

#define CH3_PAN_EVT_ADDR                CH2_CLR_ADDR+440
#define CH3_PBN_EVT_ADDR                CH3_PAN_EVT_ADDR+840
#define CH3_PCN_EVT_ADDR                CH3_PBN_EVT_ADDR+840
#define CH3_PTD_EVT_ADDR                CH3_PCN_EVT_ADDR+840
#define CH3_CLR_ADDR                    CH3_PTD_EVT_ADDR+440

#define CH4_PAN_EVT_ADDR                CH3_CLR_ADDR+440
#define CH4_PBN_EVT_ADDR                CH4_PAN_EVT_ADDR+840
#define CH4_PCN_EVT_ADDR                CH4_PBN_EVT_ADDR+840
#define CH4_PTD_EVT_ADDR                CH4_PCN_EVT_ADDR+840
#define CH4_CLR_ADDR                    CH4_PTD_EVT_ADDR+440

#define CH5_PAN_EVT_ADDR                CH4_CLR_ADDR+440
#define CH5_PBN_EVT_ADDR                CH5_PAN_EVT_ADDR+840
#define CH5_PCN_EVT_ADDR                CH5_PBN_EVT_ADDR+840
#define CH5_PTD_EVT_ADDR                CH5_PCN_EVT_ADDR+840
#define CH5_CLR_ADDR                    CH5_PTD_EVT_ADDR+440

#define CH6_PAN_EVT_ADDR                CH5_CLR_ADDR+440
#define CH6_PBN_EVT_ADDR                CH6_PAN_EVT_ADDR+840
#define CH6_PCN_EVT_ADDR                CH6_PBN_EVT_ADDR+840
#define CH6_PTD_EVT_ADDR                CH6_PCN_EVT_ADDR+840
#define CH6_CLR_ADDR                    CH6_PTD_EVT_ADDR+440

#define CH7_PAN_EVT_ADDR                CH6_CLR_ADDR+440
#define CH7_PBN_EVT_ADDR                CH7_PAN_EVT_ADDR+840
#define CH7_PCN_EVT_ADDR                CH7_PBN_EVT_ADDR+840
#define CH7_PTD_EVT_ADDR                CH7_PCN_EVT_ADDR+840
#define CH7_CLR_ADDR                    CH7_PTD_EVT_ADDR+440

#define E2END_DATA_ADDR                 (CH7_CLR_ADDR+440)


#define ONE_RECORD_LEN                   54
#define LOAD_RECORD_NUM                  96
#define ONE_RECORD_SIZE                  64
#define LOAD_RECORD_SIZE                 (LOAD_RECORD_NUM*ONE_RECORD_SIZE)

#define DAY_RECORD_NUM                   40
#define DAY_RECORD_SIZE                  (DAY_RECORD_NUM*ONE_RECORD_SIZE)

#define HOUR_RECORD_NUM                  264
#define HOUR_RECORD_SIZE                 (HOUR_RECORD_NUM*ONE_RECORD_SIZE)


//FLASH
#define LOAD_DATA_ADDR                   0
#define DAY_DATA_ADDR                    0xC000 //���ɼ�¼��48k�ռ�
#define HOUR_DATA_ADDR                  (0xC000+0x5000) //20k�ռ�
#define END_DATA_ADDR                  (HOUR_DATA_ADDR+0x21000) //132K�ռ�


#define FlashChip		YesCheck

///////////   FLASH	//ǰ300ҳΪ���ɼ�¼
#if (FlashChip == YesCheck)
#define	Mon_Data_Addr	 0x25800//0x19000	//(1840)��ҳ��
#else 
#define	Mon_Data_Addr	 0x7000///0x1554//0x19000	//(1840)��ҳ��
#endif
#define	Tamper_Data_Addr	 Mon_Data_Addr + 0xA00	//(6000)



#define FlashAT45DB		NoCheck		//ATMEL��AT25DF041Aϵ��оƬ AT26DF081��AT26DF161
#define FlashAT161Series	YesCheck	//ATMEL��AT45161оƬ ����2M�ֽ�

//#define GeneralLoadCurveSta		0x00000000		//0
//#define GeneralLoadCurveEnd		0x00090000		//384K  ��ͨ�������߷�Χ��
//#define GeneralMonCurveSta		0x00090000		//0
//#define GeneralMonCurveEnd		0x000A0000		//64K  ��ʷ���ݷ�Χ��
//#define GeneralTamperCurveSta	0x000A0000		//0
//#define GeneralTamperCurveEnd	0x000B0000		//64K  �¼���¼��Χ��

//------------------DLMS Profile tab���ݴ洢----------------
#define EventLog1Page					0x00000000
///#define EventLog1Page					GeneralTamperCurveEnd			//�¼�1��¼��ҳ��(6)
#define EventLog2Page					EventLog1Page+6*1						//�¼�2��¼��ҳ��(6)
#define EventLog3Page					EventLog1Page+6*2						//�¼�3��¼��ҳ��(6)
#define EventLog4Page					EventLog1Page+6*3						//�¼�4��¼��ҳ��(6)
#define EventLog5Page					EventLog1Page+6*4						//�¼�5��¼��ҳ��(6)
#define EventLog6Page					EventLog1Page+6*5						//�¼�6��¼��ҳ��(6)
#define EventLog7Page					EventLog1Page+6*6						//�¼�7��¼��ҳ��(6)
#define EventLog8Page					EventLog1Page+6*7						//�¼�8��¼��ҳ��(6)
#define EventLog9Page					EventLog1Page+6*8						//�¼�9��¼��ҳ��(6)
#define EventLog10Page					EventLog1Page+6*9						//�¼�10��¼��ҳ��(6)
#define EventLog11Page					EventLog1Page+6*10					//�¼�11��¼��ҳ��(6)

#define Billing_period1Page				EventLog11Page+6*1				//�˵���¼1��ҳ��(6)		//12���½���
#define Billing_period2Page				EventLog11Page+6*2			//�˵���¼1��ҳ��(20)		//31�춳��
#define Load_profile1Page				EventLog11Page+6*3			//��������1��ҳ��(20)		
#define Load_profile2Page				Load_profile1Page+40				//��������1��ҳ��(20)	
#define PowerQuality_profilePage			Load_profile2Page+6				//��������2��ҳ��(200)		

#define Profile_Page_end				PowerQuality_profilePage+40

#define GeneralMonCurveSta		Profile_Page_end		//0
#define GeneralMonCurveEnd		Profile_Page_end+0x10000		//64K  ��ʷ���ݷ�Χ��
#define GeneralTamperCurveSta	GeneralMonCurveEnd		//0
//#define GeneralTamperCurveEnd	0x000E0000		//64K  �¼���¼��Χ��
#define GeneralTamperCurveEnd	GeneralTamperCurveSta+0x10000		//64K  �¼���¼��Χ��
#define GeneralLoadCurveSta		GeneralTamperCurveEnd		//0
#define GeneralLoadCurveEnd		GeneralLoadCurveSta+0x60000		//384K  ��ͨ�������߷�Χ��


//�����ǰ���4MFLASH���в����ģ��������ַŵ�FLASH�����512K�ֽڲ���..
//����FLASH�洢�ռ䣬Ŀǰ����ռ�ΪAT25DF041A�����256*2+4��K =516K�ֽڵĿռ䡣
//��FLASHÿһҳΪ4K��4096�ֽڣ��߳�Ҳֻ����4Kһ�߳�
// 2 BYTE
#define FLASH_512	 0x200  			//512..
#define FLASH_4K	 0x1000  			//4096  = 4*1024..
#define FLASH_16K	 0x4000  			//16384 = 16*1024..
// 3 BYTE
#define FLASH_64K	 0x10000
#define FLASH_252K	 0x3F000			//252K..
#define FLASH_256K	 0x40000			//256K..
#define FLASH_184K	 0x2E000	//8213�ڲ�flash�洢�û�����Ŀռ�192K-8K=184K

//�����������--����..
//895 37F000h 37FFFFh
#define NEW_FIRMWARE_STATE			(unsigned long)(FLASH_4K)*383 				// 37F000h = 895*4K(1024) //������ʼ����ǰ��4���ֽڳ�ʼ��Ϊ��0xA5 B6 C7 D8
// page
// 4K = 4096
// ����������ʱ����Ϊ��128+252K�ֽڣ�����8���ֽڵ�CRCУ�飩����Ҫ���䵽256K�Լ�������������Ҫ��ÿ�������4K����252K-->256K..
//��������ĳɿɱ䳤�ȣ�ֻҪ��С��104���ֽ�һ��Ϳ��ԣ���ַ��Ҳ�����������������ʼ�ͽ�����ַ..
// NEW FIRMWARE UPGRADE -..
#define UPGRADE_NEW_START				(unsigned long)(FLASH_4K)*384					// 0x180000 = 384*4K(1024) 
//4k --��ʱ������128�ֽ��ã��Լ��汾��Ϣ��..
#define UPGRADE_START_PROGRAM		UPGRADE_NEW_START + FLASH_4K 					// 388*4K(1024)
#define UPGRADE_VECTOR_START 	 	UPGRADE_NEW_START + 73*FLASH_512 			// �ж���������ʼ��ַ..
#define UPGRADE_VECTOR_END 	    	UPGRADE_NEW_START + 74*FLASH_512 			// �ж���������Ҳ��0x10000��ַ�Ŀ�ʼ <1---74>..
//<75---504>.. 
#define UPGRADE_END_PROGRAM			UPGRADE_START_PROGRAM + FLASH_252K 		// 898--959 //4K(1024)

// ��������ǰ�ĳ��� 0LD FIRMWARE
#define CURRENT_NEW_START				(unsigned long)(FLASH_4K)*448					//(384+64)*FLASH_4K) 									
// 4k---��ŵ�ǰ�ļ�����ʹ��128���ֽ�ͷ�ļ���ֱ�Ӵ�ŵ�ǰ512�ֽڵ�Ӧ�ó����ж��������߳�Ӧ�ó���..
#define CURRENT_START_PROGRAM		CURRENT_NEW_START + FLASH_4K 					// 452*4K(1024)

#define CURRENT_VECTOR_START 	    CURRENT_NEW_START + 73*FLASH_512 			// ��ǰ�ж���������ʼ��ַ..
#define CURRENT_VECTOR_END 	    	CURRENT_NEW_START + 74*FLASH_512 			// ��ǰ�ж���������Ҳ��0x10000��ַ�Ŀ�ʼ <1---74>..
//<75---504> ��һ����504��512���ֽ�����..
#define CURRENT_END_PROGRAM			CURRENT_START_PROGRAM + FLASH_252K 		// 898--959 //4K(1024)

