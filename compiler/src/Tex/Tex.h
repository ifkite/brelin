#ifndef _Tex_h_
#define _Tex_h_

typedef struct Rule{
	const char *name;
	int id_var;
	int id_quantity;
}Rule;

//rule table
#define RUL_SIZ 7
const Rule rul_tab[RUL_SIZ] = {
	{"F => id\0",10, 1 },	//0
	{"F => (E)\0",10, 3 },	//1
	{"T => F\0", 9, 1},		//2
	{"T => T * F\0", 9, 3},	//3
	{"E => T\0", 8, 1},		//4
	{"E => E + T\0", 8, 3},	//5
	{"G => E&\0", 7, 2}		//6
};

#define SHIFT 0x1000
#define REDUC 0x2000
#define ACCPT 0x4000
#define ERRTX 0x0000
const int STAT_SIZ = 24;
const int ID_SIZ = 11;

const int act_tab[STAT_SIZ][ID_SIZ] = {
//  #	  , id	  , +	 , *	, (		,)	  , &	 , G 
	{0	  , 0x1005,0	 , 0	,0x1006,0	  ,0	 ,1,2,3,4},
	{ACCPT, 0	  ,0	 , 0	,0     ,0	  ,0	 ,0,0,0,0},
	{0	  , 0	  ,0x1007, 0	,0	   ,0	  ,0x1008,0,0,0,0},
	{0	  , 0	  ,0x2004,0x1009,0	   ,0     ,0x2004,0,0,0,0},
	{0	  , 0	  ,0x2002,0x2002,0	   ,0     ,0x2002,0,0,0,0},
	{0	  , 0	  ,0x2000,0x2000,0	   ,0	  ,0x2000,0,0,0,0},
	{0	  , 0x100D,0	 ,0		,0x100E,0	  ,0	 ,0,10,11,12},
	{0	  , 0x1005,0	 ,0		,0x1006,0	  ,0	 ,0,0,15,4},
	{0x2006, 0	  ,0	 ,0		,0	   ,0	  ,0	 ,0,0,0,0},
	{0	  , 0x1005,0	 ,0		,0x1006,0	  ,0	 ,0,0,0,16},
	{0	  , 0	  ,0x1011,0		,0	   ,0x1012,0	 ,0,0,0,0},
	{0	  , 0	  ,0x2004,0x1013,0	   ,0x2004,0	 ,0,0,0,0},
	{0	  , 0	  ,0x2002,0x2002,0	   ,0x2002,0	 ,0,0,0,0},
	{0	  , 0	  ,0x2000,0x2000,0	   ,0x2000,0	 ,0,0,0,0},
	{0	  , 0x100D,0	 ,0		,0x100E,0	  ,0	 ,0,20,11,12},
	{0	  ,0	  ,0x2005,0x1009,0	   ,0	  ,0x2005,0,0,0,0},
	{0	  ,0	  ,0x2003,0x2003,0	   ,0	  ,0x2003,0,0,0,0},
	{0	  ,0x100D ,0	 ,0		,0x100E,0	  ,0	 ,0,0,21,12},
	{0	  ,0	  ,0x2001,0x2001,0	   ,0	  ,0x2001,0,0,0,0},
	{0	  ,0x100D ,0	 ,0		,0x100E,0	  ,0	 ,0,0,0,22},
	{0	  ,0	  ,0x1007,0		,0	   ,0x2017,0	 ,0,0,0,0},
	{0	  ,0	  ,0x2005,0x1013,0	   ,0x2005,0	 ,0,0,0,0},
	{0	  ,0	  ,0x2003,0x2003,0	   ,0x2003,0	 ,0,0,0,0},
	{0	  ,0	  ,0x2001,0x2001,0	   ,0x2001,0	 ,0,0,0,0}
};

#define END 0
#define ID  1
#define ADD 2
#define MUT 3
#define L_BR 4
#define R_BR 5
#define SPC  6
#define GEN  7
#define EXP  8
#define TRM  9
#define FNL  10
#define EXTR_ACT 0xf000
#define EXTR_NUM 0x0fff

#endif