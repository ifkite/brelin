#include<stdio.h>
#define RUL_SIZ 7
typedef struct Rule{
	char *name;
	int id_var;
	int id_quantity;
}Rule;

const Rule rul_tab[RUL_SIZ] = {
	{"F => id\0",10, 1 },
	{"F => (E)\0",10, 3 },
	{"T => F\0", 9, 1},
	{"T => T * F\0", 9, 3},
	{"E => T\0", 8, 1},
	{"E => E + T\0", 8, 3},
	{"G => E&\0", 7, 2}
};
int main(){
	int i;
	char *ch;
	for(i = 0; i < RUL_SIZ; ++i){
		printf("%s\n",rul_tab[i].name);
	}
	
	return 0;
}
