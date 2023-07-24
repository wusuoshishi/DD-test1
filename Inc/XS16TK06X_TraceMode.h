#ifndef __XS16TK06X_TRACEMODE_H__ 
#define __XS16TK06X_TRACEMODE_H__ 

#if TRACEMODE
extern unsigned char data ReadCnt;
extern unsigned char data ReceData;
extern unsigned char data DataNum;
extern bit OddCheck;
extern bit NeedCheckOdd;
extern unsigned int xdata raw;
extern unsigned int xdata bas;


#endif
//-----------------------------------------------------------------//
//�������ƣ� void XS16TK06X_Trace_Mode_Init(void)   
//�������ܣ� XS16TK06X_Trace_ModeI_nit��ʼ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void XS16TK06X_Trace_Mode_Init(uchar iic_port);
//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Read_Data(uint *p_rawData,uint *p_baseline,ulong t_keysFlagSN)   
//�������ܣ� �����͵�����д��IICBUF
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN);   
//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Write_Data(void)  
//�������ܣ� ��IICBUF��ȡ����
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void TraceMode_Master_Write_Data(void);

#endif
