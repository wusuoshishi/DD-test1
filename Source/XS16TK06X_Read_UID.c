#include "Config.h"

#if INF_READ_EN
#pragma message "编译,CHIP_UDI_Read相关函数"
/****************************************************************/
//函数名：void CHIP_UDI_Read(void)   
//功  能：读取芯片唯一识别码
//参  数：无
//返回值：无
/****************************************************************/
uchar xdata UID_Buffer[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void CHIP_UDI_Read(void)  
{
	uchar i = 0;
	EA = 0;
	for(i = 0; i < 8; i++)
	{
		UID_Buffer[i] = CBYTE[0x43A8 + i];
	}
	EA = 1;
}
#endif	