#include <iostream>
#include <string> //used for std::string and std::stoi()
#include <cctype> //used for std::isdigit()
#include <vector> //used for making vectors

//Function for checking each character in the input is a digit to only accept whole numbers
//Iterates over the characters in the string to check if each one is a digit
//Negative numbers, scientific notations will be rejected
bool inputCheck(std::string input) {
    bool inputType = false;
    for (int i = 0; i < input.size(); ++i) {
        inputType = std::isdigit(input[i]);
        if (inputType == 0) {
            return false;
        }
        else {
            return true;
        }
    }
}
//function responsible for converting input decimal into binary string
std::vector <int> binaryStr (int x) {
    std::vector <int> binaryRev;
    if (x == 0) {
        binaryRev.push_back(0);
        return binaryRev;
        //fixed the problem where vector returns empty if 0 and displays nothing when printed
    }
    else {
        while (x != 0) {
            binaryRev.push_back(x % 2);
            x /= 2;
        }
    }
    return binaryRev;
}

int main()
{
    std::string decimalIn = " ";
    //user input is taken as a string to prevent program from stopping unless "STOP" is inputted
    bool isInt = false;
    std::cout
        << "This is a decimal to binary converter." << "\n\n"
        << "You may input STOP to terminate the program" << "\n\n"
        << "Please input a whole number." << '\n' << std::endl;
    //continuously takes input from the user after every loop
    while (std::cin >> decimalIn) {
        if (decimalIn != "STOP"){
            if (inputCheck(decimalIn) == true) {
                int decHolder = std::stoi(decimalIn); //for converting the string into an integer value; decimals are truncated here
                std::vector <int> reversed = binaryStr(decHolder);
                std::cout << decimalIn << " in binary is: ";
                for (int i = 1; i <= reversed.size(); ++i) {
                    std::cout << reversed[reversed.size()-i];
                    //prints the binary string in the correct order
                }
                std::cout << "\n\n" << "Please input a whole number." << '\n' << std::endl;
                
            }
            else {
                std::cout << "This is not a whole number. Please try again." << std::endl;
            }
        }
        else {
            std::cout << '\n' << "Program terminated by user." << std::endl;
            break;
            //terminates the program when "STOP" is inputted
        }
        
    }
}

/*
Instructions: Create a program that converts decimal numbers to binary numbers.Document your output.

The program should have the following features :

The program asks for a user input of decimal numbers.
The program will keep on asking for a new input every after a successful conversion.
The program will only terminate one the user inputs "STOP".
*/
//Psuedocode before starting
//-prompt user to input decimal integers
//-put user input into an int variable
//-make a for loop dividing the variable by 2 until it is equal to 1
//-get remainder using modulo and store in a vector
//-for loop for printing vector elements from [vec.size()-1] to [0]
