//define lex stat
#ifndef _Lex_h_
#define _Lex_h_
#include "compile.h"

#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string>
using std::string;
using std::stack;


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
#define ID_WRD 20  //identity
#define KWD    21
#define ID_LENGTH 64

#define BASE   100
#define K_VOID 100
#define K_CHAR 101
#define K_INT  102
#define K_IF   103
#define K_ELS  104
#define K_RET  105
#define K_WHILE  106
#define K_CNTU 107
#define K_BRK  108

//new for Tex
#define K_MAIN 109

#define K_SIZ  10 //num of key word

#define SIZ   16//func_tab size
#include<ctype.h>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<queue>
using std::queue;
using std::strcmp;
int ch;
FILE *fd;
typedef int (*isfuncs)(int);
typedef void (*handle)(void);//handle words
struct Func2num{
	isfuncs f;
	int num;
	handle hnd;//this is a patch
};

//l
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
//c
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
void hnd_mut(void);
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
	{ismut, MUT, hnd_mut},
	{isdiv, DIV, hnd_div},
	{isquo, QUO, hnd_quo},
	{isadr, ADR, hnd_adr}
};

struct Key2id{
	char *key;
	int key_id;
	int tex_num;//for tex analyze
};
//-1 for defalt, 
const struct Key2id key_tab[] = {
	{"void", K_VOID, 8},
	{"char", K_CHAR, 7},
	{"int", K_INT, 6},
	{"if", K_IF, 16},
	{"else", K_ELS, 17},
	{"ret", K_RET, -1},
	{"while", K_WHILE, 18},
	{"cntu", K_CNTU, -1},
	{"brk", K_BRK, -1},
	{"main", K_MAIN, 0}
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

//lex funcs
MYSQL mysql;
char *server_groups[] ={"root",(char*)NULL};
int initDb(void){
	void *status;
	mysql_library_init(0, NULL, server_groups);
	mysql_init(&mysql);
	status = mysql_real_connect(&mysql, "localhost","root","*lhh zmkM","db_symbol",0,NULL,0);
	if(!status){
		fprintf(stderr, "connect to db for symbol tabble:%s\n",mysql_error(&mysql));
		return -1;
	}
	//cleanDB();
	return 0;
}
void cleanDb(void){
	string sql_cmd = "delete * from symbol";
	mysql_query(&mysql, sql_cmd.c_str());
	fprintf(stderr,"clean symbol db\n");
}

void hnd_spc(void){
	//ch = fgetc(fd);//handle spc the first time
	//que_sym.push({SPC, NULL});
	//printf("white sp\n");
	while(isspace(ch = fgetc(fd)));
	//if hnd_ch is not a spc, then return, in which
	//it still retain a un spc char
	
}
void hnd_sem(void){
	vec_sym.push_back({19,NULL});
	//printf("; dected\n");
	printf("19\t");
	ch = fgetc(fd);//handle next
}
void hnd_lbr_f(void){
	vec_sym.push_back({1,NULL});
	//printf("( dected\n");
	printf("1\t");
	ch = fgetc(fd);//handle next
}
void hnd_rbr_f(void){
	vec_sym.push_back({2,NULL});
	//printf(") dected\n");
	printf("2\t");
	ch = fgetc(fd);//handle next
}
void hnd_lblk(void){
	vec_sym.push_back({3,NULL});
	//printf("{ dected\n");
	printf("3\t");
	ch = fgetc(fd);//handle next 
}
void hnd_rblk(void){
	vec_sym.push_back({4,NULL});
	//printf("} dected\n");
	printf("4\t");
	ch = fgetc(fd);//handle next
}
void hnd_let(void){
	//printf("letter dected\n");
	char id_ch[ID_LENGTH] = {'\0'};
	id_ch[0] = ch;//copy the first letter in the id
	int loop;
	for(loop = 1; loop < ID_LENGTH; ++loop){//length of word should less than ID_LENGTH 
		ch = fgetc(fd);
		if(isalpha(ch) || isdigit(ch) || isudline(ch)){
			id_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	//deal with word that's too long
	//ATTENTION!!! BUG'S HERE

	int hnd_id;	
	//distinguish keyword ro not
	if((hnd_id = iskeyword(id_ch))){
		//install keyword and id
		int tmp_tex_num = key_tab[hnd_id -BASE].tex_num;
		//que_sym.push({key_tab[hnd_id - BASE].key_id,key_tab[hnd_id - BASE].key});//seems that key character need not be passed 
		vec_sym.push_back({tmp_tex_num, NULL});
		if(tmp_tex_num == 6)
			vec_int.push_back(vec_sym.size() - 1);//record phrases 'int' position
		else if(tmp_tex_num == 7)
			vec_char.push_back(vec_sym.size() -1);
		else if(tmp_tex_num == 8)
			vec_void.push_back(vec_sym.size() - 1);
		else
			;
		//printf("%s, %d\n", key_tab[hnd_id - BASE].key, key_tab[hnd_id - BASE].key_id);
		printf("%d\t", tmp_tex_num);
	}
	else{
		string sql_cmd = ("insert into symbol(class, id, name, value, offset) values ('5', '', '");
		string sql_argv(id_ch);
		sql_cmd = sql_cmd + sql_argv + "', '',0 )" ;
		mysql_query(&mysql, sql_cmd.c_str());

		vec_sym.push_back({5,id_ch });
		
		//printf("%s,%d\n", id_ch, ID_WRD);
		printf("5\t");
	}
	
}
void hnd_dig(void){
	char dig_ch[ID_SIZ] = {'\0'};
	dig_ch[0] = ch;
	int loop;
	//can be simplied by func poiner, cuz it is like hnd_let
	for(loop = 1; loop < ID_SIZ; ++loop){
		ch = fgetc(fd);
		if(isdigit(ch)){
			dig_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	vec_sym.push_back({15, dig_ch});
	//printf("%s\n", dig_ch);
		
	printf("15\t");
}
void hnd_lbr_a(void){
	//que_sym.push({LBR_A, NULL});
	//printf("[ dected\n");
	ch = fgetc(fd);
}
void hnd_rbr_a(void){
	//que_sym.push({RBR_A, NULL});
	//printf("] dected\n");
	ch = fgetc(fd);
}
void hnd_assin(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '=';
	ch = fgetc(fd);
	if(isassin(ch)){
		hnd_ch[1] = '=';//seem no useful now
		ch = fgetc(fd);
		//que_sym.push({EQU, NULL});
		//printf("== dected\n");
	}
	else{
		vec_sym.push_back({14, NULL});
		//printf("= dected\n");
		printf("14\t");
	}
}
void hnd_add(void){
	vec_sym.push_back({9, NULL});
	//printf("+ dected\n");
	printf("9\t");
	ch = fgetc(fd);
}
void hnd_min(void){
	vec_sym.push_back({10, NULL});
	//printf("- dected\n");
	printf("10\t");
	ch = fgetc(fd);
}
void hnd_mut(void){
	vec_sym.push_back({11, NULL});
	//printf("* dected\n");
	printf("11\t");
	ch = fgetc(fd);
}
void hnd_div(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '/';
	ch = fgetc(fd);
	if(isdiv(ch)){
		hnd_ch[1] = '/';//seem no useful now
		ch = fgetc(fd);
		//que_sym.push({NOT, NULL});
		//printf("// dected\n");
		while(!isnline(ch=fgetc(fd)));//if ch is not a newline , loop
		ch = fgetc(fd);//deal with the new line
	}
	else{
		vec_sym.push_back({12, NULL});
		//printf("/ dected\n");
		printf("12\t");
	}
}
void hnd_quo(void){
	//que_sym.push({QUO, NULL});
	//printf("\" dected\n");
	ch = fgetc(fd);
}
void hnd_adr(void){
	//que_sym.push({ADR, NULL});
	//printf("& dected \n");
	ch = fgetc(fd);
}
#endif
