#include<vector>
#include<stdio.h>
using std::vector;
typedef struct wapper{
	int i;
	char* name;
}wapper;
vector<wapper> bad_que;

int func(){
	static char p[64];
	p[0]='l';
	p[1]='a';
	p[2]='l';
	p[3]='a';
	p[4]='\0';
	wapper w1;
	w1.i = 1;
	w1.name = p;
	bad_que.push_back(w1);
	return 0;
}

int main(){
	func();
	printf("should be ditry data: %s\n", bad_que[0].name);
	return 0;
}
