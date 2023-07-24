#include 	"..\Application_Library\Global.h"

unsigned char	xdata	b_warning_buf=0;
unsigned char	data	b_warning=0;

unsigned char	xdata	b_error_sec=0;
unsigned char	xdata	b_error_sec_1=0;
unsigned char	xdata	b_error_e3=0;

unsigned char   xdata   Target_wendu_1=35;
unsigned char   xdata   Target_wendu_2=35;

unsigned int	xdata	b_quit_time=0;



#if			 c_temp_fast
bit		f_e3_xd=0;
bit   f_first_checke3=0;
unsigned char	xdata	b_wendu_old=0;
#endif

bit		check_ad_ok=0;  //AD检测完成
bit		check_ad_ok_1=0;    //AD1检测完成

unsigned char data	b_delay_check_ad=0;

unsigned char data	gb_wendu=0;
unsigned int 	xdata	b_ad_buf0=0;
unsigned char 	xdata	b_ad_buf1=0;
unsigned char 	xdata	b_ad_value=0;		//查表得出的温度值
unsigned char 	xdata	b_temp=100;			//底部温度值
unsigned char 	xdata	b_temp_cnt=0;	//比较计数

unsigned char 	xdata	b_admax_value=0;
unsigned char 	xdata	b_admin_value=0;
unsigned char 	xdata	b_temp_ad=0;


#if			 double_ad_channel
unsigned char data	gb_wendu2=0;
unsigned int 	xdata	b_ad_buf0_1=0;
unsigned char 	xdata	b_ad_buf1_1=0;
unsigned char 	xdata	b_ad_value_1=0;		//查表得出的温度值
unsigned char 	xdata	b_temp_1=100;			//底部温度值
unsigned char 	xdata	b_temp_cnt_1=0;

unsigned char 	xdata	b_admax_value_1=0;
unsigned char 	xdata	b_admin_value_1=0;
unsigned char 	xdata	b_temp_ad_1=0;
#endif

#if   ad_en

#if	tab_50k_10k
unsigned char const code 	tab_temper[]=
{
    0x0E,   	//0
    0x0F,
    0x10,
    0x11,
    0x11,
    0x12,
    0x13,
    0x14,
    0x15,
    0x16,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1E,
    0x1F,
    0x20,
    0x21,
    0x23,
    0x24,
    0x26,
    0x27,
    0x29,
    0x2A,
    0x2C,
    0x2D,
    0x2F,
    0x31,
    0x32,
    0x34,
    0x36,
    0x38,
    0x3A,
    0x3C,
    0x3D,
    0x3F,
    0x41,
    0x43,
    0x45,
    0x48,
    0x4A,
    0x4C,
    0x4E,
    0x50,
    0x52,
    0x54,
    0x57,
    0x59,
    0x5B,
    0x5D,
    0x60,
    0x62,
    0x64,
    0x67,
    0x69,
    0x6B,
    0x6D,
    0x70,
    0x72,
    0x74,
    0x77,
    0x79,
    0x7B,
    0x7E,
    0x80,
    0x82,
    0x84,
    0x87,
    0x89,
    0x8B,
    0x8D,
    0x8F,
    0x91,
    0x94,
    0x96,
    0x98,
    0x9A,
    0x9C,
    0x9E,
    0xA0,
    0xA2,
    0xA4,
    0xA6,
    0xA8,
    0xA9,
    0xAB,
    0xAD,
    0xAF,
    0xB1,
    0xB2,
    0xB4,
    0xB6,
    0xB7,
    0xB9,
    0xBA,
    0xBC,
    0xBD,
    0xBF,
    0xC0,
    0xC2,
    0xC3,
    0xC5,
    0xC6,
    0xC7,
    0xC8,
    0xCA,
    0xCB,
    0xCC,
    0xCD,
    0xCE,
    0xD0,
    0xD1,
    0xD2,
    0xD3,
    0xD4,
    0xD5,
    0xD6,
    0xD7,
    0xD8,
    0xD9,
    0xDA,
    0xDA,
    0xDB,
    0xDC,
    0xDD,
    0xDE,
    0xDF,
    0xDF,
    0xE0,
    0xE1,
    0xE1,
    0xE2,
    0xE3,
    0xE4,
    0xE5 //136
};
#endif

