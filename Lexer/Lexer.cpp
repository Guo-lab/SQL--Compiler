/*
* @Author: gsq,
* @Date: 2022-4-1,
* @操作目的:(1)生成符号表；
*          (2)将待分析 代码转化为语法分析器可接受的序列。
*/


#include "Lexer.h"
#include "kw.h"
#include "se.h"
#include "op.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;





TokenNode TokenHead;  //定义识别TOKEN表的首结点
TokenNode token;

vector<pair<const char *, int> > kMap;    //定义关键字表
vector<pair<const char *, int> > oMap;    //定义运算符号表
vector<pair<const char *, int> > sMap;    //定义限界符号表
vector<pair<const char *, int> > MMap;    //显示自己的值的符号表 


/*
 *initMap
 * Author: gsq,
 * Date: 2022-4-1,
 */
void initMap() {
    kMap.clear();
    kMap.push_back(make_pair("SELECT", SELECT));
    kMap.push_back(make_pair("FROM", FROM));
    kMap.push_back(make_pair("WHERE", WHERE));
    kMap.push_back(make_pair("AS", AS));
    kMap.push_back(make_pair("INSERT", INSERT));
    kMap.push_back(make_pair("INTO", INTO));
    kMap.push_back(make_pair("VALUES", VALUES));
    kMap.push_back(make_pair("UPDATE", UPDATE));
    kMap.push_back(make_pair("DELETE", DELETE));
    kMap.push_back(make_pair("JOIN", JOIN));
    kMap.push_back(make_pair("LEFT", LEFT));
    kMap.push_back(make_pair("RIGHT", RIGHT));
    kMap.push_back(make_pair("MIN", MIN));
    kMap.push_back(make_pair("MAX", MAX));
    kMap.push_back(make_pair("AVG", AVG));
    kMap.push_back(make_pair("SUM", SUM));
    kMap.push_back(make_pair("UNION", UNION));
    kMap.push_back(make_pair("ALL", ALL));
    kMap.push_back(make_pair("GROUP_BY", GROUP_BY));
    kMap.push_back(make_pair("HAVING", HAVING));
    kMap.push_back(make_pair("DISTINCT", DISTINCT));
    kMap.push_back(make_pair("ORDER_BY", ORDER_BY));
    kMap.push_back(make_pair("TRUE", TRUE));
    kMap.push_back(make_pair("FALSE", FALSE));
    kMap.push_back(make_pair("IS", IS));
    kMap.push_back(make_pair("NOT", NOT));
    kMap.push_back(make_pair("NULL", NULL_));


    oMap.clear();
    oMap.push_back(make_pair("=", EQUAL));
    oMap.push_back(make_pair(">", GRT_THAN));
    oMap.push_back(make_pair("<", LES_THAN));
    oMap.push_back(make_pair(">=", GRT_EQUAL));
    oMap.push_back(make_pair("<=", LES_EQUAL));
    oMap.push_back(make_pair("!=", NOT_EQUAL));
    oMap.push_back(make_pair("<=>", NOT_EQUAL_));
    oMap.push_back(make_pair("&&", AND));
    oMap.push_back(make_pair("AND", AND_));
    oMap.push_back(make_pair("||", OR));
    oMap.push_back(make_pair("OR", OR_));
    oMap.push_back(make_pair("XOR", XOR));
    oMap.push_back(make_pair(".", POINT));

    sMap.clear();
    sMap.push_back(make_pair("(", LEFT_BRA));
    sMap.push_back(make_pair(")", RIGHT_BRA));
    sMap.push_back(make_pair(",", COMMA));

    MMap.clear();
    MMap.push_back(make_pair("STR", STR));
    MMap.push_back(make_pair("FLOAT", FLOAT));
    MMap.push_back(make_pair("INT", INT));
    MMap.push_back(make_pair("IDN", IDN));
    MMap.push_back(make_pair("OTHER", OTHER));

}



/*
 *initNode
 * Author: gsq,
 * Date: 2022-4-1,
 */
/*
void initNode() {
    TokenHead = new TokenNode();
    strcpy(TokenHead->name, "");
    TokenHead->type= TokenType::OTHER;
    strcpy(TokenHead->value, "");
    TokenHead->index= -1;
    TokenHead->line= -1;
    ////TokenHead->next = NULL;
}*/


/*
 *AddNode
 * Author: gsq,
 * Date: 2022-4-1,
 */
void AddNode(const char *name, TokenType type, const char *value, size_t index, size_t line) {

}




/*
 *seedKey
 * Author: gsq,
 * Date: 2022-4-1,
 */
