#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <string>
#include "element.h"


//inheriting
class Operation : public Element {

private:
    //no pointers = no polymorphism
    //need pointers to execute polymorphism
    Element* left_;
    Element* right_;
    char op_;

public:
    Operation(const std::string& element);
    Operation(const Element& leftElem, char op, const Element& rightElem);
    Operation(const Operation& other);
    Operation& operator=(Operation other);
    virtual ~Operation();

    virtual double Value() const override;
    virtual int IntValue() const override;
    virtual double DoubleValue() const override;
    virtual bool IsDouble() const override;
    virtual Element* Clone() const override {return new Operation(*this);};
    friend std::ostream& operator<<(std::ostream&, const Operation&);
};
#endif