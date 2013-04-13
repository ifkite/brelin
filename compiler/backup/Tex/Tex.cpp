#include<stack>
#include<cstdio>
using namespace std;
#define END 0
#define ID  1
#define ADD 2
#define MUT 3
#define L_BR 4
#define R_BR 5
#define SPC  6
#define GEN  7
#define EXP  8
#define TRM  9
#define FNL  10
#define EXTR_ACT 0xf000
#define EXTR_NUM 0x0fff
#define SHIFT 0x1000
#define REDUC 0x2000
#define ACCPT 0x4000
#define ERRTX 0x0000
/*
void init_input(int *buf, const int size){
	int i;
	for(i = 0; i < size; ++i)
		buf[i] = 0;
}
*/
//need to be modified
const int BUF_SIZ = 128;
int input_buf[BUF_SIZ] = {ID , ADD, ID, MUT, ID, SPC};
int main(){
	int buf;
	stack<int> stk_stat;
	stack<int> stk_input;
	stk_stat.push(0);//0 is start state
	buf = input_buf[0];
	int handle;
	int action;
	int stat;
	if(!buf){
		int next = 1;//next points to the one next to buf

		while(1){
		
			readBuf();//read buffer
			readStat();//read state in stack
			handle = searchActTab();//when get the value of state and buffer, we can search table
			//extract action and state num , which are stored in table
			action = handle & EXTR_ACT; 
			stat = handle & EXTR_NUM;

			switch(action){
				case SHIFT:	{
					//only SHIFT action can modify buf and the move the pointer, the pointer points to ele next to buf

					//push buf in stk_input, and input_buf[next] copy to buf, move next , ATTENTION:   MAYBE BUGS HERE!!!!
					//push stat in stk_stat
					break;
				}
				case REDUC: {
					searchRuleTab();
					//then pop stat and input in stack by rule
					//push left express to input stack
					//search gotoTab, get the next stat value
					//push the next stat value into buf
				}
				case ACCPT: {
				}
				default: {
				//error
				}	
			}
		}	
	}
	return 0;
}
