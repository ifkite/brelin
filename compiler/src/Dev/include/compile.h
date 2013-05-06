#ifndef _compile_h_
#define _compile_h_
#include<vector>
using std::vector;
typedef struct Symbol{
	int id_num;
	//char *name;
	int sym_num;
	//explaintion: sym_num
	//if id is a letter and it is 
	//an identity, then sym_num will
	//be its identifer
	//else, in digit , it will be the
	//value of digit
	//default, no value
}Symbol;
vector<Symbol> vec_sym;
vector<int> vec_int;
vector<int> vec_char;
vector<int> vec_void;
#endif
