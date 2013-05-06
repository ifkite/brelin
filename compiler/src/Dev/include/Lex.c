#include "Lex.h"
#include<mysql.h>

#include<string>
using std::string;


static MYSQL mysql;
static char *server_groups[] ={"root",(char*)NULL};
int initDb(void){
	void *status;
	mysql_library_init(0, NULL, server_groups);
	mysql_init(&mysql);
	status = mysql_real_connect(&mysql, "localhost","root","*lhh zmkM","db_symbol",0,NULL,0);
	if(!status){
		fprintf(stderr, "connect to db for symbol tabble:%s\n",mysql_error(&mysql));
		return -1;
	}
	//cleanDB();
	return 0;
}
void cleanDb(void){
	string sql_cmd = "delete * from symbol";
	mysql_query(&mysql, sql_cmd.c_str());
	fprintf(stderr,"clean symbol db\n");
}

void hnd_spc(void){
	//ch = fgetc(fd);//handle spc the first time
	//que_sym.push({SPC, NULL});
	//printf("white sp\n");
	while(isspace(ch = fgetc(fd)));
	//if hnd_ch is not a spc, then return, in which
	//it still retain a un spc char
	
}
void hnd_sem(void){
	que_sym.push({19,NULL});
	//printf("; dected\n");
	printf("19\t");
	ch = fgetc(fd);//handle next
}
void hnd_lbr_f(void){
	que_sym.push({1,NULL});
	//printf("( dected\n");
	printf("1\t");
	ch = fgetc(fd);//handle next
}
void hnd_rbr_f(void){
	que_sym.push({2,NULL});
	//printf(") dected\n");
	printf("2\t");
	ch = fgetc(fd);//handle next
}
void hnd_lblk(void){
	que_sym.push({3,NULL});
	//printf("{ dected\n");
	printf("3\t");
	ch = fgetc(fd);//handle next 
}
void hnd_rblk(void){
	que_sym.push({4,NULL});
	//printf("} dected\n");
	printf("4\t");
	ch = fgetc(fd);//handle next
}
void hnd_let(void){
	//printf("letter dected\n");
	char id_ch[ID_SIZ] = {'\0'};
	id_ch[0] = ch;//copy the first letter in the id
	int loop;
	for(loop = 1; loop < ID_SIZ ; ++loop){//length of word should less than ID_SIZ	
		ch = fgetc(fd);
		if(isalpha(ch) || isdigit(ch) || isudline(ch)){
			id_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	//deal with word that's too long
	//ATTENTION!!! BUG'S HERE

	int hnd_id;	
	//distinguish keyword ro not
	if((hnd_id = iskeyword(id_ch))){
		//install keyword and id

		//que_sym.push({key_tab[hnd_id - BASE].key_id,key_tab[hnd_id - BASE].key});//seems that key character need not be passed 
		que_sym.push({key_tab[hnd_id -BASE].tex_num, NULL});
		//printf("%s, %d\n", key_tab[hnd_id - BASE].key, key_tab[hnd_id - BASE].key_id);
		printf("%d\t", key_tab[hnd_id - BASE].tex_num);
	}
	else{
		string sql_cmd = ("insert into symbol(class, id, name, value, offset) values ('5', '', '");
		string sql_argv(id_ch);
		sql_cmd = sql_cmd + sql_argv + "', '',0 )" ;
		mysql_query(&mysql, sql_cmd.c_str());

		que_sym.push({5,id_ch });
		
		//printf("%s,%d\n", id_ch, ID_WRD);
		printf("5\t");
	}
	
}
void hnd_dig(void){
	char dig_ch[ID_SIZ] = {'\0'};
	dig_ch[0] = ch;
	int loop;
	//can be simplied by func poiner, cuz it is like hnd_let
	for(loop = 1; loop < ID_SIZ; ++loop){
		ch = fgetc(fd);
		if(isdigit(ch)){
			dig_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	que_sym.push({15, dig_ch});
	//printf("%s\n", dig_ch);
		
	printf("15\t");
}
void hnd_lbr_a(void){
	//que_sym.push({LBR_A, NULL});
	//printf("[ dected\n");
	ch = fgetc(fd);
}
void hnd_rbr_a(void){
	//que_sym.push({RBR_A, NULL});
	//printf("] dected\n");
	ch = fgetc(fd);
}
void hnd_assin(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '=';
	ch = fgetc(fd);
	if(isassin(ch)){
		hnd_ch[1] = '=';//seem no useful now
		ch = fgetc(fd);
		//que_sym.push({EQU, NULL});
		//printf("== dected\n");
	}
	else{
		que_sym.push({14, NULL});
		//printf("= dected\n");
		printf("14\t");
	}
}
void hnd_add(void){
	que_sym.push({9, NULL});
	//printf("+ dected\n");
	printf("9\t");
	ch = fgetc(fd);
}
void hnd_min(void){
	que_sym.push({10, NULL});
	//printf("- dected\n");
	printf("10\t");
	ch = fgetc(fd);
}
void hnd_mut(void){
	que_sym.push({11, NULL});
	//printf("* dected\n");
	printf("11\t");
	ch = fgetc(fd);
}
void hnd_div(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '/';
	ch = fgetc(fd);
	if(isdiv(ch)){
		hnd_ch[1] = '/';//seem no useful now
		ch = fgetc(fd);
		//que_sym.push({NOT, NULL});
		//printf("// dected\n");
		while(!isnline(ch=fgetc(fd)));//if ch is not a newline , loop
		ch = fgetc(fd);//deal with the new line
	}
	else{
		que_sym.push({12, NULL});
		//printf("/ dected\n");
		printf("12\t");
	}
}
void hnd_quo(void){
	//que_sym.push({QUO, NULL});
	//printf("\" dected\n");
	ch = fgetc(fd);
}
void hnd_adr(void){
	//que_sym.push({ADR, NULL});
	//printf("& dected \n");
	ch = fgetc(fd);
}



int main(int argc, char **argv){
	//read file 
	//open file
	initDb();//for connecting db server
	cleanDb();//clean all data
	fd = fopen("./test.me", "r");//need to modify
	if (!fd)
		perror("error opening file");//return //
	else{//not null
		ch = fgetc(fd);
		int loop;
		while(ch != EOF){//not to the end of file
			for(loop = 0; loop < SIZ; ++loop){//which init value should loop assgined
				if((*func_tab[loop].f)(ch)){
					(*func_tab[loop].hnd)();
					break;
				}
			}
		}
		//printf("find eof\n");
	}
	//bad code style
	que_sym.push({20,NULL});
	fclose(fd);
	return 0;
}