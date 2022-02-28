#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <errno.h>
#include "FileLoader.hpp"
using namespace std;

#define log_error(msg)         \
    printf("\n[ERROR]\n");     \
    printf((const char *)msg); \
    printf("\n");
#define ASSERT(expression, msg) \
    if (!expression)            \
    {                           \
        log_error(msg);         \
        assert(expression);     \
    }

typedef unsigned long long int u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

template <class T, class B>
struct generic_touple
{
    T x;
    B y;
    generic_touple(T x, B y)
    {
        this->x = x;
        this->y = y;
    }
    T &operator[](int i)
    {
        // ASSERT((i<1),"index higher then 0");
        // ASSERT((i>=0),"index lower then 0");
        // return (!i) ? x:y;
        return x;
    }
};

typedef generic_touple<u32, u32> touple;
typedef generic_touple<string, int> strITouple;

#define OP_NONE             -1
#define OP_PUSH             0x00
#define OP_PLUS             0x01
#define OP_MINUS            0x02
#define OP_PRINT            0x03
#define OP_MULTIPLY         0x04
#define OP_DIVIDE           0x05
#define OP_POP              0x06
#define OP_PUSH_POINTER     0x07
#define OP_EQUALS           0x08
#define OP_IF               0x09
#define OP_END              0x0A
#define OP_ELSE             0x0B
#define OP_WHILE            0x0C
#define OP_DO               0x0D
#define OP_SMALLER          0x0E
#define OP_DUPLICATE        0x0F
#define OP_INVERT           0x10
#define OP_MEMORY           0x11
#define OP_LOAD             0x12
#define OP_STORE            0x13
#define OP_SYSCALL3         0x14

#define MEM_CAPACITY        640000

int numCompilerArgs = 0;
char **compilerArgs;

typedef float triple[3];
struct Operation{
    Operation(u32 type,u32 value=0,u32 jmp=0,triple loc=triple{0,0,0}){
        this->type=type;
        this->value=value;
        this->jmp=jmp;
        this->loc[0]=loc[0];
        this->loc[1]=loc[1];
        this->loc[2]=loc[2];
    }
    u32 type;
    u32 value;
    u32 jmp;
    triple loc;
};
typedef Operation Op;

Operation op_push(u32 x)
{
    return {OP_PUSH, x};
}
Operation op_plus()
{
    return {OP_PLUS, 0};
}
Operation op_minus()
{
    return {OP_MINUS, 0};
}
Operation op_print()
{
    return {OP_PRINT, 0};
}
Operation op_none()
{
    return {0, 0};
}
Operation op_multiply()
{
    return {OP_MULTIPLY, 0};
}
Operation op_divide()
{
    return {OP_DIVIDE, 0};
}
Operation op_pop()
{
    return {OP_POP, 0};
}
Operation op_push_pointer(u32 p)
{
    return {OP_PUSH_POINTER, p};
}
Operation op_push_variable(string name, void *val)
{
}
Operation op_equals()
{
    return {OP_EQUALS, 0};
}
Operation op_if()
{
    return {OP_IF, 0};
}
Operation op_end()
{
    return {OP_END, 0};
}
Operation op_else(){
    return {OP_ELSE,0};
}
Operation op_while(){
    return {OP_WHILE,0};
}
Operation op_do(){
    return {OP_DO,0};
}
Operation op_smaller(){
    return {OP_SMALLER,0};
}
Operation op_duplicate(){
    return {OP_DUPLICATE,0};
}
Operation op_invert(){
    return {OP_INVERT,0};
}
Operation op_memory(){
    return {OP_MEMORY,0};
}
Operation op_load(){
    return {OP_LOAD,0};
}
Operation op_store(){
    return {OP_STORE,0};
}
Operation op_syscall3(){
    return {OP_SYSCALL3,0};
}

const char *CompilerMode = "sim";
typedef vector<Op> Programm;
// define functions
inline bool isInteger(const std::string &s);
Operation lex_col(string op, const char *filePath, int line, int col);
void simulate_programm(Programm operations);
vector<string> split_string(string text, string c);
void clean_string(string &str, string c);
vector<strITouple> strip_line(string &line);
void lex_file(const char *path, const char *m = "sim");
string trim_string_left(string str);
string make_string_from_parts(const char *data);
string get_string_until(string str, const char end);
void remove_from_end(string &str, const char amount);
string compile_programm(vector<Operation> operation);
vector<Operation> lex_line(string line, int lineIndex, const char *filePath);
Programm crossreference_blocks(Programm programm);

