//define lex stat
#define STAT 0     //start stat
#define SPC  1     //white space
#define SEM  2     //;
#define LBR_F 3    //( for func
#define RBR_F 4    //) for func
#define LBLK 5     //{ for ctrl blocks
#define RBLK 6     //}
#define LET  7     //letter
#define DIG  8     //digit
#define LBR_A 9    //[ for array
#define RBR_A 10   //] for array
#define ASSIN 11   // = assignment
#define EQU   12   // ==
#define ADD   13   //+
#define MIN   14   //-
#define MUT   15   //*
#define DIV   16   // /
#define NOT   17   //
#define QUO   18   //"
#define ADR   19   //& get address
#define ID_WRD 20  
#define ID_SIZ 64

#define BASE   100
#define K_VOID 100
#define K_CHAR 101
#define K_INT  102
#define K_IF   103
#define K_ELS  104
#define K_RET  105
#define K_FOR  106
#define K_CNTU 107
#define K_BRK  108
#define K_SIZ  9 //num of key word

#define SIZ   16//func_tab size
#include<ctype.h>
#include<stdio.h>
int ch;
FILE *fd;
typedef int (*isfuncs)(int);
typedef void (*handle)(void);//handle words
struct Func2num{
	isfuncs f;
	int num;
	handle hnd;//this is a patch
};


int issem(int hnd_ch){
	return (hnd_ch == ';' ? 1 : 0);//if hnd_ch is ';' then return 1
}
int islbr_f(int hnd_ch){
	return (hnd_ch == '(' ? 1 : 0);
}

int isrbr_f(int hnd_ch){
	return (hnd_ch == ')' ? 1 : 0);
}
int islblk(int hnd_ch){
	return (hnd_ch == '{' ? 1 : 0);
}
int isrblk(int hnd_ch){
	return (hnd_ch == '}' ? 1 : 0);
}
int isudline(int hnd_ch){
	return (hnd_ch == '_' ? 1 : 0);
}
int islbr_a(int hnd_ch){
	return (hnd_ch == '[' ? 1 : 0);
}
int isrbr_a(int hnd_ch){
	return (hnd_ch == ']' ? 1 : 0);
}
int isassin(int hnd_ch){
	return (hnd_ch == '=' ? 1 : 0);
}
int isadd(int hnd_ch){
	return (hnd_ch == '+' ? 1 : 0);
}
int ismin(int hnd_ch){
	return (hnd_ch == '-' ? 1 : 0);
}
int ismut(int hnd_ch){
	return (hnd_ch == '*' ? 1 : 0);
}
int isdiv(int hnd_ch){
	return (hnd_ch == '/' ? 1 : 0);
}
int isquo(int hnd_ch){
	return (hnd_ch == '"' ? 1 : 0);
}
int isadr(int hnd_ch){
	return (hnd_ch == '&' ? 1 : 0);
}
int isnline(int hnd_ch){
	return (hnd_ch == '\n' ? 1 : 0);
}
void hnd_spc(void);
void hnd_sem(void);
void hnd_lbr_f(void);
void hnd_rbr_f(void);
void hnd_lblk(void);
void hnd_rblk(void);
void hnd_let(void);
void hnd_dig(void);
void hnd_lbr_a(void);
void hnd_rbr_a(void);
void hnd_assin(void);
void hnd_add(void);
void hnd_min(void);
void hnd_div(void);
void hnd_quo(void);
void hnd_adr(void);

const struct Func2num func_tab[] = {
	{isspace, SPC, hnd_spc },
	{issem, SEM, hnd_sem},
	{islbr_f, LBR_F, hnd_lbr_f},
	{isrbr_f, RBR_F, hnd_rbr_f},
	{islblk, LBLK, hnd_lblk},
	{isrblk, RBLK, hnd_rblk},
	{isalpha, LET, hnd_let},
	{isdigit, DIG, hnd_dig},
	{islbr_a, LBR_A, hnd_lbr_a},
	{isrbr_a, RBR_A, hnd_rbr_a},
	{isassin, ASSIN, hnd_assin},
	{isadd, ADD, hnd_add},
	{ismin, MIN, hnd_min},
	{isdiv, DIV, hnd_div},
	{isquo, QUO, hnd_quo},
	{isadr, ADR, hnd_adr}
};

struct Key2id{
	char *key;
	int key_id;
};
const struct Key2id key_tab[] = {
	{"k_void", K_VOID},
	{"k_char", K_CHAR},
	{"k_int", K_INT},
	{"k_if", K_IF},
	{"k_els", K_ELS},
	{"k_ret", K_RET},
	{"k_for", K_FOR},
	{"k_cntu", K_CNTU},
	{"k_brk", K_BRK}
};
int iskeyword(char *str){//if str is a key word , return its map value,
						//els return 0
	int loop;
	for(loop = 0; loop < K_SIZ; ++loop){
		if(!strcmp(str, key_tab[loop].key))
			return key_tab[loop].key_id;
	}
	return 0;
}
