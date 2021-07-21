#ifndef __ALGEBRAICEXPRESSION_H
#define __ALGEBRAICEXPRESSION_H
#include "Stack.h"
#include <iostream>

std::string infix2postfix ( const std::string exp );
double evaluatePostfix ( const std::string exp );
int precedence(const char ch);

bool isExistsDigit(const char ch);

#endif