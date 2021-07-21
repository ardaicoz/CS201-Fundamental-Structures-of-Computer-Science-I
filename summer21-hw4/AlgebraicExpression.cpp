#include "AlgebraicExpression.h"
using namespace std;

string infix2postfix(const string exp ) {
    Stack aStack;
    string postFixExp = "";
    
    //for the every char in the "exp" string
    for (int i = 0; i <= exp.length(); i++) {
        //if the char is a digit
        if ( isExistsDigit( exp[i] ) ) {
            postFixExp += exp[i];
        }
        else if (exp[i] == '(') {
            //save '(' to stack
            aStack.push(exp[i]);
        }
        else if (exp[i] == ')') {
            //pop stack until matching '('
            while ( aStack.getTop() != '(') {
                postFixExp += aStack.getTop();
                aStack.pop();
            }
            aStack.pop(); //remove '('
        }
        //if char is a operator
        //precedence function used here
        else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-') {
            while ( !aStack.isEmpty() && aStack.getTop() != '(' && (precedence(exp[i]) <= precedence(aStack.getTop())) ) {
                postFixExp += aStack.getTop();
                aStack.pop();
            }
            aStack.push(exp[i]);
        }
    }

    while (!aStack.isEmpty()) {
        postFixExp += aStack.getTop();
        aStack.pop();
    }

    return postFixExp;
}

double evaluatePostfix(const string exp) {
    Stack aStack;
    const int ASCII = 48;

    for (int i = 0; i < exp.length(); i++) {
        //if this char is an operand
        if ( isExistsDigit(exp[i]) ) {
            aStack.push(exp[i] - ASCII);
        }
        else {
            double operand2 = aStack.getTop();
            cout << "operand2: " << operand2 << endl;
            aStack.pop();
            double operand1 = aStack.getTop();
            cout << "operand1: " << operand1 << endl;
            aStack.pop();

            double num = 0;
            if (exp[i] == '*') {
                num = operand1 * operand2;
            }
            else if (exp[i] == '/') {
                num = static_cast<double>(operand1) / operand2;
            }
            else if (exp[i] == '+')  {
                num = operand1 + operand2;
            }
            if (exp[i] == '-') {
                num = operand1 - operand2;
            }
            
            cout << "num: " << num << endl;
            aStack.push(num);
        }

        cout << "stack: ";
        aStack.display();
        cout << endl;
    }

    return aStack.getTop();
}

int precedence(const char ch) {
    if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else 
        return -1;

}

//does this char includes the following one of the numbers?
bool isExistsDigit(const char ch) {
    if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' )
        return true;
    else 
        return false;
}