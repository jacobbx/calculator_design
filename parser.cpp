#include "parser.h"
#include "exceptions.h"
#include "operation.h"
#include <memory>
#include <utility>
#include <stack>
#include <sstream>

using namespace std;

int Parser::OperatorPrecedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    return 0;
}

void Parser::OrderOp(stack<char> &operator_stack, stack<Element *> &element_stack)
{
    if (element_stack.size() < 2)
    {
        throw InvalidEquationStructure("Error: Too few elements \n");
    }

    Element *right = element_stack.top();
    element_stack.pop();

    Element *left = element_stack.top();
    element_stack.pop();

    char op = operator_stack.top();
    operator_stack.pop();

    try
    {
        element_stack.push(new Operation(*left, op, *right));
    }
    catch (InvalidOperator &e)
    {
        delete right;
        delete left;
        throw;
    }

    delete right;
    delete left;
}

Element *Parser::Parse(const string &equationStr)
{
    string valid_operators = "+-*/%";

    // two stack approach
    stack<Element *> element_stack;
    stack<char> operator_stack;

    stringstream line_stream(equationStr);

    try
    {
        string component;

        while (line_stream >> component)
        {
            // if it is an operator
            if (component.length() == 1 && valid_operators.find(component[0]) != string::npos)
            {
                char op = component[0];
                int precedence_result = OperatorPrecedence(op);

                // if top is greater precedence than our current component
                while (!operator_stack.empty() && operator_stack.top() != '(' && precedence_result <= OperatorPrecedence(operator_stack.top()))
                {
                    OrderOp(operator_stack, element_stack);
                }
                operator_stack.push(op);
            }

            else if (component == "(")
            {
                operator_stack.push(component[0]);
            }
            else if (component == ")")
            {
                while (!operator_stack.empty() && operator_stack.top() != '(')
                {
                    OrderOp(operator_stack, element_stack);
                }
                if (operator_stack.empty())
                {
                    throw InvalidEquationStructure("Error: Missing left parenthesis \n");
                }
                // should pop left parenthesis when found, as it will be top
                operator_stack.pop();
            }
            // element case
            else
            {
                element_stack.push(new Element(component));
            }
        }

        while (!operator_stack.empty())
        {
            if (operator_stack.top() == '(')
            {
                throw InvalidEquationStructure("Error: Missing right hand parenthesis \n");
            }
            OrderOp(operator_stack, element_stack);
        }

        if (element_stack.size() != 1)
        {
            throw InvalidEquationStructure("Error: Too many elements \n");
        }
    }
    catch (exception &e)
    {
        while (!element_stack.empty())
        {
            delete element_stack.top();
            element_stack.pop();
        }
        throw;
    }

    return element_stack.top();
}
