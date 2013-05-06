#include<string>
#include<stdio.h>
using std::string;

int main(){
	string sql_cmd = ("insert into symbol(class, id, name, value, offset) values ('5', '', '");
	char *id_ch = "num";
	string sql_argv(id_ch);
	sql_cmd = sql_cmd + sql_argv + "', '',0 )" ;
	printf("%s\n",sql_cmd.c_str());
	return 0;
}