#if	tab_100k_10k
unsigned char const code 	tab_temper[]=
{
    0x07,   	//0
    0x08,
    0x08,
    0x08,
    0x09,
    0x09,
    0x0A,
    0x0A,
    0x0B,
    0x0B,
    0x0C,
    0x0C,
    0x0D,
    0x0E,
    0x0E,
    0x0F,
    0x10,
    0x10,
    0x11,
    0x12,
    0x12,
    0x13,
    0x14,
    0x15,
    0x16,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x1F,
    0x20,
    0x22,
    0x23,
    0x24,
    0x25,
    0x27,
    0x28,
    0x29,
    0x2B,
    0x2C,
    0x2E,
    0x2F,
    0x31,
    0x32,
    0x34,
    0x36,
    0x37,
    0x39,
    0x3B,
    0x3C,
    0x3E,
    0x40,
    0x42,
    0x44,
    0x46,
    0x47,
    0x49,
    0x4B,
    0x4D,
    0x4F,
    0x51,
    0x53,
    0x55,
    0x57,
    0x59,
    0x5B,
    0x5D,
    0x5F,
    0x61,
    0x63,
    0x66,
    0x68,
    0x6A,
    0x6C,
    0x6E,
    0x70,
    0x72,
    0x74,
    0x76,
    0x78,
    0x7A,
    0x7D,
    0x7F,
    0x81,
    0x83,
    0x85,
    0x87,
    0x89,
    0x8B,
    0x8D,
    0x8F,
    0x91,
    0x93,
    0x95,
    0x96,
    0x98,
    0x9A,
    0x9C,
    0x9E,
    0xA0,
    0xA1,
    0xA3,
    0xA5,
    0xA7,
    0xA8,
    0xAA,
    0xAC,
    0xAD,
    0xAF,
    0xB0,
    0xB2,
    0xB3,
    0xB5,
    0xB6,
    0xB8,
    0xB9,
    0xBB,
    0xBC,
    0xBD,
    0xBF,
    0xC0,
    0xC1,
    0xC3,
    0xC4,
    0xC5,
    0xC6,
    0xC8,
    0xC9,
    0xCA,
    0xCB,
    0xCC,
    0xCD,
    0xCE, //136
};
#endif


#if	tab_100k_27k
unsigned char const code 	tab_temper[]=
{
    0x13,   	//0
    0x14,//1   
    0x15,//2
    0x16,//3
    0x17,//4
    0x18,//5
    0x19,//6
    0x1A,//7
    0x1C,//8
    0x1D,//9
    0x1E,//10
    0x1F,//11
    0x21,//12
    0x22,//13
    0x24,//14
    0x25,//15
    0x27,//16
    0x28,//17
    0x2A,//18
    0x2B,//19
    0x2D,//20
    0x2F,//21
    0x30,//22
    0x32,//23
    0x34,//24
    0x36,//25
    0x38,//26
    0x3A,//27
    0x3C,//28
    0x3E,//29
    0x40,//30
    0x42,//31
    0x44,//32
    0x46,//33
    0x48,//34
    0x4A,//35
    0x4D,//36
    0x4F,//37
    0x51,//38
    0x53,//39
    0x56,//40
    0x58,//41
    0x5A,//42
    0x5D,//43
    0x5F,//44
    0x61,//45
    0x64,//46
    0x66,//47
    0x69,//48
    0x6B,//49
    0x6D,//50
    0x70,//51
    0x72,//52
    0x75,//53
    0x77,//54
    0x79,//55
    0x7C,//56
    0x7E,//57
    0x81,//58
    0x83,//59
    0x85,//60
    0x88,//61
    0x8A,//62
    0x8C,//63
    0x8E,//64
    0x91,//65
    0x93,//66
    0x95,//67
    0x97,//68
    0x99,//69
    0x9C,//70
    0x9E,//71
    0xA0,//72
    0xA2,//73
    0xA4,//74
    0xA6,//75
    0xA8,//76
    0xAA,//77
    0xAC,//78
    0xAD,//79
    0xAF,//80
    0xB1,//81
    0xB3,//82
    0xB5,//83
    0xB6,//84
    0xB8,//85
    0xBA,//86
    0xBB,//87
    0xBD,//88
    0xBE,//89
    0xC0,//90
    0xC1,//91
    0xC3,//92
    0xC4,//93
    0xC6,//94
    0xC7,//95
    0xC8,//96
    0xCA,//97
    0xCB,//98
    0xCC,//99
    0xCD,//100
    0xCF,//101
    0xD0,//102
    0xD1,//103
    0xD2,//104
    0xD3,//105
    0xD4,//106
    0xD5,//107
    0xD6,//108
    0xD7,//109
    0xD8,//110
    0xD9,//111
    0xDA,//112
    0xDB,//113
    0xDC,//114
    0xDD,//115
    0xDE,//116
    0xDF,//117
    0xDF,//118
    0xE0,//119
    0xE1,//120
    0xE2,//121
    0xE2,//122
    0xE3,//123
    0xE4,//124
    0xE4,//125
    0xE5,//126
    0xE6,//127
    0xE6,//128
    0xE7,//129
    0xE7,//130
    0xE8,//131
    0xE9,//132
    0xE9,//133
    0xEA,//134
    0xEA,//135
    0xEB //136
};
#endif


