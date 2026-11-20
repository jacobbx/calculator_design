#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>

// https://claude.ai/chat/86e0c249-49c2-4a5e-a74e-c87ac83dcb3f
// https://en.wikipedia.org/wiki/Qt_(software)
// https://github.com/madhawapolkotuwa/QtWithVSCode_LoginForm/blob/main/mainwindow.h
// forward declarations
class QLineEdit;
class QLabel;
class QPalette;

class CalculatorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWindow(QWidget *parent = nullptr);

private:
    QLineEdit *display_;
    QLabel *result_;
    QPalette *background_;

    void append(const QString &text);
    void evaluate();
};
#endif