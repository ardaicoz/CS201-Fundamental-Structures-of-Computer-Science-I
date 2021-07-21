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

    for (int i = 0; i <= exp.length(); i++) {
        //if this char is an operand
        if ( isExistsDigit(exp[i]) ) {
            aStack.push(exp[i]);
        }
        else {
            char operand2 = aStack.getTop();
            aStack.pop();
            char operand1 = aStack.getTop();
            aStack.pop();

            double result;
            if (exp[i] == '*')
                result = (operand1 -'0') * (operand2 -'0');
            else if (exp[i] == '/')
                result = (operand1 -'0') / (operand2 -'0');
            else if (exp[i] == '+')
                result = (operand1 -'0') + (operand2 -'0');
            if (exp[i] == '-')
                result = (operand1 -'0') - (operand2 -'0');
            
            cout << "result: " << result << endl;
            //convert the result to char and push
            aStack.push( static_cast<char>(result) );
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