#ifndef _Tex_h_
#define _Tex_h_

typedef struct Rule{
	const char *name;
	int id_var;
	int id_quantity;
}Rule;

//rule table
#define RUL_SIZ 45
const Rule rul_tab[RUL_SIZ] = {

	{"Program => main ( ) Compound_stmt ", 30, 4 },
	{"Compound_stmt => { Declaration_list Statement_list }  " , 31, 4},
	{"Declaration_list =>  Declaration_list  Declaration " , 32, 2},
	{"Declaration_list => Declaration " , 32, 1},
	{"Declaration => Var_declaration " , 39, 1},
	{"Var_declaration => Type_specifer Identity # " , 40, 3},
	{"Var_declaration =>  Type_specifer Identity [ ] # " , 40, 5},
	{"Type_specifer => int " , 41, 1},
	{"Type_specifer => char " , 41, 1},
	{"Statement_list => Statement_list Statement " , 33, 1},
	{"Statement_list => Statement " , 33, 1},
	{"Statement => Expression_stmt " , 34, 1},
	{"Statement => If_stmt " , 34, 1},
	{"Statement => While_stmt " , 34, 1},
	{"Expression_stmt => Expression # ", 35, 2},
	{"Expression_stmt => # ", 35, 1},
	{"If_stmt => if ( Expression ) { Statement } ", 36, 7 },
	{"If_stmt => if ( Expression ) { Statement } else { Statement } ", 36, 11},
	{"While_stmt => while ( Expression ) { Statement } ", 37, 7},
	{"Expression => Var = Expression ", 38, 3},
	{"Expression => Simple_expression ", 38, 1},
	{"Expression => Simple_expression and Simple_expression ", 38, 3},
	{"Expression => Simple_expression or Simple_expression ", 38, 3},
	{"Expression => not Simple_expression  ", 38, 2},
	{"Var => Identity ", 42, 1},
	{"Var => Identity [ Expression ] ", 42, 4},
	{"Simple_expression => Additive_expression Relop Additive_expression ", 43, 3 },
	{"Simple_expression => Additive_expression ", 43, 1},
	{"Relop => <= ", 45, 1},
	{"Relop => < ", 45, 1},
	{"Relop => == ", 45, 1},
	{"Relop => > ", 45, 1},
	{"Relop => >= ", 45, 1},
	{"Relop => != ", 45, 1},
	{"Additive_expression => Additive_expression Addop Term ", 44, 3},
	{"Additive_expression  => Term ", 44, 1},
	{"Addop => + ", 46, 1},
	{"Addop => - ", 46, 1},
	{"Term => Term Mulop Factor ", 47, 3},
	{"Term => Factor ", 47, 1},
	{"Mulop => * ", 48, 1},
	{"Mulop => / ", 48, 1},
	{"Mulop => % ", 48, 1},
	{"Factor => ( Expression ) ", 49, 3},
	{"Factor=> Var ", 49, 1}
};

#define SHIFT 0x1000
#define REDUC 0x2000
#define ACCPT 0x4000
#define ERRTX 0x0000
//need modify
const int STAT_SIZ = 310;
const int ID_SIZ = 50;
const char *tab_path = "./tab_first.txt\0";

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

#endif
