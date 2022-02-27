#include<iostream>
#include <windows.h>

using namespace std;
#include"Lexer.hpp"

int main(int argc, char** argv){
    numCompilerArgs=argc;
    compilerArgs=argv;
    
    //string programm=load_programm_from_file(compilerArgs[0]);
    lex_file("bin/test.f","com");
    //write_to_file("bin/test.asm",load_programm_from_file("C:/Users/49175/Documents/C/testCNotC++/MyLanguage/assembly/add/add.asm"));
   //printf("nasm -f elf64 bin/test.asm\ngcc test.o add.c");
   //system("nasm -f elf64 bin/test.asm");
   //system("gcc bin/test.o");
    return 0;
}