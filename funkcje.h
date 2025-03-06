// Funkcje.h
#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "Stack.h"
#include "Queue.h"
#include <cstdio>
class ExpressionConverter {
private:
    Stack numberStack;
    Stack operatorStack;
    Queue postfixQueue;
    static int getPrecedence(char op);
    static bool isOperator(unsigned char c);
public:
    void processExpression();
    void checkForMin();
    void convertToPostfix(char c);

};
#endif // FUNKCJE_H