// TBD
void remove_from_end(string &str, const char amount)
{
    const char *endToken = str.c_str() + str.size();
    str = endToken - (str.size() - amount);
}
string get_string_until(string str, const char end)
{
    int i = 0;
    string token;
    while (i < str.size() && str[i] != end)
    {
        token += str[i++];
    }

    // token=str.c_str();
    str.erase(token.size(), str.size());
    return str;
}

string trim_string_left(string str)
{
    if (str[0] != ' ')
    {
        return str;
    }
    size_t i = 0;
    while (i < str.size() && str[i] == ' ')
    {
        i++;
    }
    return str.c_str() + i;
}

inline bool isInteger(const std::string &s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

vector<string> split_string(string text, string c)
{
    vector<string> vec;
    string word = "";
    int lastSpace = 0;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == *c.c_str())
        {
            vec.push_back(word);
            word = "";
            lastSpace = i;
        }
        else
            word += text[i];
    }
    if (text[text.size() - 1] != *c.c_str())
    {
        word = "";
        for (int i = lastSpace + 1; i < text.size(); i++)
        {
            word += text[i];
        }
        vec.push_back(word);
    }
    return vec;
}
void clean_string(string &str, const char c)
{
    string word;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == c)
        {
            word += " ";
        }
        else
            word += str[i];
    }

    str.clear();
    str = word;
    // memcpy((void*)str.c_str(),(void*)word.c_str(),word.size()*sizeof(char));
    // str.erase(word.size(),str.size());
}

const string ignore_tokens = "\n\r";
vector<strITouple> strip_line(string &line)
{

    for (int i = 0; i < ignore_tokens.size(); i++)
    {
        const char token = ignore_tokens[i];
        clean_string(line, token);
    }

    const char *start = line.c_str();
    const char *token = line.c_str();

    vector<strITouple> operations;
    line = trim_string_left(line);
    while (line.size() > 0)
    {
        string Token = get_string_until(line, ' ');
        line = line.c_str() + Token.size();
        line = trim_string_left(line);
        // token=token+Token.size();
        int col = token - start; //(currentCol)-start;
        operations.push_back({Token, col});
    }
    if (token == line.c_str())
    {
        int e = 0;
    }
    return operations;
}
Programm crossreference_blocks(Programm programm)
{
    vector<int> stack;
    for (int ip = 0; ip < programm.size(); ip++)
    {
        Operation op = programm[ip];
        if (op.type == OP_IF)
        {
            stack.push_back(ip);
        }else if(op.type == OP_ELSE){
            int if_ip=stack.back();
            stack.pop_back();
            ASSERT(programm[if_ip].type==OP_IF,"'else' can only be used with 'if'");
            programm[if_ip]={OP_IF,(u32)ip+1};
            stack.push_back(ip);
        }else if(op.type==OP_WHILE){
            stack.push_back(ip);
        }else if(op.type==OP_DO){
            stack.push_back(ip);
        }
        else if (op.type == OP_END)
        {
            int block_ip = stack.back();
            stack.pop_back();
            if(programm[block_ip].type==OP_IF || programm[block_ip].type==OP_ELSE){
                programm[block_ip] = {programm[block_ip].type,0, (u32)ip+1};
                programm[ip]={OP_END,0,(u32) ip+1};
            }else if(programm[block_ip].type==OP_DO){
                int while_ip=stack.back();
                stack.pop_back();
                ASSERT(programm[while_ip].type==OP_WHILE,"'do can only be used with 'while'");
                programm[ip]={OP_END,0,(u32)while_ip};
                programm[block_ip]={OP_DO,0,(u32)ip+1};
            }
            else{
                ASSERT(programm[block_ip].type==OP_IF || programm[block_ip].type==OP_ELSE,"'end' caon only be used with 'if' or 'while'");
            }
            
        }
    }
    return programm;
};
void lex_file(const char *path, const char *m)
{
    vector<int> stack;
    string file = load_programm_from_file(path);
    CompilerMode = m;
    if (CompilerMode == "sim")
    {
        vector<string> splitFile = split_string(file, "\n");
        vector<Operation> operations = lex_line(file, 0, path);
        simulate_programm(operations);
        // for(int line=0;line<splitFile.size();line++){
        //     lex_line(splitFile[line],stack,line,path);
        // }
    }
    else if (CompilerMode == "com")
    {
        vector<Operation> operations=lex_line(file, 0, path);
        string assembly_file = compile_programm(operations);
        string output_path = path;
        output_path += ".asm";
        write_to_file(output_path.c_str(), assembly_file);
        string command = "nasm -f elf64 ";
        command += output_path;
        system(command.c_str());
        command.clear();
        command = "gcc ";
        string temp = path;
        temp += ".o";
        command+="external.c ";
        command += temp;
        command += " -o";
        command += path;
        command += ".exe";
        system(command.c_str());
        output_path.clear();
        output_path=path;
       //output_path+="C:\\Users\\49175\\Documents\\C\\testCNotC++\\MyLanguage\\bin\\test.kow.exe";
       //system(output_path.c_str());
    }
    else
    {
        log_error("unkown compiler option\n");
        printf(CompilerMode);
    }
}

