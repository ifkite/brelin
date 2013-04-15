#include<stdio.h>

#include<vector>
using std::vector;

typedef struct Id{
	int a;
	char ch;
	//vector<char> str;
}Id;

int main(){
	Id id1 = {id1.a = 1};
	Id id2 = {id2.a = id1.a, id2.ch = id1.ch};
	//id2.str.push_back('s');
	printf("%d:%c%c\n", id2.a, id1.ch);
	return 0;
}
