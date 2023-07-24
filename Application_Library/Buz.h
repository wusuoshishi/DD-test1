#ifndef	__BUZ_H__
#define	__BUZ_H__


/*************************************************************
***********************IO口定义*******************************
*************************************************************/
//IO口初始化为关蜂鸣器状态

#define   _p_buz_get(x)                 GET_##x
#define   __p_buz_get(x)                _p_buz_get(x)
#define   p_buz_get                     __p_buz_get(p_buz)

#define   _p_buz_l(x)                   SET_##x##_L
#define   __p_buz_l(x)                  _p_buz_l(x)
#define   p_buz_l                       __p_buz_l(p_buz)

#define   _p_buz_h(x)                   SET_##x##_H
#define   __p_buz_h(x)                  _p_buz_h(x)
#define   p_buz_h                       __p_buz_h(p_buz)

#define   _p_buz_in(x)                  SET_##x##_IO_IN
#define   __p_buz_in(x)                 _p_buz_in(x)
#define   p_buz_in                      __p_buz_in(p_buz)

#define   _p_buz_out(x)                 SET_##x##_IO_OUT
#define   __p_buz_out(x)                _p_buz_out(x)
#define   p_buz_out                     __p_buz_out(p_buz)

#define   _p_buz_pull(x)                SET_##x##_PU_ON
#define   __p_buz_pull(x)               _p_buz_pull(x)
#define   p_buz_pull                    __p_buz_pull(p_buz)

#define   _p_buz_nPull(x)               SET_##x##_PU_OFF
#define   __p_buz_nPull(x)              _p_buz_nPull(x)
#define   p_buz_nPull                   __p_buz_nPull(p_buz)


#define			buz_disEN		{p_buz_h;p_buz_in;}


/*************************************************************
***********************外部函数申明***************************
*************************************************************/
extern	bit	f_buzRun;

extern	void	open_buz(unsigned char i);
extern	void	buz_deal(void);
extern	void	buz_ring(void);


#endif
