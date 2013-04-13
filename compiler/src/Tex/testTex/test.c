#include<stdio.h>
int arr[4][2] ={
	{1, 2},
	{2, 4},
	{3, 8},
	{4, 16}
};
int main(){
	printf("should be 2: %d\nshould be 3: %d\n",arr[0][1], arr[2][0]);
	return 0;
}
