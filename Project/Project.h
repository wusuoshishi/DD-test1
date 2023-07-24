#ifndef __PROJECT_H__
#define __PROJECT_H__

#define NK 	0x000000
#define K0 	0x000001
#define K1 	0x000002
#define K2 	0x000004
#define K3 	0x000008
#define K4 	0x000010
#define K5 	0x000020
#define K6 	0x000040
#define K7 	0x000080
#define K8 	0x000100
#define K9 	0x000200
#define K10 0x000400
#define K11 0x000800
#define K12 0x001000
#define K13 0x002000
#define K14 0x004000
#define K15	0x008000
#define K16	0x010000
#define K17	0x020000
#define K18	0x040000
#define K19 0x080000
#define K20 0x100000
#define K21	0x200000
#define K22	0x400000
#define K23	0x800000
#define K24	0x1000000
#define K25	0x2000000

/***************************IO������ӳ��*****************************/

/**********************PA��**********************/


#define SET_PA0_IO_IN TRISA |= 0x01
#define SET_PA1_IO_IN TRISA |= 0x02

#define SET_PA0_IO_OUT TRISA &= ~0x01
#define SET_PA1_IO_OUT TRISA &= ~0x02

#define SET_PA0_L PA0 = 0
#define SET_PA1_L PA1 = 0

#define SET_PA0_H PA0 = 1
#define SET_PA1_H PA1 = 1

#define SET_PA0_PU_ON PU_PA |= 0x01
#define SET_PA1_PU_ON PU_PA |= 0x02

#define SET_PA0_PU_OFF PU_PA &= ~0x01
#define SET_PA1_PU_OFF PU_PA &= ~0x02

#define SET_PA0_OD_ON ODRAIN_EN |= 0x01
#define SET_PA1_OD_ON ODRAIN_EN |= 0x02

#define SET_PA0_OD_OFF ODRAIN_EN &= ~0x01
#define SET_PA1_OD_OFF ODRAIN_EN &= ~0x02

#define GET_PA0 (DATAA&0x01)
#define GET_PA1 (DATAA&0x02)


/**********************PA��**********************/

/**********************PB��**********************/

#define SET_PB0_IO_IN TRISB |= 0x01
#define SET_PB1_IO_IN TRISB |= 0x02
#define SET_PB2_IO_IN TRISB |= 0x04
#define SET_PB3_IO_IN TRISB |= 0x08
#define SET_PB4_IO_IN TRISB |= 0x10
#define SET_PB5_IO_IN TRISB |= 0x20
#define SET_PB6_IO_IN TRISB |= 0x40
#define SET_PB7_IO_IN TRISB |= 0x80

#define SET_PB0_IO_OUT TRISB &= ~0x01
#define SET_PB1_IO_OUT TRISB &= ~0x02
#define SET_PB2_IO_OUT TRISB &= ~0x04
#define SET_PB3_IO_OUT TRISB &= ~0x08
#define SET_PB4_IO_OUT TRISB &= ~0x10
#define SET_PB5_IO_OUT TRISB &= ~0x20
#define SET_PB6_IO_OUT TRISB &= ~0x40
#define SET_PB7_IO_OUT TRISB &= ~0x80


#define SET_PB0_L PB0 = 0
#define SET_PB1_L PB1 = 0
#define SET_PB2_L PB2 = 0
#define SET_PB3_L PB3 = 0
#define SET_PB4_L PB4	= 0
#define SET_PB5_L PB5 = 0
#define SET_PB6_L PB6 = 0
#define SET_PB7_L PB7	= 0

#define SET_PB0_H PB0 = 1
#define SET_PB1_H PB1 = 1
#define SET_PB2_H PB2 = 1
#define SET_PB3_H PB3 = 1
#define SET_PB4_H PB4	= 1
#define SET_PB5_H PB5 = 1
#define SET_PB6_H PB6 = 1
#define SET_PB7_H PB7	= 1