vector<Operation> lex_line(string line, int lineIndex, const char *filePath)
{
    const char *prevLine = line.c_str();
    vector<strITouple> operations = strip_line(line);
    vector<int> stack;
    Programm programm;
    for (int i = 0; i < operations.size(); i++)
    {
        programm.push_back(lex_col(operations[i][0], filePath, lineIndex, (int)operations[i].y));
    }
    programm=crossreference_blocks(programm);
    // for(int i=0;i<operations.size();i++){
    //     simulate_programm(stack,programm[i]);
    // }
    return programm;
}
Operation lex_col(string op, const char *filePath, int line, int col)
{
    int x = 0;
    if (op == "+")
    {
        return op_plus();
    }
    else if (op == "-")
    {
        return op_minus();
    }
    else if (op == "print")
    {
        return op_print();
    }
    else if (op == "*")
    {
        return op_multiply();
    }
    else if (op == "/")
    {
        return op_divide();
    }
    else if (op == "pop")
    {
        return op_pop();
    }
    else if (op == "==")
    {
        return op_equals();
    }
    else if (op == "if")
    {
        return op_if();
    }
    else if (op == "end")
    {
        return op_end();
    }else if(op=="else"){
        return op_else();
    }else if(op=="while"){
        return op_while();
    }else if(op=="do"){
        return op_do();
    }else if(op=="<"){
        return op_smaller();
    }else if(op=="dup"){
        return op_duplicate();
    }else if(op=="!"){
        return op_invert();
    }else if(op=="mem"){
        return op_memory();
    }else if(op=="."){
        return op_store();
    }
    else if(op==","){
        return op_load();
    }else if(op=="syscall3"){
        return op_syscall3();
    }
    else if (isInteger(op))
    {
        return op_push(stoi(op));
    }
    else if (op[0] == '*')
    {
        string num = op.c_str() + 1;
        if (isInteger(num))
        {
            int p = stoi(num);
            return op_push_pointer(p);
        }
    }
    printf("unkown symbol in %s:%i:%i ", filePath, line, col,op);
    ASSERT((0 == 1), "");
    return op_none();
}

