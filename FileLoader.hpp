#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#include"Lexer.hpp"

string load_programm_from_file(const char* path){
    FILE* file=fopen(path,"rb");
    string content=" ";
    for(char c=getc(file);c!=EOF;c=getc(file)){
        content+=c;
    }
    fclose(file);
    return content;
}
void write_to_file(const char* path,string content,const char* mode="w"){
    FILE* file=fopen(path,mode);
    fwrite(content.c_str(),sizeof(const char),content.size(),file);
    fclose(file);
}

#endif