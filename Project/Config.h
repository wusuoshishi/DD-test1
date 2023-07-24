#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long ulong;
typedef unsigned char BYTE;

#define TRUE  1
#define FALSE 0

#define OPEN  1
#define CLOSE 0

#define CHIPTYPE   TRUE

#define CHIP_XS16TK06X (CHIPTYPE == XS16TK06X)
#define XS16TK06X TRUE	 			 

//-------------- <<< Use Configuration Wizard in Context Menu >>> --------------
/*******************************���ò���*******************************************/
//<h> ��������

//<o>����ģʽѡ������ <1=>����ģʽ <0=>����ģʽ
//<i>TRACEMODE:1Ϊ����ģʽ:��ͨ����λ���鿴��������;0Ϊ����ģʽ:����ͨ����λ���鿴�������ݡ�
#define TRACEMODE  	0				//1: ����ģʽ;0: ����ģʽ

//<h> ����ɨ���������

//<o>CH_MAX:				��󰴼�ɨ����  <1-26> 
//<i>CH_MAX:0-26,�����������洢��������
#define CH_MAX 			26			//1~26��������󰴼�ɨ����

//<o>SNS_NUM:				����ɨ���� <0-26> 
//<i>SNS_NUM:0-26,������󰴼�ɨ������
#define SNS_NUM 	 	4				//<=CH_MAX

//<o>CTK_RESO:			����ɨ��ֱ��� <0=>9bit <1=>10bit <2=>11bit <3=>12bit <4=>13bit <5=>14bit <6=>15bit <7=>16bit
//<i>CTK_RESO:0-7��Ӧ����ɨ��ֱ���9bit~16bit��
#define CTK_RESO		5				//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ��

//<o>CTK_DS:				�������Ƶ�� <0=>24MHz <1=>12MHz <2=>6MHz <3=>4MHz
//<i>CTK_DS:0-3��Ӧ�������Ƶ��0:24MHz,1:12MHz,2:6MHz,3:4MHz��
#define CTK_DS			1			//����ٶ�0:24MHz,1:12MHz,2:6MHz,3:4MHz��

//<o>CTK_PRS:				������ŵ�Ƶ��ѡ��<0-63> 
//<i>CTK_PRS:0-63��ӦPRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz��
#define CTK_PRS			62	//PRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz

//<o>CTK_RB:				�����ŵ����<4=>60K <5=>80K
//<i>CTK_RB:4/5��Ӧ�����ŵ���裺4:60K 5:80K ��������
#define CTK_RB 			4				//ѡ��RB�����С4:60K 5:80K ��������
#if (CTK_RB==4||CTK_RB==5)
#else 
#pragma message "CTK_RB ��������!"
CTK_RB=ERROR
#endif

//<o>CTK_RB_ADJ:				CTK_RB_ADJ��׼ֵ  <96-144> 
//<i>CTK_RB_ADJ:				ͨ�����Թ��߶�ȡRBУ׼ֵ����RBУ׼ֵ��ΪRB��׼ֵCTK_RB_ADJ
//ͨ�����Թ��߶�ȡRBУ׼ֵ����RBУ׼ֵ��ΪRB��׼ֵCTK_RB_ADJ
#define CTK_RB_ADJ 	  80


//<o>CTK_REF:				�����ο���ѹ<0=>1.5V <1=>2.1V <2=>2.5V <3=>2.9V <4=>3.2V <5=>3.5V <6=>3.9V <7=>4.2V 
//<i>CTK_REF:0-7��Ӧ�����ο���ѹ0:1.5V 1:2.1V 2:2.5V 3:2.9V 4:3.2V 5:3.5V 6:3.9V 7:4.2V��
#define CTK_REF 		4//5				//�ο���ѹ(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);ע��VCC-VTH>0.5V

