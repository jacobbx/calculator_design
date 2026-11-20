#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <unistd.h>
#include "operation.h"
#include "exceptions.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    
/*   if(argc <= 1) {
        cerr << "Usage: Enter either a filename to parse or an equation to be parsed in the format of 'Left_Element Operator Right_Element'" << endl;
        return 1;
    }
*/
    // https://claude.ai/chat/0fbb7109-18c5-43ae-ab24-ffe3b13767f8
    // while getOpt() for flag checking, switch
    if(argc == 1) {
        cerr << "Usage: " << argv[0] << " needs to be ran with [-c | -f] [args..]\n";
        return 1;
    }

    int c;
    bool is_c = false;
    bool is_f = false;
    while((c = getopt(argc, argv, ":c:f:")) != -1) {
        switch(c) {
            case 'c':
                is_c = true;
                is_c = optarg;
                if(optarg != argv[optind - 1] && optarg[0] == 'f') {
                    cerr << "Error: -c and -f cannot be used together\n" << endl;
                    return 2;
                }
                break;
            case 'f':
                is_f = true;
                is_f = optarg;
                if(optarg != argv[optind - 1] && optarg[0] == 'c') {
                    cerr << "Error: -c and -f cannot be used together\n" << endl;
                    return 2;
                }
                break;
            case '?':
                cerr << "Error: Unknown command: -" << static_cast<char>(optopt) << "\n" << endl;
                return 2;
            case ':':
                cerr << "Error: -" << static_cast<char>(optopt) << " requires arguments\n" << endl;
                return 2;
        }       
    }
    if(is_c && is_f) {
        cerr << "Error: -c and -f cannot be used together\n" << endl;
        return 2;
    }

/*    if(argc == 2) {
*/
    if(is_f) {
        // string filePath = argv[1];
        string filePath = argv[2];
        ifstream file(filePath);

        if(!file.is_open()) {
            cerr << "Error getting file." << endl;
            return 2;
        }

        string line;
        int line_counter = 0;

        //file mode

        while(getline(file, line)) {
            if(line.empty()) continue;

            line_counter++;
            Parser equation_parser;

            try {

                // Operation equation(line);
                Element* equation = equation_parser.Parse(line);
                cout << equation->Value() << endl;

            }
            catch(const exception& e) {
                cerr << e.what();
                return line_counter + 2;
            }
        }
        file.close();
        return 0;
    }
    
    //terminal mode
/*    if(argc == 4) {
*/
    else if(is_c) {
        // why did it not work using argc - optind != 3
        if(argc != 5) {
            cerr << "Error: Not enough arguments" << endl;
            return 2;
        }

        string left_elem = argv[2];
        string op_arg = argv[3];
        string right_elem = argv[4];

        string combined_equation = left_elem + " " +  op_arg + " " + right_elem;

        try {
            Operation equation(combined_equation);
            cout << equation.Value() << endl;
        }
        catch(const InvalidOperator& e) {
            cerr << e.what() << endl;
            return 4;
        }
        catch(const InvalidElement& e) {
            cerr << e.what() << endl;
            return 3;
        }
        catch(const DivideByZeroError& e) {
            cerr << e.what() << endl;
            return 5;
        }
        catch(const ModuloByDoubleError& e) {
        cerr << e.what() << endl;
        return 5;
        }
    }
    else {
        //optind starts at 1
        // asks which argv element getopt should look at next
        // optind is the index of the first arg that getopt 
        // did not use
        
        Parser equation_parser;

        while(argc > optind) {
            try {
                // Element equation(equation_based_on_operations);
                string equation_based_on_operations = argv[optind];
                Element* result = equation_parser.Parse(equation_based_on_operations);
                double value = result->Value();
                // cout << argv[optind++] << " = " <<  equation_parser.Parse(equation_based_on_operations)->Value() << endl;
                cout << argv[optind++] << " = " <<  value << endl;

            }
            catch(const exception& e) {
                cerr << e.what() << endl;
                // return index of arguemnt that failed + 2
                return 2 + optind;
            }
        }
    }
/*    else {
        cerr << "Error: Executed with incorrect parameter count" << endl;
        return 2;
    }
*/
    return 0;
}

