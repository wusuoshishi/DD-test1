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
/*******************************配置部分*******************************************/
//<h> 参数配置

//<o>工作模式选择配置 <1=>调试模式 <0=>正常模式
//<i>TRACEMODE:1为调试模式:可通过上位机查看按键数据;0为正常模式:不可通过上位机查看按键数据。
#define TRACEMODE  	0				//1: 调试模式;0: 正常模式

//<h> 按键扫描参数配置

//<o>CH_MAX:				最大按键扫描数  <1-26> 
//<i>CH_MAX:0-26,配置最大允许存储按键数。
#define CH_MAX 			26			//1~26：配置最大按键扫描数

//<o>SNS_NUM:				按键扫描数 <0-26> 
//<i>SNS_NUM:0-26,配置最大按键扫描数。
#define SNS_NUM 	 	4				//<=CH_MAX

//<o>CTK_RESO:			按键扫描分辨率 <0=>9bit <1=>10bit <2=>11bit <3=>12bit <4=>13bit <5=>14bit <6=>15bit <7=>16bit
//<i>CTK_RESO:0-7对应按键扫描分辨率9bit~16bit。
#define CTK_RESO		5				//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。

//<o>CTK_DS:				按键检测频率 <0=>24MHz <1=>12MHz <2=>6MHz <3=>4MHz
//<i>CTK_DS:0-3对应按键检测频率0:24MHz,1:12MHz,2:6MHz,3:4MHz。
#define CTK_DS			1			//检测速度0:24MHz,1:12MHz,2:6MHz,3:4MHz。

//<o>CTK_PRS:				按键充放电频率选择<0-63> 
//<i>CTK_PRS:0-63对应PRS(充放电频率) = 48/2/(x+4),62:正态分布(1~1.5~3)MHz,63:均匀分布(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz。
#define CTK_PRS			62	//PRS(充放电频率) = 48/2/(x+4),62:正态分布(1~1.5~3)MHz,63:均匀分布(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz

//<o>CTK_RB:				按键放电电阻<4=>60K <5=>80K
//<i>CTK_RB:4/5对应按键放电电阻：4:60K 5:80K 其它保留
#define CTK_RB 			4				//选择RB电阻大小4:60K 5:80K 其它保留
#if (CTK_RB==4||CTK_RB==5)
#else 
#pragma message "CTK_RB 配置有误!"
CTK_RB=ERROR
#endif

//<o>CTK_RB_ADJ:				CTK_RB_ADJ基准值  <96-144> 
//<i>CTK_RB_ADJ:				通过调试工具读取RB校准值，将RB校准值填为RB基准值CTK_RB_ADJ
//通过调试工具读取RB校准值，将RB校准值填为RB基准值CTK_RB_ADJ
#define CTK_RB_ADJ 	  80


//<o>CTK_REF:				按键参考电压<0=>1.5V <1=>2.1V <2=>2.5V <3=>2.9V <4=>3.2V <5=>3.5V <6=>3.9V <7=>4.2V 
//<i>CTK_REF:0-7对应按键参考电压0:1.5V 1:2.1V 2:2.5V 3:2.9V 4:3.2V 5:3.5V 6:3.9V 7:4.2V。
#define CTK_REF 		4//5				//参考电压(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);注：VCC-VTH>0.5V

//<h> 并联扫描参数配置
#define ADJUST_PARA_LINE (((((ulong)0x0001<<(CTK_RESO + 9)))*70)/100)//自适应目标线-分辨率最大计数的70%
//<o>FTH_PARA:				并联模式手指阈值<1-65535> 
//<i>FTH_PARA:1-65535并联模式下手指阈值。
#define FTH_PARA 			300//并联模式手指阈值

//<o>CTK_PARA_RESO:			并联按键扫描分辨率 <0=>9bit <1=>10bit <2=>11bit <3=>12bit <4=>13bit <5=>14bit <6=>15bit <7=>16bit
//<i>CTK_PARA_RESO:0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位，建议CTK_PARA_RESO = CTK_RESO。			
#define CTK_PARA_RESO		5	//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位，建议CTK_PARA_RESO = CTK_RESO。

//<o>CTK_PARA_PRS:			并联按键充放电频率<0-63> 
//<i>CTK_PARA_PRS:0-63并联模式PRS(充放电频率) = 48/2/(x+4),62:正态分布(1~1.5~3)MHz,63:均匀分布(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz。
#define CTK_PARA_PRS		62//并联模式PRS(充放电频率) = 48/2/(x+4),62:正态分布(1~1.5~3)MHz,63:均匀分布(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz。