//<h> ����ɨ���������
#define ADJUST_PARA_LINE (((((ulong)0x0001<<(CTK_RESO + 9)))*70)/100)//����ӦĿ����-�ֱ�����������70%
//<o>FTH_PARA:				����ģʽ��ָ��ֵ<1-65535> 
//<i>FTH_PARA:1-65535����ģʽ����ָ��ֵ��
#define FTH_PARA 			300//����ģʽ��ָ��ֵ

//<o>CTK_PARA_RESO:			��������ɨ��ֱ��� <0=>9bit <1=>10bit <2=>11bit <3=>12bit <4=>13bit <5=>14bit <6=>15bit <7=>16bit
//<i>CTK_PARA_RESO:0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ������CTK_PARA_RESO = CTK_RESO��			
#define CTK_PARA_RESO		5	//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ������CTK_PARA_RESO = CTK_RESO��

//<o>CTK_PARA_PRS:			����������ŵ�Ƶ��<0-63> 
//<i>CTK_PARA_PRS:0-63����ģʽPRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz��
#define CTK_PARA_PRS		62//����ģʽPRS(��ŵ�Ƶ��) = 48/2/(x+4),62:��̬�ֲ�(1~1.5~3)MHz,63:���ȷֲ�(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz��

//<o>CTK_PARA_RB:				���������ŵ����<4=>60K <5=>80K
//<i>CTK_PARA_RB:4/5��Ӧ����ģʽ�����ŵ���裺4:60K 5:80K ��������
#define CTK_PARA_RB 		4	//ѡ��RB����ģʽ�����С4:60K 5:80K ��������
#if (CTK_PARA_RB==4||CTK_PARA_RB==5)
#else 
#pragma message "CTK_PARA_RB ��������!"
CTK_PARA_RB=ERROR
#endif

//<o>CTK_PARA_REF:			���������ο���ѹ<0=>1.5V <1=>2.1V <2=>2.5V <3=>2.9V <4=>3.2V <5=>3.5V <6=>3.9V <7=>4.2V 
//<i>CTK_REF:0-7��Ӧ����ģʽ�����ο���ѹ0:1.5V 1:2.1V 2:2.5V 3:2.9V 4:3.2V 5:3.5V 6:3.9V 7:4.2V��
#define CTK_PARA_REF 		5//����ģʽ�ο���ѹ(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);ע��VCC-VTH>0.5V

//<o>PAR_NnoiseRenMaxCnt:			����ģʽ�����������жϴ���<0-255> 
//<i>PAR_NnoiseRenMaxCnt:0-255����ģʽ�����������жϴ���,��ֵԽС,����ģʽ���߸���Խ�죬��֮Խ����
#define PAR_NnoiseRenMaxCnt 20		//����ģʽ�����������жϴ���

//<o>PAR_PnoiseRenMaxCnt:			����ģʽ�����������жϴ���<0-255> 
//<i>PAR_PnoiseRenMaxCnt:0-255����ģʽ�����������жϴ���,��ֵԽС,����ģʽ���߸���Խ�죬��֮Խ����
#define PAR_PnoiseRenMaxCnt 20		//����ģʽ�����������жϴ���
//</h> ����ģʽ����ɨ���������

/***ͨ�������� SCAN_XX:0~25,SCAN_00~SCAN_SNS_NUM��Ч��SCAN_00����Ϊ255***/
//<h> ����ɨ��˳������
//<i> ����ɨ��˳����SCAN_00��SCAN_SNS_NUMɨ�裬��Ӧ��ֵΪSNSͨ���š�
#define	null_SNS	100

