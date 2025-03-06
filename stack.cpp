#include "Stack.h"
#include <cstdio>
Stack::Stack() : top(nullptr) {}
void Stack::push(char value) {
    auto* newNode = new StackNode;
    newNode->charValue = value;
    newNode->isChar = true;
    newNode->next = top;
    top = newNode;
}
void Stack::display() const {
    StackNode* current = top;
    while (current != nullptr) {
        if (current->isChar) {
            printf("%c ", current->charValue);
        } else {
            printf("%d ", current->intValue);
        }
        current = current->next;
    }
    printf("\n");
}
void Stack::push(int value) {
    auto* newNode = new StackNode;
    newNode->intValue = value;
    newNode->isChar = false;
    newNode->next = top;
    top = newNode;
}
bool Stack::isEmpty() const {
    return top == nullptr;
}
char Stack::pop() {
    if (top == nullptr) {
        return '\0';
    }
    char value;
    if (top->isChar) {
        value = top->charValue;
    } else {
        return '\0';
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
    return value;
}
int Stack::popInt() {
    if (top == nullptr || top->isChar) {
        return 0;
    }
    int value = top->intValue;
    StackNode* temp = top;
    top = top->next;
    delete temp;
    return value;
}
Stack::~Stack() {
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}