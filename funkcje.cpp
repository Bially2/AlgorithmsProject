#include "Funkcje.h"
#include <cstdio>
#include <climits>
int ExpressionConverter::getPrecedence(char op) {
    switch (op) {
        case '(':
            return 0;
        case '+':
        case '-':
        case ')':
            return 1;
        case '*':
        case '/':
            return 2;
        case 'N':
        case 'F':
        case 'M':
        case 'X':
            return 3;
        default:
            return -1;
    }
}
bool ExpressionConverter::isOperator(unsigned char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == 'N' || c == 'F' || c == 'M' || c == 'X'){
        return true;
    }
    else
        return false;
}
void ExpressionConverter::checkForMin() {
    char token;
    while (std::scanf("%c", &token) != EOF && token != ' ') {
        if (token == 'I') {
            operatorStack.push('M');
            char nextToken;
            std::scanf("%c", &nextToken);
            if (nextToken == 'N') {
                break;
            }
        } else if (token == 'A') {
            operatorStack.push('X');
            char nextToken;
            std::scanf("%c", &nextToken);
            if (nextToken == 'X') {
                break;
            }
        } else {
            break;
        }
    }
}
void ExpressionConverter::convertToPostfix(char c) {
    if (c>='0'&&c<='9') {
        if (!postfixQueue.isEmpty() && !isOperator(postfixQueue.front->data_char) && postfixQueue.front->data_char != '(') {
            postfixQueue.enqueue(' ');
        }
        postfixQueue.enqueue(c);
        return;
    }
    if (c == '(') {
        operatorStack.push(c);
        return;
    }
    if (c == ')') {
        int count = 0;
        while (!operatorStack.isEmpty() && operatorStack.top->charValue != '(') {
            char items = operatorStack.pop();
            if (items == ',') {
                ++count;
                continue;
            }
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(items);
        }
        if (operatorStack.top->charValue == '(') {
            operatorStack.pop();
        }
        if (!operatorStack.isEmpty() && (operatorStack.top->charValue == 'N' || operatorStack.top->charValue == 'F')) {
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(operatorStack.pop());
            return;
        }
        if (!operatorStack.isEmpty() && operatorStack.top->charValue == 'M') {
            int number = count + 1 ;
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(operatorStack.pop());
            postfixQueue.enqueue(number);
            return;
        }
        if (!operatorStack.isEmpty() && operatorStack.top->charValue == 'X') {
            int number = count + 1 ;
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(operatorStack.pop());
            postfixQueue.enqueue(number);
            return;
        }
        return;
    }
    if (c == ',') {
        while (!operatorStack.isEmpty() && operatorStack.top->charValue != '(' && operatorStack.top->charValue != ',') {
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(operatorStack.pop());
        }
        operatorStack.push(c);
        return;
    }
    if (c == 'N' || c == 'F') {
        operatorStack.push(c);
        return;
    }
    if (c == 'M') {
        checkForMin();
        return;
    }
    if (isOperator(c)) {
        if (!postfixQueue.isEmpty() && !isOperator(postfixQueue.front->data_char) && postfixQueue.front->data_char != '(') {
            postfixQueue.enqueue(' ');
        }
        while (!operatorStack.isEmpty() && getPrecedence(c) <= getPrecedence(operatorStack.top->charValue)) {
            postfixQueue.enqueue(' ');
            postfixQueue.enqueue(operatorStack.pop());
        }
        operatorStack.push(c);
        return;
    }
}
void ExpressionConverter::processExpression() {
    char token;
    bool lastWasDigit = true;
    bool wasError = false;
    while (std::scanf("%c", &token) != EOF && token != '.') {
        if (token >= '0' && token <= '9') {
            if (!lastWasDigit) {
                postfixQueue.enqueue(' ');
            }
            lastWasDigit = true;
            postfixQueue.enqueue(token);
        } else if (token != ' ') {
            convertToPostfix(token);
            lastWasDigit = false;
        }
    }
    while (!operatorStack.isEmpty()) {
        postfixQueue.enqueue(' ');
        postfixQueue.enqueue(operatorStack.pop());
    }
    postfixQueue.display();
    while (!postfixQueue.isEmpty()) {
        unsigned char item = postfixQueue.dequeue();
        if (item != ' ') {
            int number = 0;
            while (item >= '0' && item <= '9') {
                number = number * 10 + (item - '0');
                if (!postfixQueue.isEmpty()) {
                    item = postfixQueue.dequeue();
                } else {
                    break;
                }
            }
            if (!isOperator(item)) {
                numberStack.push(number);
            }
        }
        else {
            continue;
        }
        if (isOperator(item)) {
            if (item != 'N' && item != 'F' && item != 'M' && item != 'X') {
                int operand1 = numberStack.popInt();
                int operand2 = numberStack.popInt();
                int result = 0;
                switch (item) {
                    case '+':
                        printf("%c %d %d ", item, operand1, operand2);
                        numberStack.display();
                        result = operand2 + operand1;
                        break;
                    case '-':
                        printf("%c %d %d ", item, operand1, operand2);
                        numberStack.display();
                        result = operand2 - operand1;
                        break;
                    case '*':
                        printf("%c %d %d ", item, operand1, operand2);
                        numberStack.display();
                        result = operand2 * operand1;
                        break;
                    case '/':
                        printf("%c %d %d ", item, operand1, operand2);
                        numberStack.display();
                        if (operand1 == 0) {
                            printf("ERROR\n");
                            wasError = true;
                            while (!postfixQueue.isEmpty()) {
                                postfixQueue.dequeue();
                            }
                            while (!numberStack.isEmpty()) {
                                numberStack.popInt();
                            }
                        } else {
                            result = operand2 / operand1;
                        }
                        break;
                    default:
                        break;
                }
                if (!wasError) {
                    numberStack.push(result);
                } else {
                    break;
                }
            }
        }
        if (item == 'N') {
            int operandNegation = numberStack.popInt();
            printf("%c %d ", item, operandNegation);
            numberStack.display();
            int result = operandNegation * (-1);
            numberStack.push(result);
        }
        if (item == 'F') {
            int op3 = numberStack.popInt();
            int op2 = numberStack.popInt();
            int op1 = numberStack.popInt();
            printf("IF %d %d %d ", op3, op2, op1);
            numberStack.display();
            int result;
            if (op1 > 0) {
                result = op2;
            } else {
                result = op3;
            }
            numberStack.push(result);
        }
        if (item == 'M') {
            int count = postfixQueue.dequeue();
            int minNumber = INT_MAX;
            printf("MIN%d ", count);
            for (int i = 0; i < count; ++i) {
                if (!numberStack.isEmpty()) {
                    int currentNumber = numberStack.popInt();
                    printf("%d ", currentNumber);
                    if (currentNumber < minNumber) {
                        minNumber = currentNumber;
                    }
                }
            }
            numberStack.display();
            numberStack.push(minNumber);
        }
        if (item == 'X') {
            int count = postfixQueue.dequeue();
            int maxNumber = INT_MIN;
            printf("MAX%d ", count);
            for (int i = 0; i < count; ++i) {
                if (!numberStack.isEmpty()) {
                    int currentNumber = numberStack.popInt();
                    printf("%d ", currentNumber);
                    if (currentNumber > maxNumber) {
                        maxNumber = currentNumber;
                    }
                }
            }
            numberStack.display();
            numberStack.push(maxNumber);
        }
    }
    if (!wasError && !numberStack.isEmpty()) {
        int finalResult = numberStack.popInt();
        printf("%d\n", finalResult);
    }
}