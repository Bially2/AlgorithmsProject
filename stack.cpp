#include "Stack.h"
Stack::Stack() {
    head = nullptr;
    length = 0;
}
Stack::~Stack() {
    clear();
}
Stack::Node* Stack::createNode(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}
void Stack::push(int value) {
    Node *newNode = createNode(value);
    newNode->next = head;
    head = newNode;
    length++;
}
int Stack::pop() {
    if (isEmpty()) {
        return -1;
    }
    Node *temp = head;
    head = head->next;
    int value = temp->value;
    delete temp;
    length--;
    return value;
}
int Stack::peek() {
    if (isEmpty()) {
        return -1;
    }
    return head->value;
}
bool Stack::isEmpty() const {
    return length == 0;
}
[[maybe_unused]] int Stack::size() const {
    return length;
}
void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}
