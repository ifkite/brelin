//search 'bug' in this file to see where they are
#define _GNU_SOURCE//?how can this works
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "dbg.h"
#define TERM 1
#define NTERM 0
#define ID_END #
#define RUL_SIZ 6

//STL
#include <vector>
#include <queue>
#include <map>
using std::vector;
using std::queue;
//this code is in c flavor, which i trying to keep
//do not use iterator for vector

typedef struct Identif{
	char id_nam;
	int isTerm;
}Identif;

typedef struct Rule{
	char left;
	vector<Identif> right;//Identif *right;
	int point_pos;
	vector<char> suffix;//char
}Rule;
//put things by code now
//should be map
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
Rule basic_rule[RUL_SIZ];

//search id_table by ch_left
typedef vector<Rule> Node;//node of stat graph

queue<Node> que_nod;
vector<Node> vec_rul;

#define ID_TAB_SIZ 10
void getBasicRul(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen("./getme", "r");
	if (fp == NULL)
		 exit(EXIT_FAILURE);
	
	int init_counter = 1;
	Rule tmp_rul;
	vector<Identif> tmp_right;
	int loop_id, loop_basic_tab = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		//initBasicRul();
		//i can do nothing but trust input, i have no time
		//how foolish bugs!!!!!
		//the normal way is to check the id_tab to see whether the
		//character we get is valid or not
		
		//now, we trust input ...
		tmp_rul.left = line[0];	
		//ugly code!!!
		//find character in map	
		while(1)
			if(line[init_counter] == '=' || line[init_counter] == '>')
				++init_counter;
			else
				break;
			
		while(1)
			if(line[init_counter] == ';')
				break;
			else{
				tmp_rul.right.push_back(line[init_counter++]);//may bug?
			}
		tmp_rul.point_pos = 0;	
		basic_tab[loop_basic_tab++] = tmp_rul;
	}
	if (line)
		 free(line);
}

int findStart(char ch){
	int i;
	for(i = 0; i < RUL_SIZ; ++i){
		if(basic_rul[i].left == ch){
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
	new_nod.push_back(rul);
	if(!rul.right[point_pos].isTerm){//???BUGS: is point_pos reach to the end
		int loop_basic_tab;
		char next_id_nam = rul.right[point_pos].id_nam;
		Rule new_rul;
		for(loop_basic_tab = 0; loop_basic_tab < RUL_SIZ; ++loop_basic_tab){
			//check rule that matchs 
			if(next_id_nam == basic_tab[loop_basic_tab].left){
				new_rul = {
			            	basic_tab[loop_basic_tab].left,
							basic_tab[loop_basic_tab].right,
							basic_tab[loop_basic_tab].point_pos,
							rul.suffix
						  };

				//find first set 
				if(++rul.point_pos < rul.right.size()){
					if(!rul.right[point_pos].isTerm){// if followed noterminal, then find the first char of rule in basic_tab
						int loop;
						/*BAD CODE: [wrong logic]:supose left values of left is unque
						for(loop = 0; loop < RUL_SIZ; ++loop){
							if(basic_tab[loop].left.id_nam == rul.right[point_pos].id_nam)
								break;
						}
						//if no left value matched, ckeck(loop == RUL_SIZ, "invalid nonterminal"); //goto error
						//we trust input now, and go on
						*/
						for(loop = 0; loop < RUL_SIZ; ++loop){
							if(basic_tab[loop].left == rul.right[point_pos].id_nam){
								new_rul.suffix.push_back(
									basic_tab[loop].right[0].id_nam;//i supposed that the first character is terminal
									//BUGS:rules have many conditions, just handle the easiest one.
									//FIX:need a func to handle this findFirstCh();
								);
							}
						}
					}
				}
				new_rul.suffix.push_back();
				
			}
		}
	}
	return new_nod;
}

//seems ok
int isRightEqu(vector<char> r1, vector<char> r2){
	if(r1.size() != r2.size())
		return 0;
	int loop_right;
	for(loop_right = 0; loop_right < r1.size(); ++loop_right)
		if(r1[loop_right] != r2[loop_right])
			return 0;
	return 1;
}

int isVisit(Rule rul){
	int loop_nod, loop_rul;//loop_nod for travel all node, loop_rul for travel rule in each nod
	//ATTENTION! BUGS HERE: 
	for(loop_nod = 0; loop_nod < vec_rul.size(); ++loop_nod){
		for(loop_rul = 0; loop_rul < vec_rul[loop_nod].size(); ++loop_rul){
			if(
					rul.point_pos == vec_rul[loop_nod][loop_rul].point_pos  &&
					rul.left == vec_rul[loop_nod][loop_rul].left &&
					isRightEqu(rul.right, vec_rul[loop_nod][loop_rul].right)
			  )
				return 1;
		}
	}
	return 0;
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
	getBasicRul();
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
	/ule start_rul = {
		start_rul.left = basic_tab[start_rul_num].left,
		start_rul.right = basic_tab[start_rul_num].right,
		start_rul.point_pos = 0
	};
	start_rul.suffix.push_back('ID_END');//setSufix(start_rul, "ID_END");	
	check(0, "checked getBasicRul");
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
error:
	return 0;
