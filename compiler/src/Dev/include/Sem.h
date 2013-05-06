#ifndef _sem_h_
#define _sem_h_
#include "compile.h"
int offset;
//declaration semantic analyze
//length is the type length
void decSem(vector<int>* vec,const char* length){
	int i, id_pos;
	int id_num;
	string sql_cmd, sql_suffix, id_nam;
	sql_cmd = "update symbol set offset = ";
	sql_cmd.append(length);
	sql_suffix = "where name = ' ";
	for(i = 0; i < vec->size();++i){
		id_pos = (*vec)[i] + 1;//get id pos in lex queue
		fprintf(stderr,"int pos %d\n",(*vec)[i]);
		//get id name	
		//id_nam = vec_sym[id_pos].name;
		sql_suffix.append(id_nam);
		sql_suffix.append("'");
		sql_cmd.append(sql_suffix);
		mysql_query(&mysql,sql_cmd.c_str());
		//update symbol table with length by id name
		//update offset by add length
		offset += atoi(length);
	}
}

#endif
