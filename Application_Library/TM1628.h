#ifndef	__TM1628_H__
#define	__TM1628_H__


#if	(c_TM1628_EN || c_TM1629_EN)

/*************************************************************
***********************IO�ڶ���*******************************
*************************************************************/
//#define			p_1628dio			Px6
//#define			p_1628clk			Px6	
//#define			p_1628stb			Px6


#define			_p_1628dio_l(x)		SET_##x##_L
#define			__p_1628dio_l(x)	_p_1628dio_l(x)	
#define			p_1628dio_l			__p_1628dio_l(p_1628dio)

#define			_p_1628dio_h(x)		SET_##x##_H
#define			__p_1628dio_h(x)	_p_1628dio_h(x)
#define			p_1628dio_h			__p_1628dio_h(p_1628dio)


#define			_p_1628clk_l(x)		SET_##x##_L
#define			__p_1628clk_l(x)	_p_1628clk_l(x)	
#define			p_1628clk_l			__p_1628clk_l(p_1628clk)

#define			_p_1628clk_h(x)		SET_##x##_H
#define			__p_1628clk_h(x)	_p_1628clk_h(x)
#define			p_1628clk_h			__p_1628clk_h(p_1628clk)


#define			_p_1628stb_l(x)		SET_##x##_L
#define			__p_1628stb_l(x)	_p_1628stb_l(x)	
#define			p_1628stb_l			__p_1628stb_l(p_1628stb)

#define			_p_1628stb_h(x)		SET_##x##_H
#define			__p_1628stb_h(x)	_p_1628stb_h(x)
#define			p_1628stb_h			__p_1628stb_h(p_1628stb)




/*************************************************************
***********************��������*******************************
*************************************************************/

//#define		c_1628_lightGrade		0x8a	//���ȵȼ�
//#define		c_1628_lightMode		0x03	//��ʾģʽ	00:4bit-13part	01:5bit-12part
//										    //			10:6bit-11part	11:7bit-10part
#define		c_1628_dataWrite		0x40	//д����
#define		c_1628_dataRead			0x42	//������
#define		c_1628_initAddr			0xc0	//д���ݳ�ʼ��ַ�趨

#if	c_TM1628_EN
#define		c_1628_dataNum			14
#endif

#if	c_TM1629_EN
#define		c_1628_dataNum			16
#endif



/*************************************************************
***********************�ⲿ��������***************************
*************************************************************/	
	extern	void	TM1628_sendData();	


/*************************************************************
***********************�ⲿ��������***************************
*************************************************************/
	extern	unsigned char	xdata	gb_disIcData[c_1628_dataNum];

#endif
#endif


