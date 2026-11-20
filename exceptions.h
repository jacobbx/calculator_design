#include <iostream>
#include <string>
#include <stdexcept>

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class InvalidElement : public std::invalid_argument
{

    // claude helped me refactor what I originally tried on my own
    // I was writing classes that were unable to compile due to using
    // a default constructor that did not exist

public:
    explicit InvalidElement(const std::string &message = "Invalid Element") : std::invalid_argument(message) {}
};

class InvalidOperator : public std::invalid_argument
{

public:
    explicit InvalidOperator(const std::string &message = "Invalid Operator") : std::invalid_argument(message) {}
};

class DivideByZeroError : public std::domain_error
{

public:
    explicit DivideByZeroError(const std::string &message = "Division by zero error") : std::domain_error(message) {}
};

class ModuloByDoubleError : public std::domain_error
{

public:
    explicit ModuloByDoubleError(const std::string &message = "Modulo by double error") : std::domain_error(message) {}
};

class InvalidEquationStructure : public std::invalid_argument
{

public:
    explicit InvalidEquationStructure(const std::string &message = "Syntax error with equation") : std::invalid_argument(message) {}
};
#endif