#if	tab_50k_27k
unsigned char const code 	tab_temper[]=
{
    0x24,   	//0
    0x26,
    0x27,
    0x29,
    0x2B,
    0x2C,
    0x2E,
    0x30,
    0x32,
    0x34,
    0x36,
    0x38,
    0x3A,
    0x3D,
    0x3F,
    0x41,
    0x43,
    0x46,
    0x48,
    0x4A,
    0x4D,
    0x4F,
    0x52,
    0x54,
    0x57,
    0x59,
    0x5C,
    0x5E,
    0x61,
    0x64,
    0x66,
    0x69,
    0x6C,
    0x6E,
    0x71,
    0x73,
    0x76,
    0x79,
    0x7B,
    0x7E,
    0x80,
    0x83,
    0x86,
    0x88,
    0x8B,
    0x8D,
    0x90,
    0x92,
    0x95,
    0x97,
    0x99,
    0x9C,
    0x9E,
    0xA0,
    0xA2,
    0xA5,
    0xA7,
    0xA9,
    0xAB,
    0xAD,
    0xAF,
    0xB1,
    0xB3,
    0xB5,
    0xB7,
    0xB9,
    0xBB,
    0xBC,
    0xBE,
    0xC0,
    0xC1,
    0xC3,
    0xC5,
    0xC6,
    0xC8,
    0xC9,
    0xCB,
    0xCC,
    0xCD,
    0xCF,
    0xD0,
    0xD1,
    0xD2,
    0xD4,
    0xD5,
    0xD6,
    0xD7,
    0xD8,
    0xD9,
    0xDA,
    0xDB,
    0xDC,
    0xDD,
    0xDE,
    0xDF,
    0xE0,
    0xE1,
    0xE1,
    0xE2,
    0xE3,
    0xE4,
    0xE5,
    0xE5,
    0xE6,
    0xE7,
    0xE7,
    0xE8,
    0xE9,
    0xE9,
    0xEA,
    0xEA,
    0xEB,
    0xEB,
    0xEC,
    0xEC,
    0xED,
    0xED,
    0xEE,
    0xEE,
    0xEF,
    0xEF,
    0xF0,
    0xF0,
    0xF0,
    0xF1,
    0xF1,
    0xF2,
    0xF2,
    0xF2,
    0xF3,
    0xF3,
    0xF3,
    0xF4,
    0xF4,
    0xF4,
    0xF4,
    0xF5 //136
};
#endif


