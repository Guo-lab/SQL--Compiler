/*
* @Author: gsq,
* @Date: 2022-4-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include <cstdio>

#include "/Users/gsq/Desktop/SQL--Compiler/Lexer/Lexer.h"
#include "/Users/gsq/Desktop/SQL--Compiler/Lexer/Lexer.cpp"


using namespace std;

int main() {
    printf("Start to compile.\n");
    
    //TODO
    initMap();
    //initNode();
    scanner();

    printTokenLink();
    return 0;
}