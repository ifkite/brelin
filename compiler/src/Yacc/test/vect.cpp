#include<stdio.h>
#include<vector>
using std::vector;
vector<char> *genStr(char ch){
	vector<char> *vec_ch = new vector<char>;
	int i;
	for(i = 0; i < 5; ++i)
		vec_ch->push_back(ch + i);
	return vec_ch;
}

int main(){
	vector<char> *str = genStr('a');
	//vector<char>::iterator itr;
	int i;
	for(i = 0; i < str->size(); ++i){
		printf("%c\n", (*str)[i]);
	}
	delete str;
	return 0;
}
