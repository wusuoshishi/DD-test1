#ifndef	__CODINGSWITCH_H__
#define	__CODINGSWITCH_H__

#define		c_codingSwitch_en	(0)

#if	(c_codingSwitch_en)


/*************************************************************
***********************IO口定义*******************************
*************************************************************/
//IO口初始化为输入高电平上拉

#define   _p_codingSwitch_io1_get(x)    GET_##x
#define   __p_codingSwitch_io1_get(x)   _p_codingSwitch_io1_get(x)
#define   p_codingSwitch_io1_get        __p_codingSwitch_io1_get(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_l(x)      SET_##x##_L
#define   __p_codingSwitch_io1_l(x)     _p_codingSwitch_io1_l(x)
#define   p_codingSwitch_io1_l          __p_codingSwitch_io1_l(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_h(x)      SET_##x##_H
#define   __p_codingSwitch_io1_h(x)     _p_codingSwitch_io1_h(x)
#define   p_codingSwitch_io1_h          __p_codingSwitch_io1_h(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_in(x)     SET_##x##_IO_IN
#define   __p_codingSwitch_io1_in(x)    _p_codingSwitch_io1_in(x)
#define   p_codingSwitch_io1_in         __p_codingSwitch_io1_in(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_out(x)    SET_##x##_IO_OUT
#define   __p_codingSwitch_io1_out(x)   _p_codingSwitch_io1_out(x)
#define   p_codingSwitch_io1_out        __p_codingSwitch_io1_out(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_pull(x)   SET_##x##_PU_ON
#define   __p_codingSwitch_io1_pull(x)  _p_codingSwitch_io1_pull(x)
#define   p_codingSwitch_io1_pull       __p_codingSwitch_io1_pull(p_codingSwitch_io1)

#define   _p_codingSwitch_io1_nPull(x)  SET_##x##_PU_OFF
#define   __p_codingSwitch_io1_nPull(x) _p_codingSwitch_io1_nPull(x)
#define   p_codingSwitch_io1_nPull      __p_codingSwitch_io1_nPull(p_codingSwitch_io1)



#define   _p_codingSwitch_io2_get(x)    GET_##x
#define   __p_codingSwitch_io2_get(x)   _p_codingSwitch_io2_get(x)
#define   p_codingSwitch_io2_get        __p_codingSwitch_io2_get(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_l(x)      SET_##x##_L
#define   __p_codingSwitch_io2_l(x)     _p_codingSwitch_io2_l(x)
#define   p_codingSwitch_io2_l          __p_codingSwitch_io2_l(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_h(x)      SET_##x##_H
#define   __p_codingSwitch_io2_h(x)     _p_codingSwitch_io2_h(x)
#define   p_codingSwitch_io2_h          __p_codingSwitch_io2_h(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_in(x)     SET_##x##_IO_IN
#define   __p_codingSwitch_io2_in(x)    _p_codingSwitch_io2_in(x)
#define   p_codingSwitch_io2_in         __p_codingSwitch_io2_in(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_out(x)    SET_##x##_IO_OUT
#define   __p_codingSwitch_io2_out(x)   _p_codingSwitch_io2_out(x)
#define   p_codingSwitch_io2_out        __p_codingSwitch_io2_out(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_pull(x)   SET_##x##_PU_ON
#define   __p_codingSwitch_io2_pull(x)  _p_codingSwitch_io2_pull(x)
#define   p_codingSwitch_io2_pull       __p_codingSwitch_io2_pull(p_codingSwitch_io2)

#define   _p_codingSwitch_io2_nPull(x)  SET_##x##_PU_OFF
#define   __p_codingSwitch_io2_nPull(x) _p_codingSwitch_io2_nPull(x)
#define   p_codingSwitch_io2_nPull      __p_codingSwitch_io2_nPull(p_codingSwitch_io2)
		



#define   _p_codingSwitch_io3_get(x)    GET_##x
#define   __p_codingSwitch_io3_get(x)   _p_codingSwitch_io3_get(x)
#define   p_codingSwitch_io3_get        __p_codingSwitch_io3_get(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_l(x)      SET_##x##_L
#define   __p_codingSwitch_io3_l(x)     _p_codingSwitch_io3_l(x)
#define   p_codingSwitch_io3_l          __p_codingSwitch_io3_l(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_h(x)      SET_##x##_H
#define   __p_codingSwitch_io3_h(x)     _p_codingSwitch_io3_h(x)
#define   p_codingSwitch_io3_h          __p_codingSwitch_io3_h(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_in(x)     SET_##x##_IO_IN
#define   __p_codingSwitch_io3_in(x)    _p_codingSwitch_io3_in(x)
#define   p_codingSwitch_io3_in         __p_codingSwitch_io3_in(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_out(x)    SET_##x##_IO_OUT
#define   __p_codingSwitch_io3_out(x)   _p_codingSwitch_io3_out(x)
#define   p_codingSwitch_io3_out        __p_codingSwitch_io3_out(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_pull(x)   SET_##x##_PU_ON
#define   __p_codingSwitch_io3_pull(x)  _p_codingSwitch_io3_pull(x)
#define   p_codingSwitch_io3_pull       __p_codingSwitch_io3_pull(p_codingSwitch_io3)

#define   _p_codingSwitch_io3_nPull(x)  SET_##x##_PU_OFF
#define   __p_codingSwitch_io3_nPull(x) _p_codingSwitch_io3_nPull(x)
#define   p_codingSwitch_io3_nPull      __p_codingSwitch_io3_nPull(p_codingSwitch_io3)



#define   _p_codingSwitch_io4_get(x)    GET_##x
#define   __p_codingSwitch_io4_get(x)   _p_codingSwitch_io4_get(x)
#define   p_codingSwitch_io4_get        __p_codingSwitch_io4_get(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_l(x)      SET_##x##_L
#define   __p_codingSwitch_io4_l(x)     _p_codingSwitch_io4_l(x)
#define   p_codingSwitch_io4_l          __p_codingSwitch_io4_l(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_h(x)      SET_##x##_H
#define   __p_codingSwitch_io4_h(x)     _p_codingSwitch_io4_h(x)
#define   p_codingSwitch_io4_h          __p_codingSwitch_io4_h(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_in(x)     SET_##x##_IO_IN
#define   __p_codingSwitch_io4_in(x)    _p_codingSwitch_io4_in(x)
#define   p_codingSwitch_io4_in         __p_codingSwitch_io4_in(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_out(x)    SET_##x##_IO_OUT
#define   __p_codingSwitch_io4_out(x)   _p_codingSwitch_io4_out(x)
#define   p_codingSwitch_io4_out        __p_codingSwitch_io4_out(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_pull(x)   SET_##x##_PU_ON
#define   __p_codingSwitch_io4_pull(x)  _p_codingSwitch_io4_pull(x)
#define   p_codingSwitch_io4_pull       __p_codingSwitch_io4_pull(p_codingSwitch_io4)

#define   _p_codingSwitch_io4_nPull(x)  SET_##x##_PU_OFF
#define   __p_codingSwitch_io4_nPull(x) _p_codingSwitch_io4_nPull(x)
#define   p_codingSwitch_io4_nPull      __p_codingSwitch_io4_nPull(p_codingSwitch_io4)



/*************************************************************
***********************常量定义*******************************
*************************************************************/
#define		c_codingSwitch_s		(1)			
//顺时针转动返回参数值

#define		c_codingSwitch_n		(2)			
//逆时针转动返回参数值


/*************************************************************
***********************外部函数申明***************************
*************************************************************/	
					 								
						 								

/*************************************************************
***********************外部变量申明***************************
*************************************************************/



#endif
#endif
