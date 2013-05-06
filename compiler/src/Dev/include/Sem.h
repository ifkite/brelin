#ifndef _sem_h_
#define _sem_h_
#include "compile.h"
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
		printf("should have 2 id_id\n");
		fprintf(stderr, "%d\n", id_id);
		sql_suffix.append(id_buf);
		sql_cmd.append(sql_suffix);
		mysql_query(&mysql,sql_cmd.c_str());
		//update symbol table with length by id name
		//update offset by add length
		offset += atoi(length);
	}
}

#endif