#if   tab_other //5.1K上拉 100KNTC
unsigned char const code 	tab_temper[]=
{
	3,	//0℃		325.792
	4,	//1℃		309.671
	4,	//2℃		294.4406
	4,	//3℃		280.0466
	4,	//4℃		266.4385
	5,	//5℃		253.5692
	5,	//6℃		241.3946
	5,	//7℃		229.8733
	5,	//8℃		218.9668
	6,	//9℃		208.6389
	6,	//10℃		198.856
	6,	//11℃		189.5862
	7,	//12℃		180.8
	7,	//13℃		172.4696
	7,	//14℃		164.5689
	8,	//15℃		157.0735
	8,	//16℃		149.9605
	8,	//17℃		143.2084
	9,	//18℃		136.797
	9,	//19℃		130.7073
	10,	//20℃		124.9216
	10,	//21℃		119.423
	10,	//22℃		114.196
	11,	//23℃		109.2256
	11,	//24℃		104.4979
	12,	//25℃		100
	12,	//26℃		95.7194
	13,	//27℃		91.6446
	14,	//28℃		87.7646
	14,	//29℃		84.0692
	15,	//30℃		80.5486
	15,	//31℃		77.1937
	16,	//32℃		73.9959
	17,	//33℃		70.947
	17,	//34℃		68.0395
	18,	//35℃		65.266
	19,	//36℃		62.6197
	20,	//37℃		60.0941
	20,	//38℃		57.6832
	21,	//39℃		55.3812
	22,	//40℃		53.1827
	23,	//41℃		51.0825
	24,	//42℃		49.0757
	24,	//43℃		47.1578
	25,	//44℃		45.3244
	26,	//45℃		43.5713
	27,	//46℃		41.8947
	28,	//47℃		40.2908
	29,	//48℃		38.7563
	30,	//49℃		37.2876
	31,	//50℃		35.8818
	32,	//51℃		34.5358
	34,	//52℃		33.2469
	35,	//53℃		32.0122
	36,	//54℃		30.8294
	37,	//55℃		29.6959
	38,	//56℃		28.6095
	39,	//57℃		27.5681
	41,	//58℃		26.5695
	42,	//59℃		25.6118
	43,	//60℃		24.6931
	45,	//61℃		23.8118
	46,	//62℃		22.966
	47,	//63℃		22.1542
	49,	//64℃		21.3749
	50,	//65℃		20.6267
	52,	//66℃		19.9081
	53,	//67℃		19.2179
	55,	//68℃		18.5547
	56,	//69℃		17.9175
	58,	//70℃		17.3052
	59,	//71℃		16.7165
	61,	//72℃		16.1505
	63,	//73℃		15.6063
	64,	//74℃		15.0829
	66,	//75℃		14.5794
	68,	//76℃		14.095
	69,	//77℃		13.6288
	71,	//78℃		13.1802
	73,	//79℃		12.7483
	74,	//80℃		12.3325
	76,	//81℃		11.9321
	78,	//82℃		11.5465
	80,	//83℃		11.175
	82,	//84℃		10.8171
	83,	//85℃		10.4723
	85,	//86℃		10.1399
	87,	//87℃		9.8196
	89,	//88℃		9.5108
	91,	//89℃		9.213
	93,	//90℃		8.9258
	94,	//91℃		8.6488
	96,	//92℃		8.3817
	98,	//93℃		8.1239
	100,	//94℃		7.8751
	102,	//95℃		7.635
	104,	//96℃		7.4033
	106,	//97℃		7.1796
	108,	//98℃		6.9636
	110,	//99℃		6.755
	112,	//100℃		6.5535
	113,	//101℃		6.3589
	115,	//102℃		6.1709
	117,	//103℃		5.9892
	119,	//104℃		5.8137
	121,	//105℃		5.644
	123,	//106℃		5.4799
	125,	//107℃		5.3214
	127,	//108℃		5.168
	129,	//109℃		5.0197
	130,	//110℃		4.8763
	132,	//111℃		4.7375
	134,	//112℃		4.6033
	136,	//113℃		4.4734
	138,	//114℃		4.3478
	139,	//115℃		4.2261
	141,	//116℃		4.1084
	143,	//117℃		3.9944
	145,	//118℃		3.884
	147,	//119℃		3.7771
	148,	//120℃		3.6736
	150,	//121℃		3.5734
	152,	//122℃		3.4762
	153,	//123℃		3.3821
	155,	//124℃		3.291
	157,	//125℃		3.2026
	158,	//126℃		3.117
	160,	//127℃		3.034
	162,	//128℃		2.9535
	163,	//129℃		2.8755
	165,	//130℃		2.7998
	166,	//131℃		2.7265
	168,	//132℃		2.6553
	169,	//133℃		2.5863
	171,	//134℃		2.5193
	172,	//135℃		2.4543
	174,	//136℃		2.3913
	175,	//137℃		2.3301
	177,	//138℃		2.2707
	178,	//139℃		2.2131
	179,	//140℃		2.1571
	181,	//141℃		2.1028
	182,	//142℃		2.05
	183,	//143℃		1.9988
	185,	//144℃		1.9491
	186,	//145℃		1.9007
	187,	//146℃		1.8538
	188,	//147℃		1.8082
	190,	//148℃		1.7639
	191,	//149℃		1.7208
	192,	//150℃		1.6789
	193,	//151℃		1.6383
	194,	//152℃		1.5987
	196,	//153℃		1.5603
	197,	//154℃		1.5229
	198,	//155℃		1.4866
	199,	//156℃		1.4513
	200,	//157℃		1.4169
	201,	//158℃		1.3835
	202,	//159℃		1.351
	203,	//160℃		1.3193
	204,	//161℃		1.2885
	205,	//162℃		1.2586
	206,	//163℃		1.2295
	207,	//164℃		1.2011
	208,	//165℃		1.1735
	209,	//166℃		1.1466
	209,	//167℃		1.1205
	210,	//168℃		1.095
	211,	//169℃		1.0702
	212,	//170℃		1.0461
	213,	//171℃		1.0226
	214,	//172℃		0.9997
	214,	//173℃		0.9774
	215,	//174℃		0.9557
	216,	//175℃		0.9345
	217,	//176℃		0.9139
	217,	//177℃		0.8938
	218,	//178℃		0.8742
	219,	//179℃		0.8551
	219,	//180℃		0.8365
	220,	//181℃		0.8184
	221,	//182℃		0.8007
	221,	//183℃		0.7835
	222,	//184℃		0.7667
	223,	//185℃		0.7503
	223,	//186℃		0.7344
	224,	//187℃		0.7188
	224,	//188℃		0.7036
	225,	//189℃		0.6888
	226,	//190℃		0.6744
	226,	//191℃		0.6603
	227,	//192℃		0.6465
	227,	//193℃		0.6331
	228,	//194℃		0.62
	228,	//195℃		0.6072
	229,	//196℃		0.5947
	229,	//197℃		0.5826
	230,	//198℃		0.5707
	230,	//199℃		0.5591
	231,	//200℃		0.5478
	231,	//201℃		0.5367
	232,	//202℃		0.5259
	232,	//203℃		0.5154
	232,	//204℃		0.5051
	233,	//205℃		0.495
	233,	//206℃		0.4852
	234,	//207℃		0.4756
	234,	//208℃		0.4662
	234,	//209℃		0.4571
	235,	//210℃		0.4482
	235,	//211℃		0.4394
	236,	//212℃		0.4309
	236,	//213℃		0.4225
	236,	//214℃		0.4144
	237,	//215℃		0.4064
	237,	//216℃		0.3986
	237,	//217℃		0.391
	238,	//218℃		0.3836
	238,	//219℃		0.3763
	238,	//220℃		0.3692
	239,	//221℃		0.3622
	239,	//222℃		0.3554
	239,	//223℃		0.3488
	239,	//224℃		0.3423
	240,	//225℃		0.3359
	240,	//226℃		0.3297
	240,	//227℃		0.3236
	240,	//228℃		0.3177
	241,	//229℃		0.3118
	241,	//230℃		0.3061
	241,	//231℃		0.3006
	241,	//232℃		0.2951
	242,	//233℃		0.2898
	242,	//234℃		0.2845
	242,	//235℃		0.2794
	242,	//236℃		0.2744
	243,	//237℃		0.2695
	243,	//238℃		0.2647
	243,	//239℃		0.26
	243,	//240℃		0.2554
	243,	//241℃		0.2509
	244,	//242℃		0.2465
	244,	//243℃		0.2422
	244,	//244℃		0.238
	244,	//245℃		0.2338
	244,	//246℃		0.2298
	245,	//247℃		0.2258
	245,	//248℃		0.2219
	245,	//249℃		0.2181
	245	//250℃		0.2144

};
#endif