string compile_programm(vector<Operation> operations)
{
    string assembly_file_output_start = "BITS 64\nglobal WinMain";
    string assembly_file_output_functions = "\nextern printf\nextern exit\nextern print";
    string assembly_file_output_section_data = "\nsection .data\nTEXT_INT db \"%i \",10,0";
    string assembly_file_output_sections = "\nsection .bss\nmem: resb ";
    assembly_file_output_sections+=to_string(MEM_CAPACITY);
    assembly_file_output_sections+="\nsection .text";
    string assembly_file_output_content = "\nWinMain:";
    for (int i = 0; i < operations.size(); i++)
    {
        string temp;
        Operation op=operations[i];
        assembly_file_output_content +="\naddr_";
        assembly_file_output_content += to_string((int)i);
        assembly_file_output_content +=":\n";
        switch ((int)operations[i].type)
        {
        case OP_PUSH:
            assembly_file_output_content += "\n;--PUSH--";
            assembly_file_output_content += "\npush ";
            temp = to_string((int)op.value);
            assembly_file_output_content += temp;
            assembly_file_output_content += "\n";
            break;
        case OP_PRINT:
            assembly_file_output_content += "\n;--PRINT--";
            //assembly_file_output_content += "\nmov ebp, esp";
           // assembly_file_output_content += "\nmov rcx, TEXT_INT";
            assembly_file_output_content += "\npop rdx";
            assembly_file_output_content += "\ncall print";
            //assembly_file_output_content += "\nadd esp, 8";
            //assembly_file_output_content += "\npop rdx";
            //assembly_file_output_content+=  "\nmov esp, ebp";
            break;
        case OP_PLUS:
            assembly_file_output_content += "\n;--PLUS--";
            assembly_file_output_content += "\npop rcx";
            assembly_file_output_content += "\npop rdx";
            assembly_file_output_content += "\nadd rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
        case OP_MINUS:
            assembly_file_output_content += "\n;--MINUS--";
            assembly_file_output_content += "\npop rdx";
            assembly_file_output_content += "\npop rcx";
            assembly_file_output_content += "\nsub rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
            // TBD
        case OP_MULTIPLY:
            assembly_file_output_content += "\n;--MULTIPLY--";
            assembly_file_output_content += "\npop rdx";
            assembly_file_output_content += "\npop rcx";
            assembly_file_output_content += "\nmul rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
            // TBD
        case OP_DIVIDE:
            assembly_file_output_content += "\n;--DIVIDE--";
            assembly_file_output_content += "\npop rdx";
            assembly_file_output_content += "\npop rcx";
            assembly_file_output_content += "\ndiv rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
        case OP_POP:
            assembly_file_output_content += "\n;--POP--";
            assembly_file_output_content += "\npop rdx";
            break;
        case OP_EQUALS:
            assembly_file_output_content += "\n;--EQUALS--";
            assembly_file_output_content += "\nmov rcx, 0";
            assembly_file_output_content += "\nmov rdx, 1";
            assembly_file_output_content += "\npop rax";
            assembly_file_output_content += "\npop rbx";
            assembly_file_output_content += "\ncmp rax, rbx";
            assembly_file_output_content += "\ncmove rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
        case OP_SMALLER:
            assembly_file_output_content += "\n;--SMALLER--";
            assembly_file_output_content += "\nmov rcx, 0";
            assembly_file_output_content += "\nmov rdx, 1";
            assembly_file_output_content += "\npop rax";
            assembly_file_output_content += "\npop rbx";
            assembly_file_output_content += "\ncmp rax, rbx";
            assembly_file_output_content += "\ncmovg rcx, rdx";
            assembly_file_output_content += "\npush rcx";
            break;
        case OP_INVERT:
            assembly_file_output_content += "\n;--INVERT--\n";
            assembly_file_output_content += "pop rcx\n";
            assembly_file_output_content += "xor rcx, 0x01\n";
            assembly_file_output_content += "push rcx\n";
            break;
        case OP_IF:
            assembly_file_output_content += "\n;--IF--\n";
            assembly_file_output_content += "pop rax\n";
            assembly_file_output_content += "test rax,rax\n";
            assembly_file_output_content += "jz addr_";
            assembly_file_output_content += to_string((int)op.jmp);
            assembly_file_output_content += "\n";
            break;
        case OP_ELSE:
            assembly_file_output_content +="\n;--ELSE--\n";
            assembly_file_output_content +="jmp addr_";
            assembly_file_output_content += to_string((int)op.jmp);
            assembly_file_output_content += "\n";
            //assembly_file_output_content +="addr_";
            //assembly_file_output_content += to_string((int)i+1);
            //assembly_file_output_content +=":\n";
            break;
        case OP_WHILE:
            assembly_file_output_content +="\n;--WHILE--\n";
            //assembly_file_output_content +="jmp addr_";
            //assembly_file_output_content +=to_string((int)i);
           //assembly_file_output_content +="\naddr_";
           //assembly_file_output_content += to_string((int)i);
           //assembly_file_output_content +=":\n";
            break;
        case OP_DO:
            assembly_file_output_content +="\n;--DO--\n";
            assembly_file_output_content +="pop rax\n";
            assembly_file_output_content +="test rax, rax\n";
            assembly_file_output_content +="jz addr_";
            assembly_file_output_content += to_string((int)op.jmp);
            assembly_file_output_content += "\n";
            //assembly_file_output_content +="addr_";
            //assembly_file_output_content += to_string((int)i+1);
            //assembly_file_output_content +=":\n";
            break;
        case OP_END:
            assembly_file_output_content +="\n;--END--\n";
            //assembly_file_output_content +="jmp addr_";
            //assembly_file_output_content +=to_string(i);
            //assembly_file_output_content +="addr_";
            //assembly_file_output_content += to_string(i);
            //assembly_file_output_content +=":";
            if(i+1 != op.jmp){
                assembly_file_output_content +="\njmp addr_";
                assembly_file_output_content +=to_string((int)op.jmp);
                assembly_file_output_content +="\n";
            }
            assembly_file_output_content +="addr_";
            assembly_file_output_content += to_string(i+1);
            assembly_file_output_content +=":\n";
            //assembly_file_output_content += "ret";
            //assembly_file_output_content += "call exit\n";
            break;
        case OP_DUPLICATE:
            assembly_file_output_content+="\n;--DUPLICATE--\n";
            assembly_file_output_content+="pop rax\n";
            assembly_file_output_content+="push rax\n";
            assembly_file_output_content+="push rax\n";
            break;
        case OP_MEMORY:
            assembly_file_output_content+="\n;--MEMORY--\n";
            assembly_file_output_content+="push mem\n";
            break;
        case OP_LOAD:
           //-------- xor rcx, rcx
	       //-------- mov rcx, [rdx]
	       //-------- push rcx
            assembly_file_output_content+="\n;--LOAD--\n";
            assembly_file_output_content+="xor rcx, rcx\n";
            assembly_file_output_content+="pop rdx\n";
            assembly_file_output_content+="mov rcx, [rdx]\n";
            assembly_file_output_content+="push rcx\n";
            break;
        case OP_STORE:
            assembly_file_output_content+="\n;--STORE--\n";
            assembly_file_output_content+="pop rcx\n";
            assembly_file_output_content+="pop rdx\n";
            assembly_file_output_content+="mov [rdx], rcx\n";
            break;
        case OP_SYSCALL3:
            assembly_file_output_content+="\n;--SYSCALL3--\n";
            assembly_file_output_content+="pop rax\n";
            assembly_file_output_content+="pop r8\n";
            assembly_file_output_content+="pop rdx\n";
            assembly_file_output_content+="pop rcx\n";
            assembly_file_output_content+="syscall\n";
            break;
        default:
            break;
        }
    
    }
    string assembly_file_output = assembly_file_output_start + assembly_file_output_functions + assembly_file_output_section_data + assembly_file_output_sections + assembly_file_output_content;
    return assembly_file_output;
}
void simulate_programm(Programm operations)
{
    void* memory=malloc(MEM_CAPACITY);
    vector<int> stack;
    int a = 0;
    int b = 0;
    int ip = 0;
    while (ip < operations.size())
    {

        Operation operation = operations[ip];
        switch ((int)operation.type)
        {
        case OP_PUSH:
            stack.push_back(operation.value);
            ip++;
            break;
        case OP_PLUS:
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            stack.push_back(a + b);
            ip++;
            break;
        case OP_MINUS:
            b = stack.back();
            stack.pop_back();
            a = stack.back();
            stack.pop_back();
            stack.push_back(a - b);
            ip++;
            break;
        case OP_PRINT:
            cout << stack.back() << endl;
            //stack.pop_back();
            ip++;
            break;
        case OP_DIVIDE:
            b = stack.back();
            stack.pop_back();
            a = stack.back();
            stack.pop_back();
            stack.push_back(a / b);
            ip++;
            break;
        case OP_MULTIPLY:
            b = stack.back();
            stack.pop_back();
            a = stack.back();
            stack.pop_back();
            stack.push_back(a * b);
            ip++;
            break;
        case OP_POP:
            stack.pop_back();
            ip++;
            break;
        case OP_PUSH_POINTER:
            stack.push_back(stack[operation.value]);
            ip++;
            break;
        case OP_EQUALS:
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            stack.push_back(b == a);
            ip++;
            break;
        case OP_SMALLER:
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            stack.push_back(b < a);
            ip++;
            break;
        case OP_INVERT:
            a = stack.back();
            stack.pop_back();
            stack.push_back(!a);
            ip++;
            break;
        case OP_IF:
            if (stack.back() == 0)
            {
                ip = operation.jmp;
            }
            else
            {
                ip++;
            }
            stack.pop_back();
            break;
        case OP_END:
            ip=operation.jmp;
            break;
        case OP_ELSE:
            ip=operation.jmp;
            break;
        case OP_WHILE:
            ip++;
            break;
        case OP_DO:
            a=stack.back();
            stack.pop_back();
            if(!a){
                ip=operation.jmp;
            }else{
                ip++;
            }
            break;
        case OP_DUPLICATE:
            a=stack.back();
            stack.pop_back();
            stack.push_back(a);
            stack.push_back(a);
            ip++;
            break;
        case OP_MEMORY:
           //stack.push_back((int*)memory);
           //ip++;
            break;
        default:
            ip++;
            break;
        }
    }
}
#endif