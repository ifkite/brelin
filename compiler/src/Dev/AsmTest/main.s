   1              		.file	"main.c"
   2              		.text
   3              	.Ltext0:
   4              		.globl	main
   6              	main:
   7              	.LFB0:
   8              		.file 1 "main.c"
   1:main.c        **** #include<stdio.h>
   2:main.c        **** 
   3:main.c        **** int main(){
   9              		.loc 1 3 0
  10              		.cfi_startproc
  11 0000 55       		pushl	%ebp
  12              	.LCFI0:
  13              		.cfi_def_cfa_offset 8
  14              		.cfi_offset 5, -8
  15 0001 89E5     		movl	%esp, %ebp
  16              	.LCFI1:
  17              		.cfi_def_cfa_register 5
  18 0003 83EC10   		subl	$16, %esp
   4:main.c        **** 	int a = 1;
  19              		.loc 1 4 0
  20 0006 C745FC01 		movl	$1, -4(%ebp)
  20      000000
   5:main.c        **** 	if(a==1){
  21              		.loc 1 5 0
  22 000d 837DFC01 		cmpl	$1, -4(%ebp)
  23 0011 7507     		jne	.L2
   6:main.c        **** 		a = 2;
  24              		.loc 1 6 0
  25 0013 C745FC02 		movl	$2, -4(%ebp)
  25      000000
  26              	.L2:
   7:main.c        **** 	}
   8:main.c        **** 	return 0;
  27              		.loc 1 8 0
  28 001a B8000000 		movl	$0, %eax
  28      00
   9:main.c        **** }
  29              		.loc 1 9 0
  30 001f C9       		leave
  31              		.cfi_restore 5
  32              	.LCFI2:
  33              		.cfi_def_cfa 4, 4
  34 0020 C3       		ret
  35              		.cfi_endproc
  36              	.LFE0:
  38              	.Letext0:
