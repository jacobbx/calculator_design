# Compiler
GPP = g++

# Compilation flags
REQUIRED = -Wall -Wextra -Werror -Wfatal-errors
# You can Modify the Compiler below Compiler 
GPPFlags = $(REQUIRED) -std=c++20
Debug = -g

# source and output names
HWNUM = HW5

# GUI
QT_PREFIX ?= $(HOME)/Qt/6.12.0/macos
GUI_BUILD = build
GUI_SRC = calc_gui.cpp calculatorwindow.cpp
GUI_HEADER = calculatorwindow.h
GUI_EXTRA = CMakeLists.txt

# Rename this to the name of your main file
SRC = calc.cpp element.cpp operation.cpp parser.cpp
MAIN = calc.cpp
HEADER =  element.h operation.h exceptions.h parser.h
OBJ = element.o operation.o parser.o

#Update this with your first and last name
TARNAME = Jacob_Hessler

# Target Name. This will be the name of the executable created by running "Make"
TARGET = calculator
# The DEFAULT_GOAL variable will make it so that running "make" without any arguments will run "make calculator"
.DEFAULT_GOAL := $(Target)

# compile
$(TARGET): $(HWNUM).a
	$(GPP) $(GPPFlags) -o $(TARGET) $(MAIN) $<

%.o: %.cpp $(HEADER)
	$(GPP) $(GPPFlags) -c $< -o $@

$(HWNUM).a: $(OBJ)
	ar -rcs $(HWNUM).a $^

# clean
# Running make clean should clean up any unnecessary components
clean:
	rm -f $(TARGET) *.o *.a
	rm -rf $(GUI_BUILD)
	@echo "Removed all object files."

gui:
	cmake -S . -B $(GUI_BUILD) -DCMAKE_PREFIX_PATH=$(QT_PREFIX)
	cmake --build $(GUI_BUILD)

run-gui: gui
	open $(GUI_BUILD)/calculator_gui

# Debug option "make debug". This enables the GNU Debugger "gdb"
debug: $(SRC)
	$(GPP) $(GPPFlags) ($SRC) $(Debug) -o $(TARGET)
	@echo "Compiled Debug"

package:
#   tar -c Makefile $(SRC) -f $(HWNUM)_$(TARNAME).tar
#   Uncomment the Below line when you add headerfiles and comment out the above line
	tar -cf $(HWNUM)_$(TARNAME).tar Makefile $(SRC) $(HEADER) $(GUI_SRC) $(GUI_HEADER) $(GUI_EXTRA)