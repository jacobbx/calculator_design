#include "element.h"
#include <stdexcept>
#include "exceptions.h"

using namespace std;

Element::Element() {
    value_ = 0.0;
    isDouble_ = true;
}

Element::Element(int newInt) : value_(newInt), isDouble_(false) {}

Element::Element(double newDouble) : value_(newDouble), isDouble_(true) {}

Element::Element(const std::string& newVal) {
    int validate_int = validateString(newVal);
    //double case
    if(validate_int == 1) {
        isDouble_ = true;
        value_ = stod(newVal);
    }
    else if(validate_int == 2) {
        isDouble_ = false;
        value_ = stod(newVal);
    }
    else {
        throw InvalidElement("Error: string argument cannot be parsed: " + newVal);
    }
}


//three return values - 1, 2, 3
//1 - double
//2 - integer
//3 - invalid
int Element::validateString(string element) {

    try {
        //if it is a double
        if(element.find(".") != string::npos) {
            (void)stod(element);
            return 1;
        }
        else {
            (void)stoi(element);
            return 2;
        }
    }
    catch(const exception &e) {
        return 3;
    }
}


//Returns the stored value based on the mode the element object is in
double Element::Value() const {
    if(!isDouble_) {
        return static_cast<int>(value_);
    }
    else {
        return value_;
    }
}

//Returns the stored value as a double
double Element::DoubleValue() const {
    return value_;
}

//Returns the stored value as an integer. Truncate the decimal portion
int Element::IntValue() const {
    return static_cast<int>(value_);
}

//Returns true if the object is currently set to double type, or false if it is set to integer type
bool Element::IsDouble() const {
    return isDouble_;
}

//Updates the value stored in the Element object. This setter does not change the nature of the Element. So if the element is current in "int" mode and we set the value to "3.5" just update the value do not truncate the floating point
void Element::Value(double newVal) { 
    value_ = newVal;
}

//Toggles the state the class is in between double and int modes. This should not change the "Value" stored just the return type of the method "Value()"
void Element::ChangeType() {
    isDouble_ = !isDouble_;
}

//operator overloading
Element operator+(const Element& left_val, const Element& right_val) {
    // if either value is a double, we do double math
    if(left_val.isDouble_ || right_val.isDouble_) {
        Element sum(left_val.value_ + right_val.value_);
        return sum;
    }
    //if both are integer we do integer math
    else {
        Element sum(left_val.IntValue() + right_val.IntValue());
        return sum;
    }
}

Element operator-(const Element& left_val, const Element& right_val) {
    // if either value is a double, we do double math
    if(left_val.isDouble_ || right_val.isDouble_) {
        Element difference(left_val.value_ - right_val.value_);
        return difference;
    }
    //if both are integer we do integer math
    else {
        Element difference(left_val.IntValue() - right_val.IntValue());
        return difference;
    }
}

Element operator*(const Element& left_val, const Element& right_val) {
    //if either value is a double, we do double math
    if(left_val.isDouble_ || right_val.isDouble_) {
        Element product(left_val.value_ * right_val.value_);
        return product;
    }
    //if both are integer we do integer math
    else {
        Element product(left_val.IntValue() * right_val.IntValue());
        return product;
    }
}

Element operator/(const Element& left_val, const Element& right_val) {
    // divide by zero error
    if(right_val.value_ == 0) {
        throw DivideByZeroError("Error: Cannot perform division by 0");
    }
    
    // if either value is a double, we do double math
    if(left_val.isDouble_ || right_val.isDouble_) {
        Element quotient(left_val.value_ / right_val.value_);
        return quotient;
    }
    //if both are integer we do integer math
    else {
        Element quotient(left_val.IntValue() / right_val.IntValue());
        return quotient;
    }
}

Element operator%(const Element& left_val, const Element& right_val) {
    //cannot perform modulo with floating point or by zero
    if(right_val.value_ == 0) {
        throw DivideByZeroError("Error: Modulo by zero");
    }

    if(left_val.isDouble_ || right_val.isDouble_) {
        throw ModuloByDoubleError("Error: Cannot perform modulo on floating point");
    }
    //if both are integer we do integer math
    else {
        Element remainder(left_val.IntValue() % right_val.IntValue());
        return remainder;
    }
}

ostream& operator<<(std::ostream& os, const Element& element) {
    if(element.IsDouble()) {
        os << element.DoubleValue();
    }
    else {
        os << static_cast<int>(element.IntValue());
    }
    return os;
}