#define SCAN_00 8	//ԤԼ/����			//KEY1 ��
#define SCAN_01 15	//����/ȡ��			//KEY2 ��
#define SCAN_02 7	//��			//KEY3 ��ʱ/����
#define SCAN_03 14	//��			//KEY4 ����/ȡ��
#define SCAN_04 null_SNS
#define SCAN_05 null_SNS
#define SCAN_06 null_SNS
#define SCAN_07 null_SNS
#define SCAN_08 null_SNS
#define SCAN_09 null_SNS
#define SCAN_10 null_SNS
#define SCAN_11 null_SNS
#define SCAN_12 null_SNS
#define SCAN_13 null_SNS
#define SCAN_14 null_SNS
#define SCAN_15 null_SNS
#define SCAN_16 null_SNS
#define SCAN_17 null_SNS
#define SCAN_18 null_SNS
#define SCAN_19 null_SNS
#define SCAN_20 null_SNS
#define SCAN_21 null_SNS
#define SCAN_22 null_SNS
#define SCAN_23 null_SNS
#define SCAN_24 null_SNS
#define SCAN_25 null_SNS

//</h> ����ɨ��˳������


//<h> ������ָ��ֵ����
//<i> ������ָ��ֵ����оƬ����SNSXXͨ���Ŷ�Ӧ,SCAN_XX:0~25,SCAN_00~SCAN_SNS_NUM��Ч��
/*******************��ָ��ֵ������оƬ����SNSXX��Ӧ********/
#define	null_SNS_FTH	400

#define SCAN_FTH00 null_SNS_FTH			
#define SCAN_FTH01 null_SNS_FTH			
#define SCAN_FTH02 null_SNS_FTH
#define SCAN_FTH03 null_SNS_FTH
#define SCAN_FTH04 null_SNS_FTH
#define SCAN_FTH05 null_SNS_FTH
#define SCAN_FTH06 null_SNS_FTH
#define SCAN_FTH07 null_SNS_FTH
#define SCAN_FTH08 null_SNS_FTH
#define SCAN_FTH09 null_SNS_FTH
#define SCAN_FTH10 null_SNS_FTH
#define SCAN_FTH11 null_SNS_FTH
#define SCAN_FTH12 null_SNS_FTH
#define SCAN_FTH13 null_SNS_FTH
#define SCAN_FTH14 null_SNS_FTH
#define SCAN_FTH15 null_SNS_FTH
#define SCAN_FTH16 null_SNS_FTH
#define SCAN_FTH17 null_SNS_FTH
#define SCAN_FTH18 null_SNS_FTH
#define SCAN_FTH19 null_SNS_FTH
#define SCAN_FTH20 null_SNS_FTH
#define SCAN_FTH21 null_SNS_FTH
#define SCAN_FTH22 null_SNS_FTH
#define SCAN_FTH23 null_SNS_FTH
#define SCAN_FTH24 null_SNS_FTH
#define SCAN_FTH25 null_SNS_FTH


#define FTH00 	  SCAN_FTH00
#define FTH01 	  SCAN_FTH01
#define FTH02     SCAN_FTH02
#define FTH03     SCAN_FTH03
#define FTH04     SCAN_FTH04
#define FTH05     SCAN_FTH05
#define FTH06     SCAN_FTH06
#define FTH07     SCAN_FTH07
#define FTH08     SCAN_FTH08
#define FTH09     SCAN_FTH09
#define FTH10     SCAN_FTH10
#define FTH11     SCAN_FTH11
#define FTH12     SCAN_FTH12
#define FTH13     SCAN_FTH13
#define FTH14     SCAN_FTH14
#define FTH15     SCAN_FTH15
#define FTH16     SCAN_FTH16
#define FTH17     SCAN_FTH17
#define FTH18     SCAN_FTH18
#define FTH19     SCAN_FTH19
#define FTH20     SCAN_FTH20
#define FTH21     SCAN_FTH21
#define FTH22     SCAN_FTH22
#define FTH23     SCAN_FTH23
#define FTH24     SCAN_FTH24
#define FTH25     SCAN_FTH25


//</h> ������ָ��ֵ����


