#ifndef STACK_H
#define STACK_H

struct StackNode {
    union {
        char charValue;
        int intValue;
    };
    bool isChar;
    StackNode* next;
};
class Stack {
public:
    StackNode* top;
    Stack();
    void push(char value);
    void push(int value);
    char pop();
    [[nodiscard]] bool isEmpty() const;
    int popInt();
    void display() const;
    ~Stack();
};
#endif // STACK_H