#include "Tex.h"
#include "Lex.h"
#include "compile.h"
#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string>
using std::string;
using std::stack;
//lex funcs
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
	vec_sym.push_back({19,NULL});
	//printf("; dected\n");
	printf("19\t");
	ch = fgetc(fd);//handle next
}
void hnd_lbr_f(void){
	vec_sym.push_back({1,NULL});
	//printf("( dected\n");
	printf("1\t");
	ch = fgetc(fd);//handle next
}
void hnd_rbr_f(void){
	vec_sym.push_back({2,NULL});
	//printf(") dected\n");
	printf("2\t");
	ch = fgetc(fd);//handle next
}
void hnd_lblk(void){
	vec_sym.push_back({3,NULL});
	//printf("{ dected\n");
	printf("3\t");
	ch = fgetc(fd);//handle next 
}
void hnd_rblk(void){
	vec_sym.push_back({4,NULL});
	//printf("} dected\n");
	printf("4\t");
	ch = fgetc(fd);//handle next
}
void hnd_let(void){
	//printf("letter dected\n");
	char id_ch[ID_LENGTH] = {'\0'};
	id_ch[0] = ch;//copy the first letter in the id
	int loop;
	for(loop = 1; loop < ID_LENGTH; ++loop){//length of word should less than ID_LENGTH 
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
		vec_sym.push_back({key_tab[hnd_id -BASE].tex_num, NULL});
		//printf("%s, %d\n", key_tab[hnd_id - BASE].key, key_tab[hnd_id - BASE].key_id);
		printf("%d\t", key_tab[hnd_id - BASE].tex_num);
	}
	else{
		string sql_cmd = ("insert into symbol(class, id, name, value, offset) values ('5', '', '");
		string sql_argv(id_ch);
		sql_cmd = sql_cmd + sql_argv + "', '',0 )" ;
		mysql_query(&mysql, sql_cmd.c_str());

		vec_sym.push_back({5,id_ch });
		
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
	vec_sym.push_back({15, dig_ch});
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
		vec_sym.push_back({14, NULL});
		//printf("= dected\n");
		printf("14\t");
	}
}
void hnd_add(void){
	vec_sym.push_back({9, NULL});
	//printf("+ dected\n");
	printf("9\t");
	ch = fgetc(fd);
}
void hnd_min(void){
	vec_sym.push_back({10, NULL});
	//printf("- dected\n");
	printf("10\t");
	ch = fgetc(fd);
}
void hnd_mut(void){
	vec_sym.push_back({11, NULL});
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
		vec_sym.push_back({12, NULL});
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

//Tex func
//need to be modified
//read action tab and goto tab from file
//modify act_tab in this func
//l readTab()
static int readTab(void){
	FILE* file;
	file = fopen(tab_path , "r");
	if(!file){
		perror("error open file\n");
	}
	else{
		int loop_i = 0, loop_j = 0, num  = 0;
		while(fscanf(file, "%d", &num) != EOF){
			
			act_tab[loop_j][loop_i] = num;
			//read character by line
			++loop_i;
			if(! (loop_i % ID_SIZ)){
				loop_i = 0;
				++loop_j;
			}
		}
	}
	fclose(file);
	return 0;
}
static int *input_buf;
//input_buf static size of memory version

static int readBuf(void){
	FILE *file;
	file = fopen(input_path, "r");
	if(!file){
		perror("error open input file\n");
	}
	else{
		int num = 0, i = 0, buf_siz = 1024;
		input_buf =(int *) malloc(buf_siz);
		while(fscanf(file, "%d", &num) != EOF){
			input_buf[i] = num;
			++i;
			if(i == buf_siz){
				buf_siz *= 2;
				input_buf = (int *)realloc(input_buf, buf_siz);
			}
		}
		input_buf[i] = 20;
	}
}

//c
//const int BUF_SIZ = 128;
//int input_buf[BUF_SIZ] = {0, 1, 2, 3, 6, 5, 19, 7, 5, 19, 5, 14, 15,19, 16, 1,5, 14, 15, 2, 3,18,1,5,14,15,2,3,5,14, 15, 19, 4 ,4, 4, 20 };
//int input_buf[BUF_SIZ] = {0,1,2,3,6,5,14,15,19,16,1,5,14,15,2,3,18,1,5,14,15,2,3,16,5,14,15,19,4,4,5,14,5,9,5,11,5,19,5,14,5,9,5,19,4};
int main(){
	//Lex, output is que_sym, which is shared in .h file
	{	//read file 
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
		vec_sym.push_back({20,NULL});
		int i;
		for(i = 0; i < vec_sym.size(); ++i){
			fprintf(stderr,"%d\t", vec_sym[i].id_num);
		}
		fclose(fd);
	}

	//Tex
	{
		readTab();
		//readBuf();
		
		int buf;
		stack<int> stk_stat;
		stack<int> stk_input;
		stk_stat.push(0);//0 is start state
		buf = vec_sym[0].id_num;
		int handle;
		int action;
		int stat;
			
		if(buf != -1){
			int next = 1;//next points to the one next to buf
			int flag = 1;
			while(flag){
			
				//when get the value of state and buffer, we can search table
				//handle = searchActTab();
				handle = act_tab[stk_stat.top()][buf];
				//extract action and state num , which are stored in table
				
				//action = handle & EXTR_ACT; 
				//stat = handle & EXTR_NUM;

				//in a common way
				if(handle > 0){
					if(handle == ACCPT)
						action = ACCPT;
					else
						action = SHIFT;
				}
				else if(handle < 0){
					action = REDUC;
				}
				else
					action = ERRTX;
				//common way

				stat = abs(handle);
				switch(action){
					case SHIFT:	{
						printf("shift\n");
						//only SHIFT action can modify buf and the move the pointer, the pointer points to ele next to buf

						//push buf in stk_input, and input_buf[next] copy to buf, move next , ATTENTION:   MAYBE BUGS HERE!!!!
						//push stat in stk_stat
						stk_input.push(buf);
						buf = vec_sym[next].id_num;
						if(buf)
							++next;
						stk_stat.push(stat);
						break;
					}
					case REDUC: {
						//searchRuleTab();
						int pop_time, left_exp, rul_num;
						rul_num = stat;
						pop_time = rul_tab[rul_num].id_quantity;
						left_exp = rul_tab[rul_num].id_var;
						printf("%s\n", rul_tab[rul_num].name);
						int loop;
						//then pop stat and input in stack by rule
						for(loop = 0; loop < pop_time; ++loop){
							stk_stat.pop();
							stk_input.pop();
						}
						//push left express to input stack
						stk_input.push(left_exp);
						
						int next_stat;
						//search gotoTab, get the next stat value
						next_stat = act_tab[stk_stat.top()][left_exp];
						//push the next stat value into stk_stat
						stk_stat.push(next_stat);
						break;
					}
					//l case Accept
					case ACCPT: {
						printf("Accept!\n");
						flag = 0;
						break;
					}
					//c
					//l case default
					 default: {
						//error
						fprintf(stderr, "syntax error eccored\n");
						fprintf(stderr, "saddly, i can not tell you the line now\n");
						flag = 0;
						break;
					}	
					//c
				}
			}	
		}
	}
	
	return 0;
}
