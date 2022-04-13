#ifndef _DEFINE_H
#define _DEFINE_H

#include <string>
#include <map>
#include <vector>


//% KW 关键字
#define SELECT 1
#define FROM 2
#define WHERE 3
#define AS 4
#define INSERT 5
#define INTO 6
#define VALUES 7  
#define UPDATE 8
#define DELETE 9
#define JOIN 10
#define LEFT 11
#define RIGHT 12
#define MIN 13
#define MAX 14
#define AVG 15
#define SUM 16
#define UNION 17
#define ALL 18
#define GROUP_BY 19
#define HAVING 20
#define DISTINCT 21
#define ORDER_BY 22
#define TRUE 23
#define FALSE 24
#define IS 25
#define NOT 26
#define NULL_ 27
//以下是自己添加的
#define GROUP 28
#define ORDER 29
#define SET 30
#define ON 31
#define COUNT 32


//% OP 运算符
#define EQUAL 51         // =
#define GRT_THAN 52      // >
#define LES_THAN 53      // <
#define GRT_EQUAL 54     // >=
#define LES_EQUAL 55     // <=
#define NOT_EQUAL 56     // !=
#define NOT_EQUAL_ 57    // <=>
#define AND 58           // AND
#define AND_ 59          // &&
#define OR_ 60           // ||
#define OR 61            // OR
#define XOR 62           // XOR
#define POINT 63         // .

//% SE 限界符
#define LEFT_BRA 81      // (
#define RIGHT_BRA 82     // )
#define COMMA 83         // ,


void initMap();


#endif
