#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <stdexcept>
using namespace std;

#include "Calculator.h"

int main() {
    // Initialize variables
    string input;
    
    // Set decimal places
    cout << setprecision(9);
    
    // Output prompt
    cout << "Calculator" << endl
         << "Always end input with '='" << endl
         << "Type 'exit' to end program" << endl
         << "===========================" << endl;
    
    while (true) {
        try {
            // Prompt for input
            cout << "Enter calculation:" << endl;
            cin >> input;
            
            // Exit program when prompted
            if (input == "exit") {
                cout << "Exiting..." << endl;
                return 0;
            }
            
            // Check for invalid input
			if (input.front() != '-' && ispunct(input.front())) {
				throw runtime_error("Input has invalid format");
			}

			if (input.back() != '=') {
				throw runtime_error("'=' is not found");
			}

            for (int i = 0; i < input.size(); i++) {
                if (isalpha(input.at(i))) {
                    throw runtime_error("Input has alphabetic characters");
                } else if (!isalnum(input.at(i)) && input.at(i) != '+' && input.at(i) != '-' && input.at(i) != '*' && input.at(i) != '/' && input.at(i) != '=') {
                    throw runtime_error("Input has invalid symbols");
                }

				if (input.at(i) == '/' && input.at(i+1) == '0') {
					throw runtime_error("Cannot divide by zero");
				}

				if (input.at(i) != '=' && (ispunct(input.at(i)) && ispunct(input.at(i + 1)))) {
					throw runtime_error("Must have number between symbols");
				}
            }
        } catch (runtime_error& excpt) {
            // Display error message and handle error by going back to prompt
            cerr << "ERROR: " << excpt.what() << endl << endl;
            continue;
        }
        
        // Initialize Calculator class
        Calculator calc(input);
    
        // Output solution
        cout << "Solution: " << calc.calculate() << endl << endl;
    }
    return 0;
}