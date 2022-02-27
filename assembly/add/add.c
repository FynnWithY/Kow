#include<stdio.h>
void _printf(void* msg){
	printf((const char*)msg);
}