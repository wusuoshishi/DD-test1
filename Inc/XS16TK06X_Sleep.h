#ifndef __XS16TK06X_SLEEP_H__
#define __XS16TK06X_SLEEP_H__

#define SLEEP_MODE   		0//����Sleepģʽ��0�رգ�1������

#if SLEEP_MODE
	extern bit Sleep_Flag;
	extern uint xdata Sleep_Count;
	extern void Sleep(void);
	extern void Sleep_Delay_Us(uint us);
#endif

#endif