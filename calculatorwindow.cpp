#include "calculatorwindow.h"
#include "operation.h"
#include "exceptions.h"
#include "parser.h"
#include "element.h"

#include <QGridLayout>
#include <QPalette>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <exception>

// https://doc.qt.io/qt-6/stylesheet.html
// https://claude.ai/chat/86e0c249-49c2-4a5e-a74e-c87ac83dcb3f
// https://en.wikipedia.org/wiki/Qt_(software)

using namespace std;

CalculatorWindow::CalculatorWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Calculator");

    // the display for result and enter math bar
    display_ = new QLineEdit;
    display_->setPlaceholderText("e.g. 4.6 - 99");
    result_ = new QLabel("Result: ");

    // set background color to dark gray
    background_ = new QPalette;
    background_->setColor(QPalette::Window, Qt::darkGray);
    setPalette(*background_);
    setAutoFillBackground(true);

    // calculator buttons
    auto* grid = new QGridLayout;
    const char* labels[5][4] = {
        {"", "", "(", ")"},
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "%", "+"}
    };

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 4; ++c) {
            QString text = labels[r][c];
            auto* btn = new QPushButton(text);
            btn->setMinimumSize(50, 50);
            bool isOp = QString("+-*/%()").contains(text);
            // operators get spaces so Operation can split into 3 tokens
            QString toAppend = isOp ? " " + text + " " : text;
            connect(btn, &QPushButton::clicked, this,
                    [this, toAppend] { append(toAppend); });
            grid->addWidget(btn, r, c);
        }
    }

    auto* equals = new QPushButton("=");
    auto* clear = new QPushButton("C");
    connect(equals, &QPushButton::clicked, this, &CalculatorWindow::evaluate);
    connect(clear, &QPushButton::clicked, this, [this] {
        display_->clear();
        result_->setText("Result: ");
    });
    grid->addWidget(clear, 5, 0, 1, 2);
    grid->addWidget(equals, 5, 2, 1, 2);

    // pressing Enter in the text box also evaluates
    connect(display_, &QLineEdit::returnPressed, this, &CalculatorWindow::evaluate);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(display_);
    layout->addWidget(result_);
    layout->addLayout(grid);
}

void CalculatorWindow::append(const QString& text) {
    display_->setText(display_->text() + text);
}

void CalculatorWindow::evaluate() {
    try {
        // Operation op(display_->text().toStdString());
        Parser parser;
        Element* equation = parser.Parse(display_->text().toStdString());
        result_->setStyleSheet("");
        result_->setText("Result: " + QString::number(equation->Value(), 'g', 12));
    }
    catch (const exception& e) {
        result_->setStyleSheet("color: red;");
        // printing 'error' twice
        // result_->setText(QString("Error: ") + e.what());
        result_->setText(QString() + e.what());
    }
}