#ifndef _Tex_h_
#define _Tex_h_

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

#endif
