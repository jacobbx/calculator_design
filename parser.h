#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include "element.h"
#include <stack>

class Parser {

private:
    int OperatorPrecedence(char op);
    void OrderOp(std::stack<char>& operator_stack, std::stack<Element*>& element_stack);

public:
    Parser() = default;
    Element*Parse(const std::string& equationStr);
};
#endif