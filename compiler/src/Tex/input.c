#include <stdio.h>
//#define MAX_ROW 64 
//#define MAX_COLUMN 1024
#define ROW 50
#define COLUMN 310
//read 2 line first
int main(){
	FILE* file;
	file = fopen("./tab_first.txt", "r");
	if(!file){
		perror("error open file\n");
	}
	else{
		int tab[COLUMN][ROW];
		int loop_i = 0, loop_j = 0, num  = 0;
		while(fscanf(file, "%d", &num) != EOF){
			
			tab[loop_j][loop_i] = num;
			//read character by line
			++loop_i;
			if(! (loop_i % ROW)){
				loop_i = 0;
				++loop_j;
			}
		}
		int loop_col, loop_row;
		for(loop_col = 0; loop_col < loop_j; ++loop_col){
			for(loop_row = 0; loop_row < ROW; ++loop_row)
			printf("%d\t", tab[loop_col][loop_row]);
			printf("\n");
		}
	}

	fclose(file);
}
