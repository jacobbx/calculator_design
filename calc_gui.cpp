#include <QApplication>
#include "calculatorwindow.h"

// https://en.wikipedia.org/wiki/Qt_(software)
// https://github.com/madhawapolkotuwa/QtWithVSCode_LoginForm/blob/main/main.cpp
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CalculatorWindow w;
    w.show();
    return app.exec();
}