#define SET_PB0_PU_ON PU_PB |= 0x01
#define SET_PB1_PU_ON PU_PB |= 0x02
#define SET_PB2_PU_ON PU_PB |= 0x04
#define SET_PB3_PU_ON PU_PB |= 0x08
#define SET_PB4_PU_ON PU_PB |= 0x10
#define SET_PB5_PU_ON PU_PB |= 0x20
#define SET_PB6_PU_ON PU_PB |= 0x40
#define SET_PB7_PU_ON PU_PB |= 0x80

#define SET_PB0_PU_OFF PU_PB &= ~0x01
#define SET_PB1_PU_OFF PU_PB &= ~0x02
#define SET_PB2_PU_OFF PU_PB &= ~0x04
#define SET_PB3_PU_OFF PU_PB &= ~0x08
#define SET_PB4_PU_OFF PU_PB &= ~0x10
#define SET_PB5_PU_OFF PU_PB &= ~0x20
#define SET_PB6_PU_OFF PU_PB &= ~0x40
#define SET_PB7_PU_OFF PU_PB &= ~0x80

#define GET_PB0 (DATAB&0x01)
#define GET_PB1 (DATAB&0x02)
#define GET_PB2 (DATAB&0x04)
#define GET_PB3 (DATAB&0x08)
#define GET_PB4 (DATAB&0x10)
#define GET_PB5 (DATAB&0x20)
#define GET_PB6 (DATAB&0x40)
#define GET_PB7 (DATAB&0x80)


/**********************PB��**********************/

/**********************PC��**********************/

#define SET_PC0_IO_IN TRISC |= 0x01
#define SET_PC1_IO_IN TRISC |= 0x02
#define SET_PC2_IO_IN TRISC |= 0x04
#define SET_PC3_IO_IN TRISC |= 0x08
#define SET_PC4_IO_IN TRISC |= 0x10
#define SET_PC5_IO_IN TRISC |= 0x20
#define SET_PC6_IO_IN TRISC |= 0x40
#define SET_PC7_IO_IN TRISC |= 0x80

#define SET_PC0_IO_OUT TRISC &= ~0x01
#define SET_PC1_IO_OUT TRISC &= ~0x02
#define SET_PC2_IO_OUT TRISC &= ~0x04
#define SET_PC3_IO_OUT TRISC &= ~0x08
#define SET_PC4_IO_OUT TRISC &= ~0x10
#define SET_PC5_IO_OUT TRISC &= ~0x20
#define SET_PC6_IO_OUT TRISC &= ~0x40
#define SET_PC7_IO_OUT TRISC &= ~0x80



#define SET_PC0_L PC0 = 0
#define SET_PC1_L PC1 = 0
#define SET_PC2_L PC2 = 0
#define SET_PC3_L PC3 = 0
#define SET_PC4_L PC4	= 0
#define SET_PC5_L PC5 = 0
#define SET_PC6_L PC6 = 0
#define SET_PC7_L PC7	= 0

#define SET_PC0_H PC0 = 1
#define SET_PC1_H PC1 = 1
#define SET_PC2_H PC2 = 1
#define SET_PC3_H PC3 = 1
#define SET_PC4_H PC4	= 1
#define SET_PC5_H PC5 = 1
#define SET_PC6_H PC6 = 1
#define SET_PC7_H PC7	= 1


#define SET_PC0_PU_ON PU_PC |= 0x01
#define SET_PC1_PU_ON PU_PC |= 0x02
#define SET_PC2_PU_ON PU_PC |= 0x04
#define SET_PC3_PU_ON PU_PC |= 0x08
#define SET_PC4_PU_ON PU_PC |= 0x10
#define SET_PC5_PU_ON PU_PC |= 0x20
#define SET_PC6_PU_ON PU_PC |= 0x40
#define SET_PC7_PU_ON PU_PC |= 0x80

