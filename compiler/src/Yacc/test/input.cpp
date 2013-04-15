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
using std::map;
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
}

Rule basic_rul[RUL_SIZ];

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
	Identif tmp_id;
	int loop_id, loop_basic_tab = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
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
int main(){
	//initlize
	char start;
	start = 'S';
	int start_rul_num;
	initIdHash();
	getBasicRul();
	int loop_basic;
	int loop_right;
	int loop_suf;
	for(loop_basic = 0; loop_basic < RUL_SIZ; ++loop_basic){
		printf("left:%c\n", basic_rul[loop_basic].left)	;
		printf("right:");
		for(loop_right = 0; loop_right < basic_rul[loop_basic].right.size(); ++loop_right)
			printf("%c",basic_rul[loop_basic].right[loop_right].id_nam);
		printf("point pos:%d\n", basic_rul[loop_basic].point_pos);
		for(loop_suf = 0; loop_suf < basic_rul[loop_basic].suffix.size(); ++loop_suf)
			printf("%c", basic_rul[loop_basic].suffix[loop_suf]);
	}
	return 0;
}
