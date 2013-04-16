//search 'bug' in this file to see where they are
#define _GNU_SOURCE//?how can this works
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "dbg.h"
#define TERM 1
#define NTERM 0
#define ID_END #
#define RUL_SIZ 9

//STL
#include <vector>
#include <queue>
#include <map>
using std::vector;
using std::queue;
using std::map;
//this code is in c flavor, which i trying to keep
//do not use iterator for vector

typedef struct Identif{
	char id_nam;
	int isTerm;
}Identif;

//right should be char*
typedef struct Rule{
	char left;
	int point_pos;
	vector<Identif> right;//Identif *right;
	vector<char> suffix;//char
}Rule;

map<char, int> id_hash;
void initIdHash(void){

	//ugly code, should use loop to replace this
	id_hash['E'] = NTERM;
	id_hash['H'] = NTERM;
	id_hash['T'] = NTERM;
	id_hash['M'] = NTERM;
	id_hash['F'] = NTERM;
	id_hash['i'] = TERM;
	id_hash['+'] = TERM;
	id_hash['*'] = TERM;
	id_hash['('] = TERM;
	id_hash[')'] = TERM;
	id_hash['#'] = TERM;
}

Rule basic_rul[RUL_SIZ];

//search id_table by ch_left
typedef vector<Rule> Node;//node of stat graph

queue<Node> que_nod;
vector<Node> vec_rul;

#define ID_TAB_SIZ 11
void getBasicRul(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen("./getme", "r");
	if (fp == NULL)
		 exit(EXIT_FAILURE);
	
	int line_counter;
	Rule tmp_rul;
	vector<Identif> tmp_right;
	Identif tmp_id;
	int loop_id, loop_basic_tab = 0;
	
	while ((read = getline(&line, &len, fp)) != -1) {
		/*
		tmp_rul.left = line[0];	
		while(1)
			if(line[init_counter] == '=' || line[init_counter] == '>')
				++init_counter;
			else
				break;
			
		while(1)
			if(line[init_counter] == ';')
				break;
			else{
				tmp_id.id_nam = line[init_counter];
				tmp_id.isTerm = id_hash.find(line[init_counter])->second;
				++init_counter;
				tmp_rul.right.push_back(tmp_id);
			}
		tmp_rul.point_pos = 0;	
		basic_rul[loop_basic_tab++] = tmp_rul;
		*/	
		line_counter = 3;//right id begin with 3
		tmp_rul.left = line[0];
		while(1){
			if(line[line_counter] == ';'){
				break;
			}
			else{
				tmp_id.id_nam = line[line_counter];
				tmp_id.isTerm = id_hash.find(line[line_counter])->second;
				++line_counter;
				tmp_rul.right.push_back(tmp_id);
			}
		}
		tmp_rul.point_pos = 0;
		basic_rul[loop_basic_tab++] = tmp_rul;
		tmp_rul.right.clear();
	}
	
/*	
	while ((read = getline(&line, &len, fp)) != -1) {
		init_counter = 0;
		while(1){
			if(line[init_counter] == ';')	
				break;
			else{
				printf("%c", line[init_counter]);
				++init_counter;
			}
		}
		printf("\n");
	}
*/
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
	return (rul.point_pos == rul.right.size() ? 1 : 0);
}
Node enclosure(Rule rul){
	//if character is not a terminal
	Node new_nod;
	new_nod.push_back(rul);
	if(!rul.right[rul.point_pos].isTerm){//???BUGS: is point_pos reach to the end
		int loop_basic_tab;
		char next_id_nam = rul.right[rul.point_pos].id_nam;
		Rule new_rul;
		for(loop_basic_tab = 0; loop_basic_tab < RUL_SIZ; ++loop_basic_tab){
			//find the next rule
			//check rule that matchs 
			if(next_id_nam == basic_rul[loop_basic_tab].left){
				new_rul.left = basic_rul[loop_basic_tab].left;
				new_rul.right = basic_rul[loop_basic_tab].right;
				new_rul.point_pos = basic_rul[loop_basic_tab].point_pos;
				new_rul.suffix = rul.suffix;
				//find first set 
				if(rul.point_pos + 1 < rul.right.size()){
					if(!rul.right[rul.point_pos].isTerm){// if followed noterminal, then find the first char of rule in basic_tab
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
							if(basic_rul[loop].left == rul.right[rul.point_pos].id_nam){
								//i need chk if the suffix is in the vector already or the first of right is null
								//chkSuf();
								new_rul.suffix.push_back(
									basic_rul[loop].right[0].id_nam//i supposed that the first character is terminal
									//BUGS:rules have many conditions, just handle the easiest one.
									//FIX:need a func to handle this findFirstCh();
								);
							}
						}
					}
					else{
						//i need chk if the suffix is in the vector already
						//chkSuf();
						new_rul.suffix.push_back(rul.right[rul.point_pos].id_nam);
					}
				}
				//BUG:should check if this nod is in nod already
				new_nod.push_back(new_rul);
			}
		}
	}
	return new_nod;
}

//seems ok
int isRightEqu(vector<Identif> r1, vector<Identif> r2){
	if(r1.size() != r2.size())
		return 0;
	int loop_right;
	for(loop_right = 0; loop_right < r1.size(); ++loop_right)
		if(r1[loop_right].id_nam != r2[loop_right].id_nam)
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

int main(){
	char start;
	start = 'S';
	int start_rul_num;
	initIdHash();
	getBasicRul();
	int loop_basic;
	int loop_right;
	int loop_suf;
	start_rul_num = findStart(start);//find the start rule in rule table
	Rule start_rul; 
	start_rul.left = basic_rul[start_rul_num].left;
	start_rul.right = basic_rul[start_rul_num].right;
	start_rul.point_pos = 0;		
	start_rul.suffix.push_back('#');

	Node start_nod = enclosure(start_rul);//error here
	int loop_nod;
	/*
	for(loop_nod = 0; loop_nod < start_nod.size(); ++loop_nod){
		printf("left:%c\nright:", start_nod[loop_nod].left);
		for(loop_right = 0; loop_right < start_nod[loop_nod].right.size(); ++loop_right)
			printf("%c", start_nod[loop_nod].right[loop_right].id_nam);
		printf("\n");
		for(loop_suf = 0; loop_suf < start_nod[loop_nod].suffix.size(); ++loop_suf)	
			printf("%c", start_nod[loop_nod].suffix[loop_suf]);
		printf("\n");
	}
	*/
	que_nod.push(start_nod);
	vec_rul.push_back(start_nod);
	return 0;
}