//<h> Ĭ�ϵ���Դֵ����
//<i> PUIV00~PUIVSNS_NUMĬ�ϵ���Դֵ����SCAN_00��SCAN_SNS_NUMɨ���Ӧ��SNSͨ���Ŷ�Ӧ��
//<o>PUIV00:				SCAN_00ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV00 300
//<o>PUIV01:				SCAN_01ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV01 300
//<o>PUIV02:				SCAN_02ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV02 300
//<o>PUIV03:				SCAN_03ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV03 300
//<o>PUIV04:				SCAN_04ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV04 300
//<o>PUIV05:				SCAN_05ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV05 300
//<o>PUIV06:				SCAN_06ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV06 300
//<o>PUIV07:				SCAN_07ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV07 300
//<o>PUIV08:				SCAN_08ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV08 300
//<o>PUIV09:				SCAN_09ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV09 300
//<o>PUIV10:				SCAN_10ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV10 300
//<o>PUIV11:				SCAN_11ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV11 300
//<o>PUIV12:				SCAN_12ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV12 300
//<o>PUIV13:				SCAN_13ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV13 300
//<o>PUIV14:				SCAN_14ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV14 300
//<o>PUIV15:				SCAN_15ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV15 300
//<o>PUIV16:				SCAN_16ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV16 300
//<o>PUIV17:				SCAN_17ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV17 300
//<o>PUIV18:				SCAN_18ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV18 300
//<o>PUIV19:				SCAN_19ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV19 300
//<o>PUIV20:				SCAN_20ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV20 300
//<o>PUIV21:				SCAN_21ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV21 300
//<o>PUIV22:				SCAN_22ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV22 300
//<o>PUIV23:				SCAN_23ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV23 300
//<o>PUIV24:				SCAN_24ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV24 300
//<o>PUIV25:				SCAN_25ͨ����ӦĬ�ϵ���Դֵ<0-511> 
#define PUIV25 300

//</h> Ĭ�ϵ���Դֵ����



//</h> ����ɨ���������

#define ADJUST_STE 	0				//����Ӧ����
#define ADJUST_LINE (((((ulong)0x0001<<(CTK_RESO + 9)))*70)/100)//����ӦĿ����-�ֱ�����������70%

//<h> ��������˲�����
//<e>CS_SW:					�˲��㷨����1:��;0:�ر�
//<i>CS_SW:Ĭ�Ͽ�
#define CS_SW					0	//CS����1Ϊ����0Ϊ�أ�ʹ��"CS_DataDeal_V1.0"��ʱCS_SW = 1;�����󰴼���Ӧ�ٶ������½���

#if (CS_SW == 1)
//<o>CS_F_NUM:			�˲���������<2-20> 
//<i>CS_F_NUM:Ĭ��2��
#define CS_F_NUM			2	//CSΪ1ʱ,�������ݲ�������

//<o>CS_NOISE:				CS�����ж�ֵ<1-65535> 
//<i>CS_NOISE:1-65535,CS�����ж�ֵ��
#define CS_NOISE 			500//CS�����ж�ֵ

//<o>CS_FTH_RATE:			����>CS_NOISEʱ,FTH��������<1-100> 
//<i>CS_FTH_RATE:1-100��Data_Deal()����ֵ>CS_NOISEʱ,��ָ��ֵ����;����CS_FTH_RATE=10ʱ��FingerThreshold = CS_FTH_RATE*FingerThreshold/10��
#define CS_FTH_RATE		15//��Data_Deal()����ֵ>CS_NOISEʱ,��ָ��ֵ����;����CS_FTH_RATE=10ʱ��FingerThreshold = CS_FTH_RATE*FingerThreshold/10

//<o>FTHD_HY_RATE:		����ָ����ʱ,FTH���ͱ���<1-100> 
//<i>FTHD_HY_RATE:1-100,CS_SW = 1ʱ��FTH���ͱ���������ָ����ʱ��FHT���� FingerThreshold = FTHD_HY*FTH/10��
#define FTHD_HY_RATE	10//CS_SW = 1ʱ��FTH���ͱ���������ָ����ʱ��FHT���� FingerThreshold = FTHD_HY*FTH/10