//<o>CTK_PARA_RB:				并联按键放电电阻<4=>60K <5=>80K
//<i>CTK_PARA_RB:4/5对应并联模式按键放电电阻：4:60K 5:80K 其它保留
#define CTK_PARA_RB 		4	//选择RB并联模式电阻大小4:60K 5:80K 其它保留
#if (CTK_PARA_RB==4||CTK_PARA_RB==5)
#else 
#pragma message "CTK_PARA_RB 配置有误!"
CTK_PARA_RB=ERROR
#endif

//<o>CTK_PARA_REF:			并联按键参考电压<0=>1.5V <1=>2.1V <2=>2.5V <3=>2.9V <4=>3.2V <5=>3.5V <6=>3.9V <7=>4.2V 
//<i>CTK_REF:0-7对应并联模式按键参考电压0:1.5V 1:2.1V 2:2.5V 3:2.9V 4:3.2V 5:3.5V 6:3.9V 7:4.2V。
#define CTK_PARA_REF 		5//并联模式参考电压(0:1.5V),(1:2.1V),(2:2.5V),(3:2.9V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);注：VCC-VTH>0.5V

//<o>PAR_NnoiseRenMaxCnt:			并联模式负噪声更新判断次数<0-255> 
//<i>PAR_NnoiseRenMaxCnt:0-255并联模式负噪声更新判断次数,数值越小,并联模式基线更新越快，反之越慢。
#define PAR_NnoiseRenMaxCnt 20		//并联模式负噪声更新判断次数

//<o>PAR_PnoiseRenMaxCnt:			并联模式正噪声更新判断次数<0-255> 
//<i>PAR_PnoiseRenMaxCnt:0-255并联模式正噪声更新判断次数,数值越小,并联模式基线更新越快，反之越慢。
#define PAR_PnoiseRenMaxCnt 20		//并联模式正噪声更新判断次数
//</h> 并联模式按键扫描参数配置

/***通道开启： SCAN_XX:0~25,SCAN_00~SCAN_SNS_NUM有效，SCAN_00不能为255***/
//<h> 按键扫描顺序配置
//<i> 按键扫描顺序按照SCAN_00到SCAN_SNS_NUM扫描，对应的值为SNS通道号。
#define	null_SNS	100

#define SCAN_00 8	//预约/保温			//KEY1 减
#define SCAN_01 15	//功能/取消			//KEY2 加
#define SCAN_02 7	//减			//KEY3 定时/保温
#define SCAN_03 14	//加			//KEY4 功能/取消
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

//</h> 按键扫描顺序配置


//<h> 按键手指阈值配置
//<i> 按键手指阈值按照芯片引脚SNSXX通道号对应,SCAN_XX:0~25,SCAN_00~SCAN_SNS_NUM有效。
/*******************手指阈值设置与芯片引脚SNSXX对应********/
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


//</h> 按键手指阈值配置


