#include "Sem.h"
#include "Lex.h"
#include "Tex.h"
int main(){
{	//read file 
		//open file
		initDb();//for connecting db server
		cleanDb();//clean all data
		fd = fopen("./test.me", "r");//need to modify
		if (!fd)
			perror("error opening file");//return //
		else{//not null
			ch = fgetc(fd);
			int loop;
			while(ch != EOF){//not to the end of file
				for(loop = 0; loop < SIZ; ++loop){//which init value should loop assgined
					if((*func_tab[loop].f)(ch)){
						(*func_tab[loop].hnd)();
						break;
					}
				}
			}

		}
		//bad code style
		vec_sym.push_back({20,NULL});
		fclose(fd);
	}

	decSem(&vec_int, "4");
	return 0;
}
