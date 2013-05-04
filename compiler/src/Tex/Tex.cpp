#include "Tex.h"
#include<stack>
#include<stdio.h>
#include<stdlib.h>
using std::stack;

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
	readTab();
	readBuf();
	
	int buf;
	stack<int> stk_stat;
	stack<int> stk_input;
	stk_stat.push(0);//0 is start state
	buf = input_buf[0];
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
					buf = input_buf[next];
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
	return 0;
}
