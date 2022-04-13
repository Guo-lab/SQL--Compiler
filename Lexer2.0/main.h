#ifndef MAIN_H
#define MAIN_H

#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum TokenType { KW=100, IDN, INT, FLOAT, STRING, OP, SE, OTHER };
enum class State { BEGIN=200, IN_KW, IN_IDN, IN_INT, IN_FLOAT, IN_OP, IN_SE, IN_STR, END };
State state;

static map<TokenType, string> TokenDict= {
    {TokenType::KW,"KW"},
    {TokenType::IDN,"IDN"},
    {TokenType::INT,"INT"},
    {TokenType::FLOAT,"FLOAT"},
    {TokenType::STRING,"STRING"},
    {TokenType::OP,"OP"},
    {TokenType::SE,"SE"},
    {TokenType::OTHER,"OTHER"}
};


class TokenNode {
    public:
        string str;
        TokenType type; 
        string value;
        
        TokenNode(){
            type = TokenType::OTHER;
        }

        void clear(){
            str = "";
            type = TokenType::OTHER;
            value = "";
        }
        
};
vector<TokenNode> tokenlists;

void skip_blank();

bool get_token();
int Find_token(string str);

void deal_Begin(string &str, TokenType &type);
void deal_KW(string &str, TokenType &type);
void deal_IDN(string &str, TokenType &type);
void deal_INT(string &str, TokenType &type);
void deal_FLOAT(string &str, TokenType &type);
void deal_OP(string &str, TokenType &type);
void deal_SE(string &str, TokenType &type);
void deal_STR(string &str, TokenType &type);
TokenNode deal_End(string &str, const TokenType &type);

#endif