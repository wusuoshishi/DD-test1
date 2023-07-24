#ifndef __XS16TK06X_IIC_H__
#define __XS16TK06X_IIC_H__

#define IICS_EN							0	//IIC PA�ڴӻ�ʹ������ 			1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define IIC_FIL_SEL(x)			{PERIPH_IO_SEL &= ~(0x60);PERIPH_IO_SEL |= (0x60&(x<<5));}//1:Ϊ�����˲�(�������˲���Sleepģʽ���޻��ѹ���)��2Ϊģ���˲���3Ϊģ��������˲�(�������˲�ʱ��Sleepģʽ���޻��ѹ���);
#define IIC_IO_MAP(x)			  {REG_ADDR=0x2C,REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x<<0));}//0:ӳ�䵽SDA0_A/SCL0_A��1:ӳ�䵽SDA0_B/SCL0_B��2:ӳ�䵽SDA0_C/SCL0_C��


#define IICS_WCOL (IICSTAT & 0x02)//д��ͻ��־λ
#define IICS_WCOL_CLR (IICSTAT &= ~0x02)//���д��ͻ��־λ

#define IICS_RECOV (IICSTAT & 0x01)//����ͻ��־λ
#define IICS_RECOV_CLR (IICSTAT &= ~0x01)//�������ͻ��־λ

#define IICS_AD (IICSTAT & 0x10)//��ַ�����ݱ�־λ
#define IICS_RW (IICSTAT & 0x20)//��д��־λ

#define SCLEN 		(IICCON & 0x04)//IICʱ��ʹ��λ
#define SCLEN_CLR (IICCON &= ~0x04)//ʹ��ʱ������״̬
#define SCLEN_SET (IICCON |= 0x04)//ʹ��ʱ����������
#define IICS_RW   (IICSTAT & 0x20)//��ȡ��д��־λ
#define IICS_BF   (IICSTAT & 0x08)//��IIC_BUF����־λ
#define PSW_P 	  (PSW & 0x01)//��PSW��ż��־λ


#define IIC_EN 				0x01       
#define IIC_SR 				0x02      
#define IIC_SCLEN 		0x04    	
#define IIC_W_SCL_EN 	0x08 			
#define IIC_R_SCL_EN 	0x10 			
#define IIC_RST 			0x20

#define IIC_IE_SET IEN1 |= 0x08												//��IIC�ж�ʹ��
#define IIC_IE_CLR IEN1 &= ~0x08											//��IIC�ж�ʹ��
#define IIC_IP_SET IPL1 |= 0x08												//����IIC�ж����ȼ�Ϊ��
#define IIC_IP_CLR IPL1 &= ~0x08											//����IIC�ж����ȼ�Ϊ��
#define IIC_INT_FLAG_CLR IRCON1 &= ~0x08							// ���IIC�жϱ�־λ


#if IICS_EN
extern uint data iics_PA_soft_cnt;
extern uint xdata SCLEN_SoftCnt;
extern void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port);
#endif


#endif