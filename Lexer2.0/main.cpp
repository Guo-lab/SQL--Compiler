#include "define.h"
#include "main.h"
#include "define.cpp"


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

string code;
string::const_iterator ch;
TokenNode token;

int main() {
    printf("Start to compile.\n");
    
    initMap();
    ////printf("HELLO\n");

    ifstream File("test.txt");
    if(File) {
        code = string((istreambuf_iterator<char>(File)), istreambuf_iterator<char>());
        ch = code.cbegin();
    } else {
        cout<<"Can't find the file.\n";
        return 1;
    }
    ////printf("OKK!\n");
    
    fstream f;
	f.open("data.txt", ios::out);
    ////printf("OKK!)))))))))))\n");
    while(get_token()){
        tokenlists.push_back(token);
        //printf("OKK!\n");
        f<<token.str<<"    <"<<TokenDict[token.type] <<","<<token.value<<">\n";
    }
	f.close();

    
	f.open("../Parser/data.txt",ios::out);
    for(auto token:tokenlists)
       f<<token.str<<"\n"<<TokenDict[token.type]<<"\n";
	f.close();
    return 0;
}



void skip_blank(){
    while(ch != code.cend() && *ch!=EOF) {
        ////if(*ch == ' ') printf("1 %c\n",*ch);
        ////if(*ch == '\n') printf("One line\n");
        if(*ch=='\n') {
            ch++;
        } else if(isblank(*ch))
            ch++;
        else
            break;
    }
}



int Find_token(string str){
    map<string,int>::iterator iter;
    iter = kMap.find(str);
    if(iter != kMap.end())
        return iter->second;

    iter = oMap.find(str);
    if(iter != oMap.end())
        return iter->second;

    iter = sMap.find(str);
    if(iter != sMap.end())
        return iter->second;

    iter = MMap.find(str);
    if(iter != MMap.end())
        return iter->second;

    return 999;
}



bool get_token(){
    token.clear();
    state = State::BEGIN;
    TokenType type = TokenType::OTHER;
    string str;

    skip_blank();
    ////cout<<*ch<<endl;
    while((ch != code.cend() && *ch != EOF) || state == State::END || str != ""){
        switch (state)
        {
        case State::BEGIN:
            deal_Begin(str,type);
            break;

        case State::IN_IDN:
            deal_IDN(str,type);
            break;

        case State::IN_INT:
            deal_INT(str,type);
            break;
        case State::IN_FLOAT:
            deal_FLOAT(str,type);
            break;
        case State::IN_KW:
            deal_KW(str,type);
            break;
            
        case State::IN_SE:
            deal_SE(str,type);
            break;
        
        case State::IN_OP:
            deal_OP(str,type);
            break;
        
        case State::IN_STR:
            deal_STR(str,type);
            break;
        
        case State::END:
            token = deal_End(str,type);
            return true;
        default:
            break;
        }

    }
    return false;
}









void deal_Begin(string &str, TokenType &type){
    if(isdigit(*ch))
        state = State::IN_INT;
    else if(isalpha(*ch) || *ch == '_')
        state = State::IN_IDN;
    else if(*ch == ',' || *ch == '(' || *ch == ')') 
        state = State::IN_SE;
    else if(*ch == '\'')
        state = State::IN_STR;
    else    
        state = State::IN_OP;
}

void deal_IDN(string &str, TokenType &type){
    if(isalnum(*ch)){
        str += *ch;
        ch++;
    }
    else if((Find_token(str) != IDN) && Find_token(str) < 50){
        if(Find_token(str) == GROUP || Find_token(str) == ORDER){
            if(*ch == ' ' && *(ch+1) == 'B' && *(ch+2) == 'Y'){
                    // str += " BY";
                    ch+=3;
                    state = State::IN_KW;
            }
            else{
                type = TokenType::IDN;
                state = State::END;
            }
        }
        else
            state = State::IN_KW;
        
    }
    else if((Find_token(str) != IDN) && Find_token(str) < 70){
        state = State::IN_OP;
    }
    else{
        type = TokenType::IDN;
        if(*ch != '_')
            state = State::END;
        else{
            str+= *ch;
            ch++;
        }
    }
}

void deal_KW(string &str, TokenType &type){
    type = TokenType::KW;
    state = State::END;
}

void deal_SE(string &str, TokenType &type){
    str += *ch;
    ch++;
    type = TokenType::SE;
    state = State::END;
}

void deal_OP(string &str, TokenType &type){
    if(Find_token(str) < 999){
        type = TokenType::OP;
        state = State::END;
    }
    else{
        if(*ch == '=' || *ch == '.'){
            str += *ch;
            ch++;
            type = TokenType::OP;
            state = State::END;
        }
        else if(*ch=='!' || *ch=='&' || *ch=='|' || *ch=='<' || *ch=='>'){
            str += *ch;
            char tmp = *ch;
            ch++;
            if(tmp=='!' && *ch=='=') { str+=*ch; *ch++; }
            else if(tmp=='&' && *ch=='&'){ 
                str+=*ch; *ch++; 
            }
            else if(tmp=='|' && *ch=='|'){ 
                str+=*ch; *ch++; 
            }
            else if(tmp=='>' && *ch=='='){ 
                str+=*ch; *ch++;
            }
            else if(tmp=='<' && *ch=='='){ 
                str+=*ch; 
                ch++; 
                if(*ch=='>'){
                    str+=*ch; *ch++;
                }
            }
            type = TokenType::OP;
            state = State::END;
        }
        else{
            type = TokenType::OTHER; state = State::END;
        }
    }
}

void deal_INT(string &str, TokenType &type){
    if(isdigit(*ch)) {
        str+=*ch;
        ch++;
    } else if(*ch == '.') {
        str+=*ch;
        ch++;
        state = State::IN_FLOAT;
    } else {
        type = TokenType::INT;
        state = State::END;
    }
}

void deal_FLOAT(string &str, TokenType &type){
    if(isdigit(*ch)) {
        str+=*ch;
        ch++;
    } else {
        type = TokenType::FLOAT;
        state = State::END;
    }
}

void deal_STR(string &str, TokenType &type){
    str += *ch;
    ch++;
    while(*ch != '\''){
        if(*ch == '\\'){
            str += *ch;
            ch++;
        }
        str += *ch;
        ch++;
    }
    str += *ch;
    ch++;
    type = TokenType::STRING;
    state = State::END;
}

TokenNode deal_End(string &str, const TokenType &type){
    TokenNode temp;
    int ans = Find_token(str);
    temp.str = str;
    temp.type = type;
    if(type == KW)
        temp.value = to_string(ans);
    else if(type == OP)
        temp.value = to_string(ans-50);
    else if(type == SE)
        temp.value = to_string(ans-80);
    else
        temp.value = str;

    return temp;
}