unsigned char	get_wendu1(unsigned char ad_value);
unsigned char	get_wendu2(unsigned char ad_value);
void    temp_fast();


//-----------------------------------------------------------------//
//函数名称： void lab_ad_fun(void)
//函数功能： 得出过滤的AD值（20ms执行一次）
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void lab_ad_fun(void)
{
    uchar ad_com=0;

#if   c_ad_buz_com
    if(f_buzRun)
        ad_com=1;
#endif

    if(ad_com==0)
    {
        if(b_delay_check_ad<10)   //复用之后延时检测AD
            b_delay_check_ad++;

        if(b_delay_check_ad>=10)
        {
            b_temp_ad=ADC_Obtain(c_ad_channel);
            b_ad_buf0 += b_temp_ad;	//12位数据右对齐
            b_ad_buf1 ++;
            if(b_temp_ad>=b_admax_value)
                b_admax_value=b_temp_ad;
            if(b_temp_ad<=b_admin_value)
                b_admin_value=b_temp_ad;
            if(b_ad_buf1 >= 0x0a)
            {
                b_ad_buf1 = 0;
                b_ad_buf0-=b_admin_value;
                b_ad_buf0-=b_admax_value;
                b_ad_value = b_ad_buf0>>3;
				#if	c_ad_up_pull
                	b_ad_value = ~b_ad_value;
				#endif
                b_ad_buf0 = 0;
                b_admax_value=0;
                b_admin_value=0xff;

#if	c_ad_mode

                b_temp = b_ad_value;
                check_ad_ok=1;
#endif
            }

#if	(c_ad_mode==0)

            b_temp_cnt ++;
            if(b_temp == b_ad_value)
                b_temp_cnt = 0;
            if(b_temp_cnt >= 0x32)
            {
                b_temp_cnt = 0;
                b_temp = b_ad_value;
                gb_wendu =  get_wendu1(b_temp);
                check_ad_ok=1;
            }

#endif


#if		double_ad_channel
            b_temp_ad_1=ADC_Obtain(c_ad_channel_1);
            b_ad_buf0_1 += b_temp_ad_1;	//12位数据右对齐
            b_ad_buf1_1 ++;
            if(b_temp_ad_1>=b_admax_value_1)
                b_admax_value_1=b_temp_ad_1;
            if(b_temp_ad_1<=b_admin_value_1)
                b_admin_value_1=b_temp_ad_1;
            if(b_ad_buf1_1 >= 0x0a)
            {
                b_ad_buf1_1 = 0;
                b_ad_buf0_1-=b_admin_value_1;
                b_ad_buf0_1-=b_admax_value_1;
                b_ad_value_1 = b_ad_buf0_1>>3;
#if	c_ad_up_pull_1
                b_ad_value_1 = ~b_ad_value_1;
#endif
                b_ad_buf0_1 = 0;
                b_admax_value_1=0;
                b_admin_value_1=0xff;
#if	c_ad_mode_1

                b_temp_1 = b_ad_value_1;
                check_ad_ok_1=1;

#endif
            }

#if	(c_ad_mode_1==0)
            b_temp_cnt_1 ++;
            if(b_temp_1 == b_ad_value_1)
                b_temp_cnt_1 = 0;
            if(b_temp_cnt_1 >= 0x32)
            {
                b_temp_cnt_1 = 0;
                b_temp_1 = b_ad_value_1;
                gb_wendu2 =  get_wendu2(b_temp_1);
                check_ad_ok_1=1;
            }
#endif

#endif
        }

    }
    else
    {
        b_delay_check_ad=0;
        b_temp_cnt=0;
#if	  double_ad_channel
        b_temp_cnt_1=0;
#endif
    }
}

