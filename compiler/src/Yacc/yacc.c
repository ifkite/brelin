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
/*
Rule initRul(Rule _rule){	
	
}
*/
Node enclosure(Rule rul){
}

isVisit(Rule rul){
}
//generate nest stat node
void genNode(Node node){
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
}

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
	while(!que_nod.empty()){	
		//for all rules in head of queue, that all pointers reach the end
		head = que_nod.front();
		//chk if point reach end
		if(chkPoint(head)){//if return true, then pop front of queue and give a integer value to this stat of rule and mark down
		}
		else{
			genNode(head);
		}
	}
	return 0;

