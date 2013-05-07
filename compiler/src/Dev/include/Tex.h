#ifndef _Tex_h_
#define _Tex_h_
#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string>
using std::string;
using std::stack;



typedef struct Rule{
	const char *name;
	int id_var;
	int id_quantity;
}Rule;

//rule table
#define RUL_SIZ 35
const Rule rul_tab[RUL_SIZ] = {
{"" , 0 , 0},
{"G => Program  " , 0 , 0 },
{"Program => main ( ) Compound_stmt  " , 21 , 4},
{"Compound_stmt => { Local_declarations Statement_list }  " , 22 , 4},
{"Local_declarations => Local_declarations Var_declaration " , 23 , 2},
{"Local_declarations => Var_declaration  " , 23 , 1},
{"Var_declaration => Type_specifer identity $ " , 26, 3},
{"Type_specifer => int " , 27 , 1},
{"Type_specifer => char " , 27 , 1},
{"Type_specifer => void " , 27 , 1},
{"Statement_list => Statement_list Statement  " , 24 , 2},
{"Statement_list => Statement " , 24 , 1},
{"Statement => Expression_stmt " , 25 , 1},
{"Expression_stmt => Expression $ " , 28 , 2},
{"Expression => Var = Expression " , 29 , 3},
{"Expression => Simple_expression " , 29 , 1},
{"Simple_expression => Additive_expression " , 31 , 1},
{"Additive_expression => Additive_expression Addop Term " , 32 , 3},
{"Additive_expression => Term " , 32 , 1},
{"Addop => + " , 33 , 1},
{"Addop => - " , 33 , 1},
{"Term => Term Mulop Factor " , 34 , 3},
{"Term => Factor " , 34 , 1},
{"Mulop => * " , 35 , 1},
{"Mulop => / " , 35 , 1},
{"Mulop => % " , 35 , 1},
{"Factor => ( Expression ) " , 36 , 3},
{"Factor => Var " , 36 , 1},
{"Factor => num " , 36 , 1},
{"Var => identity " , 30 , 1},
{"Statement => If_stmt " , 25 , 1},
{"If_stmt => if ( Expression ) { Statement } " , 37 , 7},
{"If_stmt => if ( Expression ) { Statement } else { Statement } " , 37 , 11},
{"Statement => While_stmt " , 25 , 1},
{"While_stmt => while ( Expression ) { Statement } " , 38 , 7}
};

#define SHIFT 0x1000
#define REDUC 0x2000
#define ACCPT 0x4000
#define ERRTX 0x0000
//need modify
const int STAT_SIZ = 68;
const int ID_SIZ = 39;
const char *tab_path = "./gram_matrix.txt\0";
const char *input_path = "./input.txt\0";

int act_tab[STAT_SIZ][ID_SIZ];

/*
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
*/

#define EXTR_ACT 0xf000
#define EXTR_NUM 0x0fff
//Tex func
//need to be modified
//read action tab and goto tab from file
//modify act_tab in this func
//l readTab()
int readTab(void){
	FILE* file;
	file = fopen(tab_path , "r");
	if(!file){
		perror("error open file\n");
	}
	else{
		int loop_i = 0, loop_j = 0, num  = 0;
		while(fscanf(file, "%d", &num) != EOF){
			
			act_tab[loop_j][loop_i] = num;
			//read character by line
			++loop_i;
			if(! (loop_i % ID_SIZ)){
				loop_i = 0;
				++loop_j;
			}
		}
	}
	fclose(file);
	return 0;
}
//not useful anymore
//input_buf static size of memory version
/*
int readBuf(void){
	FILE *file;
	file = fopen(input_path, "r");
	if(!file){
		perror("error open input file\n");
	}
	else{
		int num = 0, i = 0, buf_siz = 1024;
		input_buf =(int *) malloc(buf_siz);
		while(fscanf(file, "%d", &num) != EOF){
			input_buf[i] = num;
			++i;
			if(i == buf_siz){
				buf_siz *= 2;
				input_buf = (int *)realloc(input_buf, buf_siz);
			}
		}
		input_buf[i] = 20;
	}
}
*/
//symbol for semantic analyze
typedef struct SemSym{
	int sym_val;//symol value, intput value form lex
	int sem_val;//value for semantic analyzing proc
	int id_id;//for id
}SemSym;
//will visited by Sem.h funcs and Tex.cpp proc
stack<SemSym> stk_input;
/*
void mypush(stack<SemSym> & stk,const int sym_val){
	SemSym tmp_sem_sym = {sym_val, 0};
	stk.push(tmp_sem_sym);
}
*/


#endif