#if		(c_ad_mode == 0)
/*-----------------------------------------------------------------
函数名称： unsigned char	get_wendu1(unsigned char ad_value)
函数功能： 将得到的ad值进行温度转换
输入参数： ad值
返 回 值： 温度值
-----------------------------------------------------------------*/
unsigned char	get_wendu1(unsigned char ad_value)
{
    unsigned char i=0;

    while(ad_value >= tab_temper[i])
    {
        i++;
        if(i >= 250) break;	//136
    }
    if(i)
        i--;
    return i;

}
#endif


#if		double_ad_channel

#if		(c_ad_mode_1 == 0)
/*-----------------------------------------------------------------
函数名称： unsigned char	get_wendu1(unsigned char ad_value)
函数功能： 将得到的ad值进行温度转换
输入参数： ad值
返 回 值： 温度值
-----------------------------------------------------------------*/
unsigned char	get_wendu2(unsigned char ad_value2)
{
    unsigned char i=0;

    while(ad_value2 >= tab_temper[i])
    {
        i++;
        if(i >= 136) break;
    }
    if(i)
        i--;
    return i;

}
#endif

#endif


#if			 c_temp_fast
/*-----------------------------------------------------------------
函数名称： unsigned char	get_wendu1(unsigned char ad_value)
函数功能： 判升温过快程序 连续2次3秒升温超过4度
输入参数：
返 回 值： 温度值
-----------------------------------------------------------------*/
void    temp_fast()
{
    if(f_mjs_power&&(!b_warning)&&(gb_wendu>=50))
    {
        if(b_error_e3>=3)
        {
            b_error_e3=0;
            if(!f_first_checke3)
            {
                if((gb_wendu>=b_wendu_old)&&(gb_wendu-b_wendu_old>=4))
                {
                    if(!f_e3_xd)
                    {
                        f_e3_xd=1;
                    }
                    else
                    {
                        b_warning |= 0X04;
                    }
                }
                else
                    f_e3_xd=0;
            }
            f_first_checke3=0;
            b_wendu_old=gb_wendu;
        }
    }
    else
    {
        b_error_e3=0;
        f_first_checke3=1;
        f_e3_xd=0;
        b_wendu_old=gb_wendu;
    }
}
#endif

