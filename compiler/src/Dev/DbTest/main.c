#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
static char * server_groups[] ={"root", (char*)NULL};
int main(){
	MYSQL sql;
	MYSQL *mysql = &sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sqlcmd[2048];
	int t, r;
	mysql_library_init(0, NULL, server_groups);
	mysql_init(mysql);
	if(!mysql_real_connect(mysql, "localhost","root","*lhh zmkM","db_symbol",0,NULL,0)){
		fprintf(stderr,"无法连接到数据库，错误原因是:%s\n",mysql_error(mysql));
	}
	else{
		printf("connect successed\n");
		sprintf(sqlcmd, "%s", "insert into symbol(class,id, name, value,offset) values('15','','num','',0)");
		int status;
		status  = mysql_query(mysql, sqlcmd);
		if(status)
			printf("insert failed\n");
		sprintf(sqlcmd, "%s","select * from symbol");
		t = mysql_real_query(mysql, sqlcmd, (unsigned int)strlen(sqlcmd));
		if(t)
			printf("query failed\n");
		else{/*{{{*/
			res=mysql_store_result(mysql);//返回查询的全部结果集
			while(row=mysql_fetch_row(res)){//mysql_fetch_row取结果集的下一行
			 for(t=0;t<mysql_num_fields(res);t++){//结果集的列的数量
			   printf("%s\t",row[t]);
			 }
			  printf("\n");
			}
			mysql_free_result(res);
		}/*}}}*/
	}
	mysql_close(mysql);
	mysql_library_end();
	return EXIT_SUCCESS;	
}
