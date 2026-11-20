#include <iostream>
#ifndef ELEMENT_H
#define ELEMENT_H

class Element {

private:
    double value_;
    bool isDouble_;
    int validateString(std::string);

public:
    Element();
    Element(int newInt);
    Element(double newDouble);
    Element(const std::string& newVal);
    virtual double Value() const;
    virtual double DoubleValue() const;
    virtual int IntValue() const;
    virtual bool IsDouble() const;
    virtual void Value(double);
    void ChangeType();
    virtual Element* Clone() const {return new Element(*this);};
    friend Element operator+(const Element&, const Element&);
    friend Element operator-(const Element&, const Element&);
    friend Element operator*(const Element&, const Element&);
    friend Element operator/(const Element&, const Element&);
    friend Element operator%(const Element&, const Element&);
    friend std::ostream& operator<<(std::ostream&, const Element&);
    virtual ~Element() = default;
};
#endif 