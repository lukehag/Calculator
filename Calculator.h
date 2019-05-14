#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
    public:
        Calculator(string input) { this->input = input; } // Initializes input
        void sortInput(); // Separates the input(string) into a numbers vector(float) and operators vector(char)
        float calculate(); // Creates answer based on numbers, operators and order of operations

    private:
        string input;
        vector<float> numbers;
        vector<char> operators;
};

#endif