//<h> 默认电流源值配置
//<i> PUIV00~PUIVSNS_NUM默认电流源值按照SCAN_00到SCAN_SNS_NUM扫描对应的SNS通道号对应。
//<o>PUIV00:				SCAN_00通道对应默认电流源值<0-511> 
#define PUIV00 300
//<o>PUIV01:				SCAN_01通道对应默认电流源值<0-511> 
#define PUIV01 300
//<o>PUIV02:				SCAN_02通道对应默认电流源值<0-511> 
#define PUIV02 300
//<o>PUIV03:				SCAN_03通道对应默认电流源值<0-511> 
#define PUIV03 300
//<o>PUIV04:				SCAN_04通道对应默认电流源值<0-511> 
#define PUIV04 300
//<o>PUIV05:				SCAN_05通道对应默认电流源值<0-511> 
#define PUIV05 300
//<o>PUIV06:				SCAN_06通道对应默认电流源值<0-511> 
#define PUIV06 300
//<o>PUIV07:				SCAN_07通道对应默认电流源值<0-511> 
#define PUIV07 300
//<o>PUIV08:				SCAN_08通道对应默认电流源值<0-511> 
#define PUIV08 300
//<o>PUIV09:				SCAN_09通道对应默认电流源值<0-511> 
#define PUIV09 300
//<o>PUIV10:				SCAN_10通道对应默认电流源值<0-511> 
#define PUIV10 300
//<o>PUIV11:				SCAN_11通道对应默认电流源值<0-511> 
#define PUIV11 300
//<o>PUIV12:				SCAN_12通道对应默认电流源值<0-511> 
#define PUIV12 300
//<o>PUIV13:				SCAN_13通道对应默认电流源值<0-511> 
#define PUIV13 300
//<o>PUIV14:				SCAN_14通道对应默认电流源值<0-511> 
#define PUIV14 300
//<o>PUIV15:				SCAN_15通道对应默认电流源值<0-511> 
#define PUIV15 300
//<o>PUIV16:				SCAN_16通道对应默认电流源值<0-511> 
#define PUIV16 300
//<o>PUIV17:				SCAN_17通道对应默认电流源值<0-511> 
#define PUIV17 300
//<o>PUIV18:				SCAN_18通道对应默认电流源值<0-511> 
#define PUIV18 300
//<o>PUIV19:				SCAN_19通道对应默认电流源值<0-511> 
#define PUIV19 300
//<o>PUIV20:				SCAN_20通道对应默认电流源值<0-511> 
#define PUIV20 300
//<o>PUIV21:				SCAN_21通道对应默认电流源值<0-511> 
#define PUIV21 300
//<o>PUIV22:				SCAN_22通道对应默认电流源值<0-511> 
#define PUIV22 300
//<o>PUIV23:				SCAN_23通道对应默认电流源值<0-511> 
#define PUIV23 300
//<o>PUIV24:				SCAN_24通道对应默认电流源值<0-511> 
#define PUIV24 300
//<o>PUIV25:				SCAN_25通道对应默认电流源值<0-511> 
#define PUIV25 300

//</h> 默认电流源值配置



//</h> 按键扫描参数配置

#define ADJUST_STE 	0				//自适应步进
#define ADJUST_LINE (((((ulong)0x0001<<(CTK_RESO + 9)))*70)/100)//自适应目标线-分辨率最大计数的70%

//<h> 按键软件滤波配置
//<e>CS_SW:					滤波算法开关1:打开;0:关闭
//<i>CS_SW:默认开
#define CS_SW					0	//CS开关1为开；0为关，使用"CS_DataDeal_V1.0"库时CS_SW = 1;开启后按键响应速度有所下降。

#if (CS_SW == 1)
//<o>CS_F_NUM:			滤波采样次数<2-20> 
//<i>CS_F_NUM:默认2次
#define CS_F_NUM			2	//CS为1时,按键数据采样次数

//<o>CS_NOISE:				CS噪声判断值<1-65535> 
//<i>CS_NOISE:1-65535,CS噪声判断值。
#define CS_NOISE 			500//CS噪声判断值

//<o>CS_FTH_RATE:			噪声>CS_NOISE时,FTH调整比例<1-100> 
//<i>CS_FTH_RATE:1-100当Data_Deal()返回值>CS_NOISE时,手指阈值比例;例：CS_FTH_RATE=10时，FingerThreshold = CS_FTH_RATE*FingerThreshold/10。
#define CS_FTH_RATE		15//当Data_Deal()返回值>CS_NOISE时,手指阈值比例;例：CS_FTH_RATE=10时，FingerThreshold = CS_FTH_RATE*FingerThreshold/10

//<o>FTHD_HY_RATE:		当手指按下时,FTH迟滞比例<1-100> 
//<i>FTHD_HY_RATE:1-100,CS_SW = 1时，FTH迟滞比例，当手指按下时，FHT按照 FingerThreshold = FTHD_HY*FTH/10。
#define FTHD_HY_RATE	10//CS_SW = 1时，FTH迟滞比例，当手指按下时，FHT按照 FingerThreshold = FTHD_HY*FTH/10

#endif
//</e>CS_SW
//</h> 按键软件滤波配置


//<h> 按键基线更新配置

//<o>TK_COMFIRM_COUNT:				手指触摸确认次数<0-255> 
//<i>TK_COMFIRM_COUNT:0-255,手指触摸确认次数。
#define	TK_COMFIRM_COUNT  	5						//手指触摸确认次数；

//<o>TK_LEFT_COUNT:				手指离开判断次数<0-255> 
//<i>TK_LEFT_COUNT:0-255,手指离开判断次数。
#define TK_LEFT_COUNT 			2						//手指离开判断次数；

