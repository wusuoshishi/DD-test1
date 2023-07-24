#ifndef __XS16TK06X_SLEEP_H__
#define __XS16TK06X_SLEEP_H__

#define SLEEP_MODE   		0//设置Sleep模式：0关闭；1开启。

#if SLEEP_MODE
	extern bit Sleep_Flag;
	extern uint xdata Sleep_Count;
	extern void Sleep(void);
	extern void Sleep_Delay_Us(uint us);
#endif

#endif