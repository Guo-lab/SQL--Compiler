#ifndef _LEXER_H_INCLUDED
#define _LEXER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

using namespace std;

//@ KW, OP, SE => NO
//@ IDN, CONS, OTHER => VALUE
//@ IDN - 为字母、数字和下划线组成的不以数字开头的串
enum TokenType { KW=100, IDN, INT, FLOAT, STR, OP, SE, OTHER };
enum class State { BEGIN=200, IN_KW, IN_IDN, IN_INT, IN_FLOAT, IN_OP, IN_SE, IN_STR, END };
State state;

//! g++ -std=c++11 a.cpp
static map<TokenType, string> TokenDict= {
    {TokenType::KW,"KEYWORD"},
    {TokenType::IDN,"IDN"},
    {TokenType::INT,"INT"},
    {TokenType::FLOAT,"FLOAT"},
    {TokenType::STR,"STR"},
    {TokenType::OP,"OPERATOR"},
    {TokenType::SE,"SE"},
    {TokenType::OTHER,"OTHER"}
};




string code;
string::const_iterator iter;
size_t line;



//% STRUCT
/*
struct TokenNode {
    char name[30];
    TokenType type; 
    char value[30];

    size_t index;
    size_t line;
    ////TokenNode *next;
};*/

class TokenNode {
    public:
        char name[30] = {0};
        TokenType type; 
        char value[30];
        size_t index;
        size_t line;
    
        TokenNode(){
            type = TokenType::OTHER;
            line = 0;
        }
        TokenNode(char* name, TokenType type, char* value, size_t line) {
            strcpy(this->name, name);
            strcpy(this->value, value);
            this->line = line;
            this->type = type;
        }
        // ! 表达式必须包含 bool 类型(或可转换为 bool)C/C++(711)
        operator bool() {
            if(type == TokenType::OTHER)
                return false;
            else
                return true;
        }
};



vector<TokenNode> tokens;



//% FUNCTION
void initMap();
void initNode();
void AddNode(const char *name, TokenType type, const char *value, size_t index, size_t line);

int seekKey(string *word);


void scanner();
    void dealBegin(const char &name, TokenType &type);
    void dealKw(const char &name, TokenType &type);
    void dealIDN(const char &name, TokenType &type);
    void dealInt(const char &name, TokenType &type);
    void dealFloat(const char &name, TokenType &type);
    void dealOp(const char &name, TokenType &type);
    void dealSe(const char &name, TokenType &type);
    void dealStr(const char &name, TokenType &type);
    TokenNode dealEnd(const char &name, const TokenType &type);
    
    void skipBlank();

void printTokenLink();


#endif