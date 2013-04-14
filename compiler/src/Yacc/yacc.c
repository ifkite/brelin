#include<stdio.h>
#include<string.h>
#define TERM 1
#define NTERM 0
#include "dbg.h"
#define ID_END #
#define RUL_SIZ 6
#include <vector>
#include <queue>
using std::vector;
typedef struct Identif{
	char id_nam;
	int isTerm;
}Identif;

typedef struct Rule{
	Identif left;
	vector<Identif> right;//Identif *right;
	int point_pos;
	vector<char> suffix;//char

//put things by code now
Identif id_tab[] = {
	{'E', NTERM}, {'H', NTERM}, {'T', NTERM}, {'M', NTERM}, {'F', NTERM},
	{'i', TERM}, {'+', TERM}, {'*', TERM}, {'(', TERM}, {')', TERM}
};
/*
void initId(char ch_id, int term){
}
*/
//what basic_rule table may look like

/*
Rule basic_rule[] = {
};
*/

//search id_table by ch_left
typedef vector<Rule> Node;//node of stat graph

queue<Node> que_nod;
vector<Node> vec_rul;

int findStart(char ch){
	int i;
	for(i = 0; i < RUL_SIZ; ++i){
		if(basic_rul[i].left.id_nam == ch){
			return i;
		}
	}
	return -1;
}

int chkPoint(Rule rul){
	return (rul.point_pos == rul.right.size() ? 1 : 0)
}
/*
Rule initRul(Rule _rule){	
	
}
*/
Node enclosure(Rule rul){
	//if character is not a terminal
	Node new_nod;
	if(!rul.right[point_pos].isTerm){
		int loop_basic_tab;
		char next_id_nam = rul.right[point_pos].id_nam;
		for(loop_basic_tab = 0; loop_basic_tab < RUL_SIZ; ++loop_basic_tab){
			//check rule that matchs 
			if(next_id_nam == basic_tab[loop_basic_tab].left.id_nam){
				new_nod.push_back(
						{
							basic_tab[loop_basic_tab].left,
							basic_tab[loop_basic_tab].right,
							basic_tab[loop_basic_tab].point_pos,
							rul.suffix
						}
				);
			}
		}
	}
}

int isVisit(Rule rul){
	
}
//generate nest stat node
//Rule genRul(Rule rul){
	/*
	Node tmp_nod;
	for(){
		//generate one rule first
		;//gen_rul 
		;
		if(!isVisit(gen_rule)){
			tmp_nod = enclosure(gen_rule);//enclosure will generate vector rules
			que_nod.push_back(tmp_nod);
			vec_rul.push_back(tmp_nod);
		}
	}
	que_nod.pop_back();
	*/
	//copy, and mov pointer position				
//}

int main(){
	//initlize
	char start;
	start = 'S';
	int start_rul_num;
	start_rul_num = findStart(start);//find the start rule in rule table
	//check(start_rule, "no start rule matchs");
	//init start rule
	/*
	 in pure c, written like this
	Rule start_rul = {
		.left = basic_tab[start_rul_num].left,
		.right = basic_tab[start_rul_num].right,
		.point_pos = 0
	};
	*/

	//start_rul = initRul(basic_tab[start_rul_num]);
	Rule start_rul = {
		start_rul.left = basic_tab[start_rul_num].left,
		start_rul.right = basic_tab[start_rul_num].right,
		start_rul.point_pos = 0
	};
	start_rul.suffix.push_back('ID_END');//setSufix(start_rul, "ID_END");	

	//set the succssor of start rule
	Node start_nod = enclosure(start_rul);//error here
	que_nod.push_back(start_nod);
	vec_rul.push_back(start_nod);
	//push start rule in the vector to make the first node
	//Node nod_start;
	//nod_start.push_back();
	//push first nod in queue
	Node head;//to store head of queue
	int loop_vec;
	Rule tmp_start_rul;
	Node tmp_nod;
	while(!que_nod.empty()){	
		//for all rules in head of queue, that all pointers reach the end
		head = que_nod.front();
		//chk if point reach end
		for(loop_vec = 0; loop_vec < head.size(); ++loop_vec){
			if(!chkPoint(head[loop_vec])){//if return true, then pop front of queue and give a integer value to this stat of rule and mark down
				//genRul(head[loop_vec]);
				//generate a rule
				tmp_start_rul = {
					tmp_start_rul.left = head[loop_vec].left, 
					tmp_start_rul.right = head[loop_vec].right,
					tmp_start_rul.point_pos = ++head[loop_vec].point_pos;
					tmp_start_rul.suffix = head[loop_vec].suffix
				};
				if(!isVisit(tmp_start_rul)){
					tmp_nod = enclosure(tmp_start_rul);
					que_nod.push_back(tmp_nod);
					vec_rul.push_back(tmp_nod);
					que_nod.pop_front();
				}
			}
		}
	}
	return 0;

