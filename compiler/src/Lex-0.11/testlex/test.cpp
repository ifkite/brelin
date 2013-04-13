#include<stdio.h>
#include<queue>
using std::queue;
typedef struct Symbol{
	int id_num;
	char *name;
}Symbol;
queue<Symbol> que_sym;

int main(){
	que_sym.push({1,"me"});
	printf("%d:%s\n", que_sym.back().id_num, que_sym.back().name);
	return 0;
}
