#ifndef _sem_h_
#define _sem_h_
#include "compile.h"
int offset;
//declaration semantic analyze
//length is the type length
void decSem(vector<int>* vec, int length){
	int i, id_pos;
	string sql_cmd;
	for(i = 0; i < vec->size();++i){
		id_pos = (*vec)[i] + 1;//get id pos in lex queue
		//get id name	
		//vec_sym[id_pos].name
		//update symbol table with length by id name
		//update offset by add length
	}
}

#endif
