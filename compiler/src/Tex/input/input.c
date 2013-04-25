#include<stdio.h>
//read 2 line first
int main(){
	FILE* file;
	file = fopen("./text.txt", "r");
	if(!file){
		perror("error open file\n");
	}
	else{
		int tab[2][4];
		int loop_i = 0, loop_j = 0, num  = 0;
		while(fscanf(file, "%x", &num) != EOF){
			
			tab[loop_j][loop_i] = num;
			//read character by line
			++loop_i;
			if(! (loop_i % 4)){
				loop_i = 0;
				++loop_j;
			}
		}
		for(loop_j = 0 ; loop_j < 2; ++loop_j){
			for(loop_i = 0; loop_i < 4; ++loop_i)
				printf("%x ", tab[loop_j][loop_i]);
			printf("\n");
		}
		tab[0][3]++;
		printf("in dec: %d", tab[0][3]);
		printf("in hex: %x", tab[0][3]);
	}

	fclose(file);
}
