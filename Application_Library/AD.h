#ifndef	__AD_h__
#define	__AD_h__


/*************************************************************
***********************常量定义*******************************
*************************************************************/
#if   tab_100k_27k
#define		c_open_error	0x03	//开路AD 注意 ：开路AD对应温度必须在-20度以下
#define		c_short_error	0xfd	//短路AD	注意：短路AD对应温度必须在250度以上
#define   c_over_error       251//0xf8   //超温AD	注意：超温AD对应温度必须在180度以上
#endif

#if   tab_50k_10k
#define		c_open_error	0x05	//开路AD 注意 ：开路AD对应温度必须在-20度以下
#define		c_short_error	0xFC	//短路AD	注意：短路AD对应温度必须在250度以上
#define   c_over_error 0xF6   //超温AD	注意：超温AD对应温度必须在180度以上
#endif

#if   tab_100k_10k
#define		c_open_error	0x02	//开路AD 注意 ：开路AD对应温度必须在-20度以下
#define		c_short_error	0xfa	//短路AD	注意：短路AD对应温度必须在250度以上
#define   c_over_error 0xec   //超温AD	注意：超温AD对应温度必须在180度以上
#endif

#if   tab_50k_27k
#define		c_open_error	0x05	//开路AD 注意 ：开路AD对应温度必须在-20度以下
#define		c_short_error	0xFE	//短路AD	注意：短路AD对应温度必须在250度以上
#define   c_over_error 0xFD   //超温AD	注意：超温AD对应温度必须在180度以上
#endif

#if   tab_other
#define		c_open_error	3	//开路AD 注意 ：开路AD对应温度必须在-20度以下
#define		c_short_error	248	//短路AD	注意：短路AD对应温度必须在250度以上
#define   c_over_error 243   //温度保护AD
#endif


#define		c_temp_fast	0	//温升过快函数

/*************************************************************
***********************外部函数申明***************************
*************************************************************/
extern	void	lab_ad_fun();
extern	void	warning_check();


/*************************************************************
***********************外部变量申明***************************
*************************************************************/
extern	unsigned char	data	b_warning;
extern	unsigned char	xdata	b_error_sec;
extern	unsigned char	xdata	b_error_sec_1;
extern	unsigned char	xdata	b_error_e3;

extern	unsigned char data	gb_wendu;
extern	unsigned char 	xdata	b_temp;
extern  unsigned char   xdata   Target_wendu_1;   //目标温度
extern  unsigned char   xdata   Target_wendu_2;   //目标温度
#if			 double_ad_channel
extern	unsigned char data	gb_wendu2;	//ad通道2
extern	unsigned char 	xdata	b_temp_1;			//ad通道2
#endif



#endif