#endif
//</e>CS_SW
//</h> ��������˲�����


//<h> �������߸�������

//<o>TK_COMFIRM_COUNT:				��ָ����ȷ�ϴ���<0-255> 
//<i>TK_COMFIRM_COUNT:0-255,��ָ����ȷ�ϴ�����
#define	TK_COMFIRM_COUNT  	5						//��ָ����ȷ�ϴ�����

//<o>TK_LEFT_COUNT:				��ָ�뿪�жϴ���<0-255> 
//<i>TK_LEFT_COUNT:0-255,��ָ�뿪�жϴ�����
#define TK_LEFT_COUNT 			2						//��ָ�뿪�жϴ�����

//<o>LONG_KEY_COUNT:				����������жϴ���<0-65535> 
//<i>LONG_KEY_COUNT:0-65535,��ʱ��0����1ms��ʱ������������жϴ���,1000Ϊ1S,0Ϊȡ���������жϹ��ܡ�
#define	LONG_KEY_COUNT  		15000				//��ʱ��0����1ms��ʱ������������жϴ���,1000Ϊ1S,0Ϊȡ���������жϹ���

//<o>TK_EOT:				��������,0������<0-255> 
//<i>TK_EOT:0-25,differ����TK_EOT*fht����,0ʱȡ������
#define TK_EOT 							0						//������TK_EOT*fht����,0ʱȡ������

//<o>KEYS_RENOVATE_FLAG:				�������߸������α�־<0x00000000-0xFFFFFFFF> 
//<i>KEYS_RENOVATE_FLAG:0x00000000-0xFFFFFFFF,�������߸������α�־��Ӧ��bitΪ1���������߸��£�0���رջ��߸���		
#define KEYS_RENOVATE_FLAG 					0xFFFFFFFF	//0xFFFFFFFF//0x00000000;//�������߸������α�־1���������߸��£�0���رջ��߸���		

//<o>RENOVATE_FTH_RATE:				������ָ��ֵ����<1-20> 
//<i>RENOVATE_FTH_RATE:1-20,������ָ��ֵ= fht*RENOVATE_FTH_RATE/10��
#define RENOVATE_FTH_RATE 					7						//������ָ��ֵ= fht*RENOVATE_FTH_RATE/10		

//<o>RENOVATE_NTH_RATE:				����������ֵ����<1-20> 
//<i>RENOVATE_NTH_RATE:1-20,�������߸���������ֵ= fht*RENOVATE_NTH_RATE/10��
#define RENOVATE_NTH_RATE						4						//�������߸���������ֵ= fht*RENOVATE_NTH_RATE/10	
//<o>TK_RATE_HY:				��ָ��ֵ���ͱ���<1-20> 
//<i>TK_RATE_HY:1-20,�а�������ʱ��ָ��ֵFingerThreshold = FingerThreshold*TK_RATE_HY/10;
#define TK_RATE_HY  								6						//�а�������ʱ��ָ��ֵFingerThreshold = FingerThreshold*TK_RATE_HY/10;

//<o>OVER_P_NOISE_MAX_COUNT:				differ���ڵ�������������<0-255> 
//<i>OVER_P_NOISE_MAX_COUNT:0-255,�������߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ�졣
#define OVER_P_NOISE_MAX_COUNT			30				//�������߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��

//<o>UNDER_P_NOISE_MAX_COUNT:				differС�ڵ�������������<0-255> 
//<i>UNDER_P_NOISE_MAX_COUNT:0-255,�������߸���differ<=����������,���»��ߣ�ֵԽС�����߸���Խ�졣
#define UNDER_P_NOISE_MAX_COUNT			6//5					//�������߸���differ<=����������,���»��ߣ�ֵԽС�����߸���Խ��

//<o>OVER_N_NOISE_MAX_COUNT:				differ���ڵ��ڸ���������<0-255> 
//<i>OVER_N_NOISE_MAX_COUNT:0-255,�������߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ�졣
#define OVER_N_NOISE_MAX_COUNT			6//5					//�������߸���differ>=����������,���»��ߣ�ֵԽС�����߸���Խ��	

