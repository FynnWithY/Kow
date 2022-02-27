#include<stdio.h>

extern int bar(int param);
extern int _main();

void _printf(char string){
	printf((char*)string);
}
//int main(){
//	_main();
//	return printf("hello world from C: %i",bar(6));
//}