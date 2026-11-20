#include "operation.h"
#include "exceptions.h"
#include <memory>
#include <sstream>
#include <utility>

using namespace std;



//parses 3 token equation
Operation::Operation(const string& equation) : Element() {
    string left_element, right_element, op;
    string valid_operators = "+-*/%";
    
    stringstream line_stream(equation);

    if(!(line_stream >> left_element >> op >> right_element)) {
        throw InvalidElement("Error: Invalid equation: " + equation + '\n');
    }

    if(op.length() != 1 || valid_operators.find(op[0]) == string::npos) {
        throw InvalidOperator("Error: Invalid operator: " + op + '\n');
    }

    string excess;
    if(line_stream >> excess) {
        throw InvalidElement("Error: equation contains too many values: " + equation + '\n');
    }

    Element* left_pointer = nullptr;
    Element* right_pointer = nullptr;

    try {
        left_pointer = new Element(left_element);
        right_pointer = new Element(right_element);
    }
    catch(const InvalidElement& e) {
        delete left_pointer;
        delete right_pointer;
        throw;
    }

    left_ = left_pointer;
    right_ = right_pointer;
    op_ = op[0];
}

Operation::Operation(const Element& leftElem, char op, const Element& rightElem) : Element(), left_(leftElem.Clone()), right_(rightElem.Clone()), op_(op) 
{
    string valid_operators = "+-*/%";

    if(valid_operators.find(op) == string::npos) {
        throw InvalidOperator(string("Error: Invalid operator: ") + op + '\n');
    }
}

//copy constructor
Operation::Operation(const Operation& other) : Element(other), left_(other.left_->Clone()), right_(other.right_->Clone()), op_(other.op_) {}

Operation& Operation::operator=(Operation other) {
    swap(left_, other.left_);
    swap(right_, other.right_);
    swap(op_, other.op_);
    return *this;
}

Operation::~Operation() {
    delete left_;
    delete right_;
}

double Operation::Value() const {
    Element left_value(left_ -> Value());
    Element right_value(right_-> Value());

    //if not supposed to be a double
    if(!left_->IsDouble()) {
        left_value = Element(left_->IntValue());
    }

    if(!right_->IsDouble()) {
        right_value = Element(right_->IntValue());
    }

    Element result(0);

    switch(op_) {
        case '+':
            result = left_value + right_value;
            break;
        
        case '-':
            result = left_value - right_value;
            break;

        case '*':
            result = left_value * right_value;
            break;
        
        case '/':
            result = left_value / right_value;
            break;

        case '%':
            result = left_value % right_value;
            break;

        default:
            //claude.ai helped me understand to throw an exception to be caught later, instead of cerr.
            //cerr only prints, and needs to return something; I was returning error code
            //that error code needs to be returned after a catch, and the program needs to be stopped right when the error occurs
            throw InvalidOperator(string("Error: Invalid operator: ") + op_); 
    }

    return result.Value();
}

int Operation::IntValue() const {
    Element left_value(left_ -> IntValue());
    Element right_value(right_-> IntValue());

    Element result(0);

    switch(op_) {
        case '+':
            result = left_value + right_value;
            break;
        
        case '-':
            result = left_value - right_value;
            break;

        case '*':
            result = left_value * right_value;
            break;
        
        case '/':
            result = left_value / right_value;
            break;

        case '%':
            result = left_value % right_value;
            break;

        default:
            //claude.ai helped me understand to throw an exception to be caught later, instead of cerr.
            //cerr only prints, and needs to return something; I was returning error code
            //that error code needs to be returned after a catch, and the program needs to be stopped right when the error occurs
            throw InvalidOperator(string("Error: Invalid operator: ") + op_); 
    }

    return result.IntValue();
}

double Operation::DoubleValue() const {
    Element left_value(left_ -> DoubleValue());
    Element right_value(right_-> DoubleValue());

    Element result(0.0);

    switch(op_) {
        case '+':
            result = left_value + right_value;
            break;
        
        case '-':
            result = left_value - right_value;
            break;

        case '*':
            result = left_value * right_value;
            break;
        
        case '/':
            result = left_value / right_value;
            break;

        case '%':
            result = left_value % right_value;
            break;

        default:
            //claude.ai helped me understand to throw an exception to be caught later, instead of cerr.
            //cerr only prints, and needs to return something; I was returning error code
            //that error code needs to be returned after a catch, and the program needs to be stopped right when the error occurs
            throw InvalidOperator(string("Error: Invalid operator: ") + op_); 
    }

    return result.DoubleValue();
}

bool Operation::IsDouble() const {
    return left_->IsDouble() || right_->IsDouble();
}

ostream& operator<<(ostream& print, const Operation& operation) {
    return print << "(" << *(operation.left_) << " " << operation.op_ << " " << *(operation.right_) << ")";
}

