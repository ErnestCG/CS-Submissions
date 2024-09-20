#include <iostream>
#include <string> //used for std::string and std::stoi()
#include <vector> //used for making vectors
#include <cctype> //used for std::tolower
#include <map> //used for std::map
#include <cmath> //used for pow()
#include <algorithm> //used for reverse()

int toDecimal(int base, std::string number) {
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
    int decOut = 0;
    int tempInt = 0;
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
    std::cout << "Please input a number in the same base system previously entered" << std::endl;
    std::cin >> input;
    //Calls a function to convert all letters to lower case to prevent having to do 2 checks for uppercase and lowercase
    std::string lowered = lowerCase(input);
    //Recursion to continue asking the user for a correct input
    for (int i = 0; i < lowered.size(); ++i) {
        bool isIn = subString.find(lowered[i]) != std::string::npos;
        if (!isIn) {
            std::cout << "This is not a valid number" << std::endl;
            return validNum(base);
        }
    }
    //Returns a valid number with only the valid digits in the base system
    return input;
}

//Function responsible for converting input decimal into other base systems
std::vector <char> toRadix(int decimal) {
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
    int temp = decimal;
    //If else added for if the user types 0 as the number to handle this edge case
    if (decimal != 0) {
        for (int i = 2; i <= 16; ++i) {
            int temp2 = temp;
            while (temp2 > 0) { //Algorithm for getting and storing the digits of the converted number
                radix.push_back(digitEquiv[temp2 % i]);
                temp2 /= i;
            }
            std::cout << "base" << i << '\t';
            for (int x = radix.size()-1; x >= 0; --x) { //Prints out the values in the vector in reverse
                std::cout << radix[x];
            }
            radix.clear();
            std::cout << std::endl;
            
        }
    }
    else {
        for (int i = 2; i <= 16; ++i) {
            radix.push_back('0');
            std::cout << "base" << i << '\t';
            for (int x = radix.size() - 1; x >= 0; --x) {
                std::cout << radix[x];
            }
            radix.clear();
            std::cout << std::endl;

        }
    }
    std::cout << std::endl;
    return radix;
}

int main()
{
    int baseInput = 0;
    std::string numInput = " ";
    bool isInt = false, running = true;
    int decHolder = 0;
    std::string stop = " ";
    std::cout << "This is a radix converter. If you enter a base system and a valid number, it will convert the number\n"
        << "into its equivalent in bases 2 to 16.\n" << std::endl;
    while (running) {
        baseInput = validBase();
        numInput = validNum(baseInput);
        std::cout << '\n';
        if (baseInput != 10) { //Makes the program skip the step of converting the number to decimal if it is already base 10
            int decHolder = toDecimal(baseInput,numInput);
            toRadix(decHolder);
        }
        else {
            toRadix(std::stoi(numInput));
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
    //bunch of iterations over string elements checking for character validity
