#include <iostream>
#include <string> //used for std::string and std::stoi()
#include <vector> //used for making vectors
#include <cctype> //used for std::tolower
#include <map> //used for std::map
#include <cmath> //used for pow()
#include <algorithm> //used for reverse()

unsigned long long toDecimal(int base, std::string number) {
    //Creating a map to get the integer equivalent of the character digit for computation
    std::map<char, int> digitEquiv;
    digitEquiv['0'] = 0;
    digitEquiv['1'] = 1;
    digitEquiv['2'] = 2;
    digitEquiv['3'] = 3;
    digitEquiv['4'] = 4;
    digitEquiv['5'] = 5;
    digitEquiv['6'] = 6;
    digitEquiv['7'] = 7;
    digitEquiv['8'] = 8;
    digitEquiv['9'] = 9;
    digitEquiv['a'] = 10;
    digitEquiv['b'] = 11;
    digitEquiv['c'] = 12;
    digitEquiv['d'] = 13;
    digitEquiv['e'] = 14;
    digitEquiv['f'] = 15;
    unsigned long long decOut = 0;
    int perDigit = 0;
    int counter = 0;
    //Performing the multiplication method of converting other base systems to decimal
    for (int i = number.size() - 1; i >= 0; --i) {
        perDigit = pow(base, counter) * digitEquiv[number[i]];
        decOut += perDigit;
        counter++;
    }
    //Returns a decimal integer
    return decOut;
}

std::string lowerCase(const std::string& input) {
    //Makes the input all lowercase to simplify the checking validNum checking process
    std::string lower = "";
    for (int i = 0; i < input.size(); ++i) {
        lower += std::tolower(input[i]);
    }
    //Returns the inputted number with all letters lowercase
    return lower;
}

int validBase() { //Asks for user input and checks if the input is an integer and is in the range 2 to 16
    int input;
    std::cout << "Please input a base system from 2 to 16" << std::endl;
    std::cin >> input;
    //If the inputted value is not an integer, the program does not immediately crash
    //Instead it clears the error, clears the buffer and asks the user to input a correct base system
    if (std::cin.fail() || 2 > input || input > 16) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "That is not a recognized base system" << std::endl;
        return validBase();
    }
    //Returns a valid base within the range 2 to 16
    return input;
}

std::string validNum(int base) { //Checks if the digit is valid by checking against the set of accepted characters
    std::string validDigits = "0123456789abcdef"; //Defines the set of digits that are accepted
    //Creates a smaller string from 0 up to the element located at validDigits[base]
    std::string subString = validDigits.substr(0, base);
    std::string input;
    //std::cout << "Please input a number in the same base system previously entered" << std::endl;
    std::cin >> input;
    //Calls a function to convert all letters to lower case to prevent having to do 2 checks for uppercase and lowercase
    std::string lowered = lowerCase(input);
    //Recursion to continue asking the user for a correct input
    for (int i = 0; i < lowered.size(); ++i) {
        bool isIn = subString.find(lowered[i]) != std::string::npos;
        if (!isIn) {
            std::cout << "This is not a valid number, please input another within the entered base system." << std::endl;
            return validNum(base);
        }
    }
    //Returns a valid number with only the valid digits in the base system
    return input;
}

//Function responsible for converting input decimal into other base systems
std::vector <char> toRadix(unsigned long long decimal,int base) {
    std::map<int, char> digitEquiv;
    digitEquiv[0] = '0';
    digitEquiv[1] = '1';
    digitEquiv[2] = '2';
    digitEquiv[3] = '3';
    digitEquiv[4] = '4';
    digitEquiv[5] = '5';
    digitEquiv[6] = '6';
    digitEquiv[7] = '7';
    digitEquiv[8] = '8';
    digitEquiv[9] = '9';
    digitEquiv[10] = 'a';
    digitEquiv[11] = 'b';
    digitEquiv[12] = 'c';
    digitEquiv[13] = 'd';
    digitEquiv[14] = 'e';
    digitEquiv[15] = 'f';
    std::vector <char> radix;
    unsigned long long temp = decimal;
    //If else added for if the user types 0 as the number to handle this edge case
    if (decimal != 0) {
            while (temp > 0) { //Algorithm for getting and storing the digits of the converted number
                radix.push_back(digitEquiv[temp % base]);
                temp /= base;
            }
    }
    else {
         radix.push_back('0');
        }
    return radix;
}
char validOperator(){
    char op;
    std::cout << "Please choose an operator to be used (+, -, *, /)" << std::endl;
    std::string validOperators = "+-*/";
    std::cin >> op;
    bool isIn = validOperators.find(op) != std::string::npos;
    if (!isIn) {
        std::cout << "This is not a valid number" << std::endl;
        return validOperator();
    }
    return op;
}

int main()
{
    int baseInput = 0;    
    std::string operand1 = "";    
    std::string operand2 = "";
    bool isInt = false, running = true;
    unsigned long long decHolder1 = 0;
    unsigned long long decHolder2= 0;
    unsigned long long decResult = 0;
    char op;
    std::string stop = " ";

    std::cout << "This is a simple arithmetic calculator. It will handle any radix from 2-16.\nBut it is locked to the unsigned long long size limit, meaning large results will cause it to overflow and produce incorrect results.\nThe program is unable to handle negative results for now.\n" << std::endl;
    while (running) {
        std::vector <char> radResult;
        baseInput = validBase();
        std::cout << "Please input the first operand in the same base system previously entered" << std::endl;
        operand1 = validNum(baseInput);
        std::cout << "Please input the second operand in the same base system previously entered" << std::endl;
        operand2 = validNum(baseInput);
        op = validOperator();
        
        //Still don't know how to properly process multiple inputs in the terminal without validity checks being skipped
        decHolder1 = toDecimal(baseInput, operand1);
        decHolder2 = toDecimal(baseInput, operand2);
        if (baseInput != 10) { //Makes the program skip the step of converting the number to decimal if it is already base 10
            switch (op) {
            case '+':
                decResult = decHolder1 + decHolder2;
                break;
            case '-':
                decResult = decHolder1 - decHolder2;
                break;
            case '*':
                decResult = decHolder1 * decHolder2;
                break;
            case '/':
                decResult = decHolder1 / decHolder2;
                break;
            }
            radResult = toRadix(decResult, baseInput);
            for (int x = radResult.size() - 1; x >= 0; --x) { //Prints out the values in the vector in reverse
                std::cout << radResult[x];
            }
            std::cout << std::endl;
        }
        else {
            switch (op) {
            case '+':
                decResult = decHolder1 + decHolder2;
                break;
            case '-':
                decResult = decHolder1 - decHolder2;
                break;
            case '*':
                decResult = decHolder1 * decHolder2;
                break;
            case '/':
                decResult = decHolder1 / decHolder2;
                break;
            }
            std::cout << decResult << std::endl;
        }
        std::cout << "Enter \"STOP\" to terminate the program, if you wish to continue enter anything else."
            << std::endl;
        std::cin >> stop;
        //For stopping the program
        if (stop == "STOP") {
            running = false;
        }
    }
    std::cout << "Program terminated by user.";
    return 0;
}
//ask for input: base,operand 1, operand 2, operator
//check each time if inputs are valid, ask again for a proper input if wrong

/*1. The "calculator" would accept two operands from the user as well as one operator and one integer (0-16).
2. The integer would indicate the base of the operands accepted.
3. The calculator would identify which among the four operators (+, -, *, /) did the user input and apply the corresponding operations to the operands.
4. The calculator should also be able to show an error message "Unidentified Operation" to the user if they placed an operator that is not among the five operators.*/