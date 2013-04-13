#include "Lex.h"
void hnd_spc(void){
	//ch = fgetc(fd);//handle spc the first time
	printf("white sp\n");
	while(isspace(ch = fgetc(fd)));
	//if hnd_ch is not a spc, then return, in which
	//it still retain a un spc char
	
}
void hnd_sem(void){
	printf("; dected\n");
	ch = fgetc(fd);//handle next
}
void hnd_lbr_f(void){
	printf("( dected\n");
	ch = fgetc(fd);//handle next
}
void hnd_rbr_f(void){
	printf(") dected\n");
	ch = fgetc(fd);//handle next
}
void hnd_lblk(void){
	printf("{ dected\n");
	ch = fgetc(fd);//handle next 
}
void hnd_rblk(void){
	printf("} dected\n");
	ch = fgetc(fd);//handle next
}
void hnd_let(void){
	printf("letter dected\n");
	char id_ch[ID_SIZ] = {'\0'};
	id_ch[0] = ch;//copy the first letter in the id
	int loop;
	for(loop = 1; loop < ID_SIZ ; ++loop){//length of word should less than ID_SIZ	
		ch = fgetc(fd);
		if(isalpha(ch) || isdigit(ch) || isudline(ch)){
			id_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	//deal with word that's too long
	//ATTENTION!!! BUG'S HERE

	int hnd_id;	
	//distinguish keyword ro not
	if((hnd_id = iskeyword(id_ch))){
		//install keyword and id
		printf("%s, %d\n", key_tab[hnd_id - BASE].key, key_tab[hnd_id - BASE].key_id);
	}
	else
		printf("%s,%d\n", id_ch, ID_WRD);
	
}
void hnd_dig(void){
	char dig_ch[ID_SIZ] = {'\0'};
	dig_ch[0] = ch;
	int loop;
	//can be simplied by func poiner, cuz it is like hnd_let
	for(loop = 1; loop < ID_SIZ; ++loop){
		ch = fgetc(fd);
		if(isdigit(ch)){
			dig_ch[loop] = ch;
			continue;
		}
		else
			break;
	}
	printf("%s\n", dig_ch);
}
void hnd_lbr_a(void){
	printf("[ dected\n");
	ch = fgetc(fd);
}
void hnd_rbr_a(void){
	printf("] dected\n");
	ch = fgetc(fd);
}
void hnd_assin(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '=';
	ch = fgetc(fd);
	if(isassin(ch)){
		hnd_ch[1] = '=';//seem no useful now
		ch = fgetc(fd);
		printf("== dected\n");
	}
	else{
		printf("= dected\n");
	}
}
void hnd_add(void){
	printf("+ dected\n");
	ch = fgetc(fd);
}
void hnd_min(void){
	printf("- dected\n");
	ch = fgetc(fd);
}
void hnd_mut(void){
	printf("* dected\n");
	ch = fgetc(fd);
}
void hnd_div(void){
	char hnd_ch[3] = {'\0'};
	hnd_ch[0] = '/';
	ch = fgetc(fd);
	if(isdiv(ch)){
		hnd_ch[1] = '/';//seem no useful now
		ch = fgetc(fd);
		printf("// dected\n");
		while(!isnline(ch=fgetc(fd)));//if ch is not a newline , loop
		ch = fgetc(fd);//deal with the new line
	}
	else{
		printf("/ dected\n");
	}
}
void hnd_quo(void){
	printf("\" dected\n");
	ch = fgetc(fd);
}
void hnd_adr(void){
	printf("& dected \n");
	ch = fgetc(fd);
}

int main(int argc, char **argv){
	//read file 
	//open file
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
		printf("find eof\n");
	}
	fclose(fd);
	//parse
	//write file
}
