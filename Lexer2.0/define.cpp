#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <iostream>

#include "define.h"
#include "main.h"


using namespace std;

map<string, int> kMap;    //定义关键字表
map<string, int> oMap;    //定义运算符号表
map<string, int> sMap;    //定义限界符号表
map<string, int> MMap;    //显示自己的值的符号表 



void initMap() {
    kMap.clear();
    kMap.insert(make_pair("SELECT", SELECT));
    kMap.insert(make_pair("FROM", FROM));
    kMap.insert(make_pair("WHERE", WHERE));
    kMap.insert(make_pair("AS", AS));
    kMap.insert(make_pair("INSERT", INSERT));
    kMap.insert(make_pair("INTO", INTO));
    kMap.insert(make_pair("VALUES", VALUES));
    kMap.insert(make_pair("UPDATE", UPDATE));
    kMap.insert(make_pair("DELETE", DELETE));
    kMap.insert(make_pair("JOIN", JOIN));
    kMap.insert(make_pair("LEFT", LEFT));
    kMap.insert(make_pair("RIGHT", RIGHT));
    kMap.insert(make_pair("MIN", MIN));
    kMap.insert(make_pair("MAX", MAX));
    kMap.insert(make_pair("AVG", AVG));
    kMap.insert(make_pair("SUM", SUM));
    kMap.insert(make_pair("UNION", UNION));
    kMap.insert(make_pair("ALL", ALL));
    kMap.insert(make_pair("GROUP BY", GROUP_BY));
    kMap.insert(make_pair("HAVING", HAVING));
    kMap.insert(make_pair("DISTINCT", DISTINCT));
    kMap.insert(make_pair("ORDER BY", ORDER_BY));
    kMap.insert(make_pair("TRUE", TRUE));
    kMap.insert(make_pair("FALSE", FALSE));
    kMap.insert(make_pair("IS", IS));
    kMap.insert(make_pair("NOT", NOT));
    kMap.insert(make_pair("NULL", NULL_));
    kMap.insert(make_pair("GROUP", GROUP));
    kMap.insert(make_pair("ORDER", ORDER));
    kMap.insert(make_pair("SET", SET));
    kMap.insert(make_pair("ON", ON));
    kMap.insert(make_pair("COUNT", COUNT));

    oMap.clear();
    oMap.insert(make_pair("=", EQUAL));
    oMap.insert(make_pair(">", GRT_THAN));
    oMap.insert(make_pair("<", LES_THAN));
    oMap.insert(make_pair(">=", GRT_EQUAL));
    oMap.insert(make_pair("<=", LES_EQUAL));
    oMap.insert(make_pair("!=", NOT_EQUAL));
    oMap.insert(make_pair("<=>", NOT_EQUAL_));
    oMap.insert(make_pair("AND", AND));
    oMap.insert(make_pair("&&", AND_));
    oMap.insert(make_pair("||", OR_));
    oMap.insert(make_pair("OR", OR));
    oMap.insert(make_pair("XOR", XOR));
    oMap.insert(make_pair(".", POINT));

    sMap.clear();
    sMap.insert(make_pair("(", LEFT_BRA));
    sMap.insert(make_pair(")", RIGHT_BRA));
    sMap.insert(make_pair(",", COMMA));

    MMap.clear();
    MMap.insert(make_pair("STRING", STRING));
    MMap.insert(make_pair("FLOAT", FLOAT));
    MMap.insert(make_pair("INT", INT));
    MMap.insert(make_pair("IDN", IDN));
    MMap.insert(make_pair("OTHER", OTHER));

}