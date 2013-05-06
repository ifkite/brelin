#ifndef _compile_h_
#define _compile_h_
#include<vector>
using std::vector;
typedef struct Symbol{
	int id_num;
	char *name;
}Symbol;
vector<Symbol> vec_sym;
vector<int> vec_int;
vector<int> vec_char;
vector<int> vec_void;
#endif
