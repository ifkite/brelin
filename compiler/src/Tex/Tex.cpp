#include "Tex.h"
#include<stack>
#include<stdio.h>
using std::stack;
/*
void init_input(int *buf, const int size){
	int i;
	for(i = 0; i < size; ++i)
		buf[i] = 0;
}
*/
//need to be modified
const int BUF_SIZ = 128;
int input_buf[BUF_SIZ] = {L_BR, ID , ADD, ID, R_BR, MUT, ID, SPC, END};
int main(){
	int buf;
	stack<int> stk_stat;
	stack<int> stk_input;
	stk_stat.push(0);//0 is start state
	buf = input_buf[0];
	int handle;
	int action;
	int stat;
	if(buf){
		int next = 1;//next points to the one next to buf
		int flag = 1;
		while(flag){
		
			//readBuf();//read buffer
			//readStat();//read state in stack
			//stk_stat.top()	

			//when get the value of state and buffer, we can search table
			//handle = searchActTab();
			handle = act_tab[stk_stat.top()][buf];
			//extract action and state num , which are stored in table
			action = handle & EXTR_ACT; 
			stat = handle & EXTR_NUM;

			switch(action){
				case SHIFT:	{
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
				case ACCPT: {
					printf("Accept!\n");
					flag = 0;
					break;
				}
				default: {
					//error
					fprintf(stderr, "syntax error eccored\n");
					fprintf(stderr, "saddly, i can not tell you the line now\n");
					flag = 0;
					break;
				}	
			}
		}	
	}
	return 0;
}
