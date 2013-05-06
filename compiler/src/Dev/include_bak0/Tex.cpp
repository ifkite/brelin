#include "Tex.h"
#include "Lex.h"
#include "compile.h"
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
		fclose(fd);
	}

	//Tex
	{
		//declaration semantic analyze
		//deSem(vec_int,4);
		//decSem(vec_char, 1);
		//decSem(vec_void,1);
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