//<o>LONG_KEY_COUNT:				长按键清除判断次数<0-65535> 
//<i>LONG_KEY_COUNT:0-65535,定时器0开启1ms定时，长按键清除判断次数,1000为1S,0为取消长按键判断功能。
#define	LONG_KEY_COUNT  		15000				//定时器0开启1ms定时，长按键清除判断次数,1000为1S,0为取消长按键判断功能

//<o>TK_EOT:				消顶倍数,0无消顶<0-255> 
//<i>TK_EOT:0-25,differ超过TK_EOT*fht消顶,0时取消消顶
#define TK_EOT 							0						//超过过TK_EOT*fht消顶,0时取消消顶

//<o>KEYS_RENOVATE_FLAG:				按键基线更新屏蔽标志<0x00000000-0xFFFFFFFF> 
//<i>KEYS_RENOVATE_FLAG:0x00000000-0xFFFFFFFF,按键基线更新屏蔽标志对应的bit为1：开启基线更新；0：关闭基线更新		
#define KEYS_RENOVATE_FLAG 					0xFFFFFFFF	//0xFFFFFFFF//0x00000000;//按键基线更新屏蔽标志1：开启基线更新；0：关闭基线更新		

//<o>RENOVATE_FTH_RATE:				按键手指阈值比例<1-20> 
//<i>RENOVATE_FTH_RATE:1-20,按键手指阈值= fht*RENOVATE_FTH_RATE/10。
#define RENOVATE_FTH_RATE 					7						//按键手指阈值= fht*RENOVATE_FTH_RATE/10		

//<o>RENOVATE_NTH_RATE:				按键噪声阈值比例<1-20> 
//<i>RENOVATE_NTH_RATE:1-20,按键基线更新噪声阈值= fht*RENOVATE_NTH_RATE/10。
#define RENOVATE_NTH_RATE						4						//按键基线更新噪声阈值= fht*RENOVATE_NTH_RATE/10	
//<o>TK_RATE_HY:				手指阈值迟滞比例<1-20> 
//<i>TK_RATE_HY:1-20,有按键按下时手指阈值FingerThreshold = FingerThreshold*TK_RATE_HY/10;
#define TK_RATE_HY  								6						//有按键按下时手指阈值FingerThreshold = FingerThreshold*TK_RATE_HY/10;

//<o>OVER_P_NOISE_MAX_COUNT:				differ大于等于正噪声计数<0-255> 
//<i>OVER_P_NOISE_MAX_COUNT:0-255,按键基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快。
#define OVER_P_NOISE_MAX_COUNT			30				//按键基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快

//<o>UNDER_P_NOISE_MAX_COUNT:				differ小于等于正噪声计数<0-255> 
//<i>UNDER_P_NOISE_MAX_COUNT:0-255,按键基线更新differ<=正噪声计数,更新基线，值越小，基线更新越快。
#define UNDER_P_NOISE_MAX_COUNT			6//5					//按键基线更新differ<=正噪声计数,更新基线，值越小，基线更新越快

//<o>OVER_N_NOISE_MAX_COUNT:				differ大于等于负噪声计数<0-255> 
//<i>OVER_N_NOISE_MAX_COUNT:0-255,按键基线更新differ>=负噪声计数,更新基线，值越小，基线更新越快。
#define OVER_N_NOISE_MAX_COUNT			6//5					//按键基线更新differ>=负噪声计数,更新基线，值越小，基线更新越快	

//<o>UNDER_N_NOISE_MAX_COUNT:				differ小于等于负噪声计数<0-255> 
//<i>UNDER_N_NOISE_MAX_COUNT:0-255,按键基线更新differ<=负噪声计数,更新基线，值越小，基线更新越快。
#define	UNDER_N_NOISE_MAX_COUNT			30				//按键基线更新differ<=负噪声计数,更新基线，值越小，基线更新越快

//<o>UNDER_N:				大于等于负UNDER_N倍手指阈值噪声<1-30> 
//<i>UNDER_N:1-30,大于等于负UNDER_N倍手指阈值噪声基线(differ>=-(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10))。
#define UNDER_N											5					//大于等于负UNDER_N倍手指阈值噪声基线(differ>=-(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10))

//<o>UNDER_NN_NOISE_MAX_COUNT:				小于等于负UNDER_N倍手指阈值噪声计数<0-255> 
//<i>UNDER_NN_NOISE_MAX_COUNT:0-255,小于等于负UNDER_N倍手指阈值噪声计数,更新基线，值越小，基线更新越快。
#define	UNDER_NN_NOISE_MAX_COUNT		5					//小于等于负UNDER_N倍手指阈值噪声计数,更新基线，值越小，基线更新越快