int seekKey(string &wor) {
    //cout << typeid(wor).name() << endl;
    const char * word = wor.c_str();
    for (int i = 0; i < int(kMap.size()); i++) {
        if (strcmp(word, kMap[i].first) == 0) {
            ////cout <<kMap[i].second<<endl; 
            return kMap[i].second;
        }
    }
    for (int i = 0; i < int(oMap.size()); i++) {
        if (strcmp(word, oMap[i].first) == 0) {
            ////cout <<oMap[i].second<<endl; 
            return oMap[i].second;
        }
    }
    for (int i = 0; i < int(sMap.size()); i++) {
        if (strcmp(word, sMap[i].first) == 0) {
            ////cout <<sMap[i].second<<endl; 
            return sMap[i].second;
        }
    }
    for (int i = 0; i < int(MMap.size()); i++) {
        if (strcmp(word, MMap[i].first) == 0) {
            ////cout <<MMap[i].second<<endl; 
            return MMap[i].second;
        }
    }
    return OTHER;
}







/*
 *skipBlank
 * Author: gsq,
 * Date: 2022-4-1,
 */
void skipBlank() {
    while(iter!=code.cend() && *iter!=EOF) {
        if(*iter=='\n') {
            iter++;
            line++;
        } else if(isblank(*iter))
            iter++;
        else
            break;
    }
}
void dealBegin(string &name, TokenType &type){
    if(isdigit(*iter)) state = State::IN_INT; //!
    else if(isalpha(*iter) || *iter=='_') { 
        ////cout<<"INTO IDN"<<endl; 
        state = State::IN_IDN;
    }
    else if(*iter==',' || *iter=='(' || *iter==')') state = State::IN_SE;
    else if(*iter=='\'' || *iter=='\"') {
        state = State::IN_STR;
        name+=*iter;
        iter++;
    }
    else state = State::IN_OP;
}
void dealInt(string &name, TokenType &type){
    if(isdigit(*iter)) {
        name+=*iter;
        iter++;
    } else if(*iter == '.') {
        name+=*iter;
        iter++;
        state = State::IN_FLOAT;
    } else {
        type = TokenType::INT;
        state = State::END;
    }
}
void dealFloat(string &name, TokenType &type) {
    if(isdigit(*iter)) {
        name+=*iter;
        iter++;
    } else {
        type = TokenType::FLOAT;
        state = State::END;
    }
}

void dealIDN(string &name, TokenType &type){
    if(isalnum(*iter)) {
        name+=*iter;
        ////cout << typeid(name).name() << endl;
        ////cout << name << endl;
        ////cout << seekKey(name) << endl;
        iter++;
        ////cout << *iter << endl; //cout << typeid(*iter).name() << endl;
    } else if((seekKey(name) != OTHER) && seekKey(name)<30) {
        state = State::IN_KW;
        ////cout << "INTO KW1" << endl;
    }else if((seekKey(name) >50) && seekKey(name)<70) {
        state = State::IN_OP;
        iter--;
        ////cout << "INTO OP-AND1" << endl;
    } else {
        type = TokenType::IDN;
        state = State::END;
    }
}
void dealKw(string &name, TokenType &type){
    type = TokenType::KW;
    state = State::END;
}

void dealSe(string &name, TokenType &type){
    name+=*iter;
    iter++;
    type = TokenType::SE;
    state = State::END;
}

void dealOp(string &name, TokenType &type){
    if(*iter=='=') {
        name+=*iter;
        iter++;
        type = TokenType::OP;
        state = State::END;
    } else if(*iter=='.') {
        name+=*iter;
        iter++;
        type = TokenType::OP;
        state = State::END;
    } else if(*iter=='!' || *iter=='&' || *iter=='|' || *iter=='<' || *iter=='>') {
        name+=*iter;
        const char lastOp = *iter;
        iter++;
        if(iter!=code.cend()) {
            if(lastOp=='!' && *iter=='=') { name+=*iter; *iter++; }
            else if(lastOp=='&' && *iter=='&') { name+=*iter; *iter++; }
            else if(lastOp=='|' && *iter=='|') { name+=*iter; *iter++; }
            else if(lastOp=='<' && *iter=='=') { 
                name+=*iter; 
                iter++; 
                if(iter!=code.cend() && *iter=='>') {
                    name+=*iter; *iter++;
                }}
            else if(lastOp=='>' && *iter=='=') { name+=*iter; *iter++; }
            type = TokenType::OP;
            state = State::END;
        }
    } else if(*iter =='D') {
        iter++;
        ////cout << *iter << endl;
        type = TokenType::OP;
        state = State::END;
    } else if(*iter =='R') {
        iter++;
        type = TokenType::OP;
        state = State::END;
    }
    else { type = TokenType::OTHER; state = State::END; }
}


void dealStr(string &name, TokenType &type){
    //TODO
    if((*iter=='\'')||(*iter=='\"')){
        type = TokenType::STR;
        state = State::END;
    }
    name+=*iter;
    iter++;
}

TokenNode dealEnd(string &name, const TokenType &type){
    TokenNode EndToken;
    //!EndToken = new TokenNode();
    ////cout << name << "***"<< type << "***" << line << endl;
    
    char *value;
    if(type==KW) sprintf(value, "%d", seekKey(name));
    ////cout << value << endl;
    
    char *name_;
    sprintf(name_, "%s", name.c_str());
    EndToken = TokenNode(name_, type, value, line);
    ////cout << "return EndToken" <<endl;
    return EndToken;
}













