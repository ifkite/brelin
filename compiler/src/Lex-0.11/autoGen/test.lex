%{
#include<stdio.h>
%}
number ([0-9])+
type [ \t\n]+int[ \t]*
%%
{number} {printf("number detected\n");}
{type} {printf("type dected\n");}
%%
