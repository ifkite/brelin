#ifndef _sem_h_
#define _sem_h_
#include "compile.h"
//to use stk_input
#include "Tex.h"
int offset;
//declaration semantic analyze
//length is the type length
void decSem(vector<int>* vec,const char* length){
	int i, id_pos;
	int id_id;
	string sql_cmd, sql_suffix;
	char id_buf[8];
	for(i = 0; i < vec->size();++i){
		sql_cmd = "update symbol set offset = ";
		sql_cmd.append(length);
		sql_suffix = " where id = ";

		id_pos = (*vec)[i] + 1;//get id pos in lex queue
		//get id name	
		id_id = vec_sym[id_pos].sym_num;
		sprintf(id_buf, "%d", id_id);
		sql_suffix.append(id_buf);
		sql_cmd.append(sql_suffix);
		mysql_query(&mysql,sql_cmd.c_str());
		//update symbol table with length by id name
		//update offset by add length
		offset += atoi(length);
	}
}
int fd_sem;
int ip;//instructor pos
const char *sem_path = "./sem_res.txt";
int sem_dummy(void){
	return 0;
}
//rule factor=>num
int sem_oneargv(void){
	return stk_input.top().sem_val;
}


typedef int (*sem_func)();
//same order with rul_tab
sem_func sem_func_tab[] = {
	sem_dummy,
};

#endif