//<o>UNDER_N_NOISE_MAX_COUNT:				differС�ڵ��ڸ���������<0-255> 
//<i>UNDER_N_NOISE_MAX_COUNT:0-255,�������߸���differ<=����������,���»��ߣ�ֵԽС�����߸���Խ�졣
#define	UNDER_N_NOISE_MAX_COUNT			30				//�������߸���differ<=����������,���»��ߣ�ֵԽС�����߸���Խ��

//<o>UNDER_N:				���ڵ��ڸ�UNDER_N����ָ��ֵ����<1-30> 
//<i>UNDER_N:1-30,���ڵ��ڸ�UNDER_N����ָ��ֵ��������(differ>=-(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10))��
#define UNDER_N											5					//���ڵ��ڸ�UNDER_N����ָ��ֵ��������(differ>=-(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10))

//<o>UNDER_NN_NOISE_MAX_COUNT:				С�ڵ��ڸ�UNDER_N����ָ��ֵ��������<0-255> 
//<i>UNDER_NN_NOISE_MAX_COUNT:0-255,С�ڵ��ڸ�UNDER_N����ָ��ֵ��������,���»��ߣ�ֵԽС�����߸���Խ�졣
#define	UNDER_NN_NOISE_MAX_COUNT		5					//С�ڵ��ڸ�UNDER_N����ָ��ֵ��������,���»��ߣ�ֵԽС�����߸���Խ��

//<o>MULTI_KEY_MAX_COUNT:				�ఴ�������жϸ���<0-30> 
//<i>MULTI_KEY_MAX_COUNT:0-30,�ఴ�������жϸ���������0ʱ�޶ఴ���жϡ�
#define MULTI_KEY_MAX_COUNT					0						//�ఴ�������жϸ���������0ʱ�޶ఴ���ж�

//<o>MULTI_KEY_RST_COUNT:				�ఴ���жϻ��߸�λ����<0-255> 
//<i>MULTI_KEY_RST_COUNT:0-255,�ఴ���жϻ��߸�λ������
#define MULTI_KEY_RST_COUNT					30					//�ఴ���жϻ��߸�λ����;	

//<e>���߸���ģʽ��0:����ģʽ��1����ˮģʽ
#define RENOVATE_MODE 							0						//���߸���ģʽ��0:����ģʽ��1����ˮģʽ
#if (RENOVATE_MODE == 1)
//<o>RENOVATE_MODE1_FTH_RATE:				RENOVATE_MODE = 1ʱ,��ָ��ֵ����<1-20> 
//<i>RENOVATE_MODE1_FTH_RATE:1-20,RENOVATE_MODE = 1ʱ,mode_flag��Ӧ�İ�����λʱ����ָ��ֵ= fht*renovate_mode1_fth_rate/10��
#define RENOVATE_MODE1_FTH_RATE 		6						//RENOVATE_MODE = 1ʱ,mode_flag��Ӧ�İ�����λʱ����ָ��ֵ= fht*renovate_mode1_fth_rate/10

//<o>WATER_FLOW_LEFT_MAX_COUNT:				RENOVATE_MODE = 1ʱ,��ˮ�뿪�жϴ�<0-255> 
//<i>WATER_FLOW_LEFT_MAX_COUNT:0-255RENOVATE_MODE = 1ʱ,��ˮ�뿪�жϴ�����
#define WATER_FLOW_LEFT_MAX_COUNT		50					//RENOVATE_MODE = 1ʱ,��ˮ�뿪�жϴ���;

//<o>WATER_FLOW_MAX_COUNT:				RENOVATE_MODE = 1ʱ,��ˮ�жϸ���<0-255> 
//<i>WATER_FLOW_MAX_COUNT:0-255,RENOVATE_MODE = 1ʱ,��ˮ�жϸ�����
#define WATER_FLOW_MAX_COUNT				2						//RENOVATE_MODE = 1ʱ,��ˮ�жϸ���;	

