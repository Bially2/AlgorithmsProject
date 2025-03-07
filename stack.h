//
// Created by szyiw on 27.05.2024.
//

#ifndef AISDPROJ3_STACK_H
#define AISDPROJ3_STACK_H


class Stack {
private:
    struct Node {
        int value;
        Node *next;
    };
    Node *head;
    int length;

    static Node* createNode(int value);
public:
    Stack();
    ~Stack();
    void push(int value);
    int pop();
    int peek();
    [[nodiscard]] bool isEmpty() const;

    [[maybe_unused]] [[nodiscard]] int size() const;
    void clear();
};


#endif //AISDPROJ3_STACK_H