#include "Config.h"

#if INF_READ_EN
#pragma message "����,CHIP_UDI_Read��غ���"
/****************************************************************/
//��������void CHIP_UDI_Read(void)   
//��  �ܣ���ȡоƬΨһʶ����
//��  ������
//����ֵ����
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