/*
 *getNextToken
 * Author: gsq,
 * Date: 2022-4-1,
 */
//% END if(token->name == "#") break;
//%State { BEGIN, IN_KW, IN_IDN, IN_INT, IN_FLOAT, IN_OP, IN_SE, IN_STR, END };
TokenNode getNextToken() {
    state = State::BEGIN;
    TokenType type = TokenType::OTHER;
    string name;
    //cout << name << endl;

    //!token = new TokenNode();

    skipBlank();
    ////cout << "After skipping Blank" << endl;
    
    ////cout << *iter << endl;
    while((iter!=code.cend() && *iter!=EOF) || state==State::END) {
        switch(state) {
        case State::BEGIN:
            dealBegin(name,type);
            ////cout << "Begin" <<endl;
            break;
        case State::IN_SE:
            dealSe(name,type);
            break;
        case State::IN_FLOAT:
            dealFloat(name,type);
            break;
        case State::IN_IDN:
            dealIDN(name,type);
            break;
        case State::IN_INT:
            dealInt(name,type);
            break;
        case State::IN_KW:
            dealKw(name,type);
            ////cout << "INTO KW" << endl;
            break;
        case State::IN_OP:
            ////cout << "AND / OR / XOR" <<endl;
            dealOp(name,type);
            break;
        case State::IN_STR:
            dealStr(name,type);
            break;
        case State::END:
            token = dealEnd(name,type);
            ////auto token = dealEnd(name,type);
            strcpy(token.value, token.name); 
            ////cout<<"END"<<endl;
            ////cout<<token.name<<endl;
            ////cout<<token.value<<endl;
            ////cout<<token.type<<endl;
            ////cout<<token.line<<endl;
            ////cout<<token.index<<endl;
            return token;
        }
        ////cout<<"GAME OVER"<<endl;
    }
    strcpy(token.name, "$");
    token.line = line;
    token.type = TokenType::OTHER;
    strcpy(token.value, "$");
    ////token->next = NULL;

    ////cout << "OUT" << endl;
    return token;
}




















// !
//vector<TokenNode*> tokens;

/*
 *scanner
 * Author: gsq,
 * Date: 2022-4-1,
 */
void scanner() {
    FILE *infile;
    string Filename = "test.txt";
    ifstream in(Filename);
    
    code = "";
    line = 1;
    
    if(in) {
        code = string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        iter = code.cbegin();
        //cout << code[0] << endl;
    } 
    else {
        printf("Can not find the file.\n");
        return;
    }


    //TokenNode *token_;
    //strcmp(token_->name,"$")!=0
    
    int i=0;
    ////for(TokenNode *token_ = getNextToken(); token_,i++; i<=1,token_ = getNextToken()) {
    for(TokenNode token_ = getNextToken(); token_; token_ = getNextToken()) {
        ////cout << token_.name <<endl;
        tokens.push_back(token_);
        
        /*for (int i = 0; i<tokens.size(); ++i){
            ////cout << typeid(tokens[i]->name).name()<<endl;
            string s(tokens[i].name);
            cout <<tokens[i].name<<"    "<<"<"<<TokenDict[tokens[i].type]<<", "<< seekKey(s) <<">"<<endl; //seekKey(tokens[i]->name) 
        } 
        cout << "NO Segmentation fault yet.\n";
        */
    }

    //!
    ////cout<<"CANNOT REACH HERE."<<endl;


	/*for (int i = 0; i<tokens.size(); ++i) {
        string s(tokens[i].name);
        cout <<tokens[i].name<<"    "<<"<"<<TokenDict[tokens[i].type]<<", "<< seekKey(s) <<">"<<endl;
    }*/
    /*
    for(auto token : tokens) {
        string s(tokens[i].name);
        cout <<tokens[i].name<<"    "<<"<"<<TokenDict[tokens[i].type]<<", "<< seekKey(s) <<">"<<endl;
    }
    */

}




/*
 *printTokenLink
 * Author: gsq,
 * Date: 2022-4-2,
 */
void printTokenLink() {
    cout << "Start to Print" << endl;
    
    for(auto token : tokens) {
        string s(token.name);
        if(seekKey(s)<30) 
            cout <<token.name<<"    "<<"<"<<TokenDict[token.type]<<", "<< seekKey(s) <<">" << "     " << "in line: "<<token.line<<endl;
        else if(seekKey(s)>50 && seekKey(s)<70)
            cout <<token.name<<"    "<<"<"<<TokenDict[token.type]<<", "<< seekKey(s)-50 <<">"<< "      "<< "in line: "<<token.line<<endl;
        else if(seekKey(s)>80 && seekKey(s)<90)
            cout <<token.name<<"    "<<"<"<<TokenDict[token.type]<<", "<< seekKey(s)-80 <<">"<< "      "<< "in line: "<<token.line<<endl;
        else 
            cout <<token.name<<"    "<<"<"<<TokenDict[token.type]<<", "<< token.value <<">"<< "     "<< "in line: "<<token.line<<endl;
    }

}