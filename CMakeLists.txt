cmake_minimum_required(VERSION 3.16)
project(CalculatorGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.12.0/macos")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(calculator_gui
    calc_gui.cpp
    calculatorwindow.cpp calculatorwindow.h
    element.cpp operation.cpp parser.cpp)

target_link_libraries(calculator_gui PRIVATE Qt6::Widgets)