//<o>MULTI_KEY_MAX_COUNT:				多按键消除判断个数<0-30> 
//<i>MULTI_KEY_MAX_COUNT:0-30,多按键消除判断个数，等于0时无多按键判断。
#define MULTI_KEY_MAX_COUNT					0						//多按键消除判断个数，等于0时无多按键判断

//<o>MULTI_KEY_RST_COUNT:				多按键判断基线复位计数<0-255> 
//<i>MULTI_KEY_RST_COUNT:0-255,多按键判断基线复位计数。
#define MULTI_KEY_RST_COUNT					30					//多按键判断基线复位计数;	

//<e>基线更新模式：0:常规模式；1：防水模式
#define RENOVATE_MODE 							0						//基线更新模式：0:常规模式；1：防水模式
#if (RENOVATE_MODE == 1)
//<o>RENOVATE_MODE1_FTH_RATE:				RENOVATE_MODE = 1时,手指阈值比例<1-20> 
//<i>RENOVATE_MODE1_FTH_RATE:1-20,RENOVATE_MODE = 1时,mode_flag对应的按键置位时，手指阈值= fht*renovate_mode1_fth_rate/10。
#define RENOVATE_MODE1_FTH_RATE 		6						//RENOVATE_MODE = 1时,mode_flag对应的按键置位时，手指阈值= fht*renovate_mode1_fth_rate/10

//<o>WATER_FLOW_LEFT_MAX_COUNT:				RENOVATE_MODE = 1时,溢水离开判断次<0-255> 
//<i>WATER_FLOW_LEFT_MAX_COUNT:0-255RENOVATE_MODE = 1时,溢水离开判断次数。
#define WATER_FLOW_LEFT_MAX_COUNT		50					//RENOVATE_MODE = 1时,溢水离开判断次数;

//<o>WATER_FLOW_MAX_COUNT:				RENOVATE_MODE = 1时,溢水判断个数<0-255> 
//<i>WATER_FLOW_MAX_COUNT:0-255,RENOVATE_MODE = 1时,溢水判断个数。
#define WATER_FLOW_MAX_COUNT				2						//RENOVATE_MODE = 1时,溢水判断个数;	

//<o>WATER_FLOW_RST_COUNT:				RENOVATE_MODE = 1时,溢水判断基线复位计数<0-255> 
//<i>WATER_FLOW_RST_COUNT:0-255,RENOVATE_MODE = 1时,溢水判断基线复位计数。
#define WATER_FLOW_RST_COUNT				30					//RENOVATE_MODE = 1时,溢水判断基线复位计数;

//<o>WATER_FLOW_RATE:				RENOVATE_MODE = 1时,溢水判断比例<1-20> 
//<i>WATER_FLOW_RATE:1-20,RENOVATE_MODE = 1时,溢水判断比例,(((long)n_base_line[i] - (long)base_line[i])) > (renovate_water_flow_rate*FingerThreshold/10)的个数大于2时为溢水。
#define WATER_FLOW_RATE							6						//RENOVATE_MODE = 1时,溢水判断比例,(((long)n_base_line[i] - (long)base_line[i])) > (renovate_water_flow_rate*FingerThreshold/10)的个数大于2时为溢水。

//<o>N_BASE_LINE_RENO_MAX_COUNT:				RENOVATE_MODE = 1时,n_base_line基线更新判断次数<0-255> 
//<i>N_BASE_LINE_RENO_MAX_COUNT:0-255,RENOVATE_MODE = 1时,n_base_line基线更新判断次数。 
#define N_BASE_LINE_RENO_MAX_COUNT	30					//RENOVATE_MODE = 1时,n_base_line基线更新判断次数；

#endif
//</e>基线更新模式

//</h> 按键基线更新配置



#define UN_NORMAL_CHECK 						0 					//Rawdata 导常判断 1为开，0为关,注:不能识别所有异常

#if UN_NORMAL_CHECK
#define UN_NORMAL_MAX_COUNT					3						//Rawdata>=分辨率最大计数的80%时异常判断次数
#define UN_NORMAL_RECOVER_MAX_COUNT	3						//判断Rawdata异常时允许适应次数,
#endif


#define			c_xs_cs						0
#define			c_xs_baseLindChangNum	5

//</h>

/*******************************配置部分*******************************************/
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
