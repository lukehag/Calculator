#include <string>
#include <vector>
using namespace std;

#include "Calculator.h"

void Calculator::sortInput() {
    float num = 0;
    float tempDecimal = 0; // To store numbers who are in decimal places
    float decimalPlace = 1; // To keep track of the decimal places of a number
    bool isDecimal = false;
    
    for (int i = 0; i < input.length(); i++) {
        if (isdigit(input.at(i))) { // If char is digit, sort into variable num (or tempDecimal if 'isDecimal' is true)
            if (isDecimal) {
                tempDecimal *= 10;
                tempDecimal += (float)input.at(i) - 48;
                decimalPlace *= 10; // Add another decimal place
            } else {
                num *= 10;
                num += (float)input.at(i) - 48;
            }
        } else if (input.at(i) == '.') { // '.' indicates that the next set of numbers will be in a decimal, so tell program to expect decimals
            isDecimal = true;
        } else { // A operator signifies a new number, so calculate decimal and sort variable num and current operator
            // Tell program to stop searching for decimals and add decimals into variable num
            isDecimal = false;
            num += tempDecimal / decimalPlace;
            
            // Put variable num and operators into respective vectors, and reset variable num
            numbers.push_back(num);
            operators.push_back(input.at(i));
            num = 0.0;
        }
    }
    // Sort negative numbers
    // If the first character in 'input' is '-' then delete the first number (which is 0), and delete first operator (which is '-') then make the actual first number into a negative
    if (input.at(0) == '-') {
        numbers.erase(numbers.begin());
        operators.erase(operators.begin());
        numbers.at(0) *= -1;
    }
    // Sorts through 'operator' vector and checks for '-' operators, it then changes the operator into '+' and changes the number behind said operator into a negative value
    for (int i = 0; i < operators.size(); i++) {
        if (operators.at(i) == '-') {
            operators.at(i) = '+';
            numbers.at(i + 1) *= -1;
        }
    }
}

float Calculator::calculate() {
    sortInput();
    
    while (operators.size() > 1) { // Keep checking the first index in 'operators' until the vector is empty
        switch (operators.at(0)) {
            case '+':
                // Check for and calculate higher priority operators before continuing
                if (operators.at(1) == '*') {
                    numbers.at(1) *= numbers.at(2);
                    numbers.erase(numbers.begin() + 2);
                    operators.erase(operators.begin() + 1);
                } else if (operators.at(1) == '/') {
                    numbers.at(1) /= numbers.at(2);
                    numbers.erase(numbers.begin() + 2);
                    operators.erase(operators.begin() + 1);
                }
                
                numbers.at(0) += numbers.at(1);
                numbers.erase(numbers.begin() + 1);
                operators.erase(operators.begin());
                break;
            
            case '*':
                numbers.at(0) *= numbers.at(1);
                numbers.erase(numbers.begin() + 1);
                operators.erase(operators.begin());
                break;
            
            case '/':
                numbers.at(0) /= numbers.at(1);
                numbers.erase(numbers.begin() + 1);
                operators.erase(operators.begin());
                break;
        }
    }
    return numbers.at(0);
}