#endif






/*-----------------------------------------------------------------
函数名称： void	warning_check(void)
函数功能： 检测ad值是否符合要求，否则报警
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
函数名称： void	warning_check(void)
函数功能： 检测ad值是否符合要求，否则报警
输入参数： 无
返 回 值： 无
-----------------------------------------------------------------*/

void	warning_check()
{
	/*开路报错检测*/
    if(check_ad_ok)
    {
        if(!f_mjs_power)
            b_error_sec=0;
        if(b_temp<=c_open_error)
        {
            if(b_error_sec>=c_kltime)
            {
              if(!(b_warning&0x01))
              {
                open_buz(2);	//报警音
                b_warning|=0x01;
              }
            }
        }
        else if(b_temp>c_open_error+2)
        {
            b_error_sec = 0;
		#if	c_bjhf_1	//0	 开路报警可恢复
            b_warning&=~0x01;
		#endif
        }
        
		///*短路报错检测*/
        //if(b_temp>=c_short_error)
        //{
        //  if(f_mjs_power)
        //  {
        //      if(!(b_warning&0x02))
        //      {
        //        open_buz(2);	//报警音
        //        b_warning|=0x02;
        //      }
        //  }
        //}
        //else
        //{
		//#if	c_bjhf_2	//0   //短路报警可恢复
        //    b_warning&=~0x02;
		//#endif
        //}

		/*短路报错检测*/
		/*带延时*/
        if(b_temp>=c_short_error)
        {
          if(f_mjs_power)
          {
            if(b_error_sec_1>=40)
            {

              if(!(b_warning&0x02))
              {
                open_buz(2);	//报警音
                b_warning|=0x02;
              }
            }

          }
        }
        else
        {
			b_error_sec_1=0;
		#if	c_bjhf_2	//0   //短路报警可恢复
            b_warning&=~0x02;
		#endif
        }



		///*超温报错检测*/
        //if((b_temp<c_short_error)&&(b_temp>=c_over_error))
        //{
    	//		if(f_mjs_power)
    	//		{
        //      if(!(b_warning&0x04))
        //      {
        //        open_buz(2);	//报警音
        //        b_warning|=0x04;
        //      }
		//	    }
        //}
 //       else
 //         b_warning&=~0x10;
    }

	#if	double_ad_channel
    if(check_ad_ok_1)
    {
        if(!f_mjs_power)
        	b_error_sec_1=0;
        if(b_temp_1<=c_open_error)
        {
            if(b_error_sec_1>=c_kltime)
            {
            	if(!(b_warning&0x04))
               	{
                 open_buz(2);
                 b_warning|=0x04;
               	}
            }
        }
        else if(b_temp_1>c_open_error+2)
        {
            b_error_sec_1 = 0;
		#if	c_bjhf_1
             b_warning&=~0x04;
		#endif
        }
         
        if(b_temp_1>=c_short_error)
        {
           	if(f_mjs_power)
           	{
               if(!(b_warning&0x08))
               {
                 open_buz(8);
                 b_warning|=0x08;
               }
           	}
        }
        else
        {
		#if	c_bjhf_2	//短路报警可恢复
            b_warning&=~0x08;
		#endif
        }

    }
	#endif
       

        if(b_warning!=b_warning_buf)
        {
            if(b_warning && (b_warning_buf == 0))
            {
                
            }
            else if(!b_warning && (b_warning_buf != 0))
            {
                open_buz(1);	//按键音
            }
        }

        if(b_warning)
        {
          b_quit_time++;
          if(b_quit_time>=3000)
          {
            quit_work();
            b_quit_time=0;
            b_warning=0;
          }
        }
        else
          b_quit_time=0;


        b_warning_buf=b_warning;
}
