#define SET_PC0_PU_OFF PU_PC &= ~0x01
#define SET_PC1_PU_OFF PU_PC &= ~0x02
#define SET_PC2_PU_OFF PU_PC &= ~0x04
#define SET_PC3_PU_OFF PU_PC &= ~0x08
#define SET_PC4_PU_OFF PU_PC &= ~0x10
#define SET_PC5_PU_OFF PU_PC &= ~0x20
#define SET_PC6_PU_OFF PU_PC &= ~0x40
#define SET_PC7_PU_OFF PU_PC &= ~0x80

#define GET_PC0 (DATAC&0x01)
#define GET_PC1 (DATAC&0x02)
#define GET_PC2 (DATAC&0x04)
#define GET_PC3 (DATAC&0x08)
#define GET_PC4 (DATAC&0x10)
#define GET_PC5 (DATAC&0x20)
#define GET_PC6 (DATAC&0x40)
#define GET_PC7 (DATAC&0x80)

/**********************PC��**********************/

/**********************PD��*********************/

#define SET_PD0_IO_IN TRISD |= 0x01
#define SET_PD1_IO_IN TRISD |= 0x02
#define SET_PD2_IO_IN TRISD |= 0x04
#define SET_PD3_IO_IN TRISD |= 0x08
#define SET_PD4_IO_IN TRISD |= 0x10
#define SET_PD5_IO_IN TRISD |= 0x20
#define SET_PD6_IO_IN TRISD |= 0x40
#define SET_PD7_IO_IN TRISD |= 0x80

#define SET_PD0_IO_OUT TRISD &= ~0x01
#define SET_PD1_IO_OUT TRISD &= ~0x02
#define SET_PD2_IO_OUT TRISD &= ~0x04
#define SET_PD3_IO_OUT TRISD &= ~0x08
#define SET_PD4_IO_OUT TRISD &= ~0x10
#define SET_PD5_IO_OUT TRISD &= ~0x20
#define SET_PD6_IO_OUT TRISD &= ~0x40
#define SET_PD7_IO_OUT TRISD &= ~0x80


#define SET_PD0_L PD0 = 0
#define SET_PD1_L PD1 = 0
#define SET_PD2_L PD2 = 0
#define SET_PD3_L PD3 = 0
#define SET_PD4_L PD4	= 0
#define SET_PD5_L PD5 = 0
#define SET_PD6_L PD6 = 0
#define SET_PD7_L PD7	= 0

#define SET_PD0_H PD0 = 1
#define SET_PD1_H PD1 = 1
#define SET_PD2_H PD2 = 1
#define SET_PD3_H PD3 = 1
#define SET_PD4_H PD4	= 1
#define SET_PD5_H PD5 = 1
#define SET_PD6_H PD6 = 1
#define SET_PD7_H PD7	= 1

#define SET_PD0_PU_ON PU_PD |= 0x01
#define SET_PD1_PU_ON PU_PD |= 0x02
#define SET_PD2_PU_ON PU_PD |= 0x04
#define SET_PD3_PU_ON PU_PD |= 0x08
#define SET_PD4_PU_ON PU_PD |= 0x10
#define SET_PD5_PU_ON PU_PD |= 0x20
#define SET_PD6_PU_ON PU_PD |= 0x40
#define SET_PD7_PU_ON PU_PD |= 0x80

#define SET_PD0_PU_OFF PU_PD &= ~0x01
#define SET_PD1_PU_OFF PU_PD &= ~0x02
#define SET_PD2_PU_OFF PU_PD &= ~0x04
#define SET_PD3_PU_OFF PU_PD &= ~0x08
#define SET_PD4_PU_OFF PU_PD &= ~0x10
#define SET_PD5_PU_OFF PU_PD &= ~0x20
#define SET_PD6_PU_OFF PU_PD &= ~0x40
#define SET_PD7_PU_OFF PU_PD &= ~0x80

