#include <iostream>
#include <string>
#include <set>

bool validOperator(std::string _operator) { //Checking if operator is supported
    std::set<std::string> validOp {
        "&","|","^","<<",">>"
    };
    if (validOp.find(_operator) != validOp.end()) {
        return true;
    }
    return false;
}

int main()
{
    
    std::cout << "This is a bitwise calculator using 64 bit unsigned long long containers.\n" 
              << "It only supports decimal input and the ff. operators (&, |, ^, <<, >>):\n\n";
    while (true){
        std::string op = "";
        unsigned long long operand1 = 0, operand2 = 0, result = 0;

        std::cout 
            << "Please input a bitwise operation in the format: operand_1 bitwise_operator operand_2\nExample: 1234 << 3" 
            << std::endl;

        if (!(std::cin >> operand1)) {//input error checking
            std::cout << "Incorrect operand input\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin >> op;
        if (!(std::cin >> operand2)) {
            std::cout << "Incorrect operand input\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        //I don't know how to deal with multiple inputs in a loop properly yet so here is a janky implementation of input checking that just restarts the loop if an incorrect operand is given
        
        if (!validOperator(op)){ //necessary for checking if string input is a valid operator since switch case is used after
            std::cout << "Unidentified Operation\n" << std::endl;
            continue;
        }
        else {//logic for choosing correct operation
            switch (op[0]) {//converting string to char is necessary to use switch case
            case '&':
                result = operand1 & operand2;
                break;
            case '|':
                result = operand1 | operand2;
                break;
            case '^':
                result = operand1 ^ operand2;
                break;
            case '<':
                result = operand1 << operand2;
                break;
            case '>':
                result = operand1 >> operand2;
                break;
            }
            std::cout << "Result: " << result << '\n' << std::endl;
        }
    }
    return 0;
 }

/*
1. The "calculator" would accept two operands(decimal numbers) from the user as well as one operator.
2. The calculator would identify which among the five operators (&, |, ^, <<, >>) did the user input and apply the 
   corresponding operations to the operands.
3. The calculator should also be able to show an error message "Unidentified Operation" to the user if they placed 
   an operator that is not among the five operators.
*/