//<o>WATER_FLOW_RST_COUNT:				RENOVATE_MODE = 1ʱ,��ˮ�жϻ��߸�λ����<0-255> 
//<i>WATER_FLOW_RST_COUNT:0-255,RENOVATE_MODE = 1ʱ,��ˮ�жϻ��߸�λ������
#define WATER_FLOW_RST_COUNT				30					//RENOVATE_MODE = 1ʱ,��ˮ�жϻ��߸�λ����;

//<o>WATER_FLOW_RATE:				RENOVATE_MODE = 1ʱ,��ˮ�жϱ���<1-20> 
//<i>WATER_FLOW_RATE:1-20,RENOVATE_MODE = 1ʱ,��ˮ�жϱ���,(((long)n_base_line[i] - (long)base_line[i])) > (renovate_water_flow_rate*FingerThreshold/10)�ĸ�������2ʱΪ��ˮ��
#define WATER_FLOW_RATE							6						//RENOVATE_MODE = 1ʱ,��ˮ�жϱ���,(((long)n_base_line[i] - (long)base_line[i])) > (renovate_water_flow_rate*FingerThreshold/10)�ĸ�������2ʱΪ��ˮ��

//<o>N_BASE_LINE_RENO_MAX_COUNT:				RENOVATE_MODE = 1ʱ,n_base_line���߸����жϴ���<0-255> 
//<i>N_BASE_LINE_RENO_MAX_COUNT:0-255,RENOVATE_MODE = 1ʱ,n_base_line���߸����жϴ����� 
#define N_BASE_LINE_RENO_MAX_COUNT	30					//RENOVATE_MODE = 1ʱ,n_base_line���߸����жϴ�����

#endif
//</e>���߸���ģʽ

//</h> �������߸�������



#define UN_NORMAL_CHECK 						0 					//Rawdata �����ж� 1Ϊ����0Ϊ��,ע:����ʶ�������쳣

#if UN_NORMAL_CHECK
#define UN_NORMAL_MAX_COUNT					3						//Rawdata>=�ֱ�����������80%ʱ�쳣�жϴ���
#define UN_NORMAL_RECOVER_MAX_COUNT	3						//�ж�Rawdata�쳣ʱ������Ӧ����,
#endif


#define			c_xs_cs						0
#define			c_xs_baseLindChangNum	5

//</h>

/*******************************���ò���*******************************************/
//-------------------- <<< end of configuration section >>> --------------------
#include "XS16TK06X.H"
#include "absacc.h"
#include "intrins.h"
#include "stdlib.h"
#include "XS16TK06X_TraceMode.h"
#include "XS16TK06X_TK.h"
#include "XS16TK06X_Timer.h"
#include "Touch_MCU_Init.h"
#include "XS16TK06X_EEP.h"
#include "XS16TK06X_LVDT.h"
#include "XS16TK06X_ADC.h"
#include "XS16TK06X_UART.h"
#include "XS16TK06X_IIC.h"
#include "XS16TK06X_PWM.h"
#include "XS16TK06X_INT.h"
#include "XS16TK06X_Idle.h"
#include "XS16TK06X_Sleep.h"
#include "XS16TK06X_Read_UID.h"

#include "Project.h"
#include ".\Application_Library\Global.h"


extern unsigned long xdata keys_flag_Tracemode;	
#if CH_MAX
extern unsigned int  xdata raw_data[];
extern unsigned int  xdata base_line[];
#endif

extern uchar xdata CFG_Rb;	
extern unsigned long xdata keys_flag;	
extern unsigned int  xdata ctk_soft_reset_count;
extern unsigned int  xdata long_key_clear_count;
extern bit ctk_para_done;
extern bit parallel_mode;
#endif  