#define GET_PD0 (DATAD&0x01)
#define GET_PD1 (DATAD&0x02)
#define GET_PD2 (DATAD&0x04)
#define GET_PD3 (DATAD&0x08)
#define GET_PD4 (DATAD&0x10)
#define GET_PD5 (DATAD&0x20)
#define GET_PD6 (DATAD&0x40)
#define GET_PD7 (DATAD&0x80)

/**********************PD��**********************/

/***************************IO������ӳ��*****************************/


//IO�ڷ�ת
#define TRUN_PA0 {if(PA0 != 0){PA0 = 0;}else{PA0 = 1;}}
#define TRUN_PA1 {if(PA1 != 0){PA1 = 0;}else{PA1 = 1;}}

#define TRUN_PB0 {if(PB0 != 0){PB0 = 0;}else{PB0 = 1;}}
#define TRUN_PB1 {if(PB1 != 0){PB1 = 0;}else{PB1 = 1;}}
#define TRUN_PB2 {if(PB2 != 0){PB2 = 0;}else{PB2 = 1;}}
#define TRUN_PB3 {if(PB3 != 0){PB3 = 0;}else{PB3 = 1;}}
#define TRUN_PB4 {if(PB4 != 0){PB4 = 0;}else{PB4 = 1;}}
#define TRUN_PB5 {if(PB5 != 0){PB5 = 0;}else{PB5 = 1;}}
#define TRUN_PB6 {if(PB6 != 0){PB6 = 0;}else{PB6 = 1;}}
#define TRUN_PB7 {if(PB7 != 0){PB7 = 0;}else{PB7 = 1;}}

#define TRUN_PC0 {if(PC0 != 0){PC0 = 0;}else{PC0 = 1;}}
#define TRUN_PC1 {if(PC1 != 0){PC1 = 0;}else{PC1 = 1;}}
#define TRUN_PC2 {if(PC2 != 0){PC2 = 0;}else{PC2 = 1;}}
#define TRUN_PC3 {if(PC3 != 0){PC3 = 0;}else{PC3 = 1;}}
#define TRUN_PC4 {if(PC4 != 0){PC4 = 0;}else{PC4 = 1;}}
#define TRUN_PC5 {if(PC5 != 0){PC5 = 0;}else{PC5 = 1;}}
#define TRUN_PC6 {if(PC6 != 0){PC6 = 0;}else{PC6 = 1;}}
#define TRUN_PC7 {if(PC7 != 0){PC7 = 0;}else{PC7 = 1;}}

#define TRUN_PD0 {if(PD0 != 0){PD0 = 0;}else{PD0 = 1;}}
#define TRUN_PD1 {if(PD1 != 0){PD1 = 0;}else{PD1 = 1;}}
#define TRUN_PD2 {if(PD2 != 0){PD2 = 0;}else{PD2 = 1;}}
#define TRUN_PD3 {if(PD3 != 0){PD3 = 0;}else{PD3 = 1;}}
#define TRUN_PD4 {if(PD4 != 0){PD4 = 0;}else{PD4 = 1;}}
#define TRUN_PD5 {if(PD5 != 0){PD5 = 0;}else{PD5 = 1;}}
#define TRUN_PD6 {if(PD6 != 0){PD6 = 0;}else{PD6 = 1;}}
#define TRUN_PD7 {if(PD7 != 0){PD7 = 0;}else{PD7 = 1;}}

extern void Project(void);
extern bit IsTouch;




extern  unsigned	char	xdata   b_NOW_or_Target_cnt ;    //0:Ŀ���¶�,5:�����¶�
extern  unsigned	char	xdata   b_NOW_or_Target_cnt2 ;    //0:Ŀ���¶�,5:�����¶�
extern	bit		gf_check;   //�ϵ��Լ��־



#define c_NOW_or_Target_cnt_MAX 10//ʱ��ת�����ֵ
#define c_IS_disp_NOW   5  //��ʾ�����¶�
#define c_IS_disp_Target   0  //��ʾĿ���¶�




//#if test_en       
//
//extern void  test_deal();
//
//#endif


#endif