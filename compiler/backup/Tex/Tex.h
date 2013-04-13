#ifndef _Tex_h_
#define _Tex_h_

typedef struct Rule{
	char *name;
	int id_var;
	int id_quantity;
}Rule;

//rule table
const Rule rul_tab[RUL_SIZ] = {
	{"F => id\0",10, 1 },
	{"F => (E)\0",10, 3 },
	{"T => F\0", 9, 1},
	{"T => T * F\0", 9, 3},
	{"E => T\0", 8, 1},
	{"E => E + T\0", 8, 3},
	{"G => E&\0", 7, 2}
};

const int STAT_SIZ = 23;
const int ID_SIZ = 11;

const int act_tab[STAT_SIZ][ID_SIZ] = {
	0, 

}
#endif
