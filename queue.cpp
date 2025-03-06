#include "Queue.h"
#include <cstdio>
Queue::Queue() : front(nullptr), rear(nullptr) {}
unsigned char Queue::enqueue(char data) {
    auto* newNode = new QueueNode(data);
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    return 0;
}
unsigned char Queue::enqueue(int data) {
    auto* newNode = new QueueNode(data);
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    return 0;
}
unsigned char Queue::dequeue() {
    if (isEmpty()) {
        return '\0';
    }
    unsigned char char_data = front->data_char;
    int int_data = front->data_int;
    QueueNode* temp = front;
    front = front->next;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
    return char_data ? char_data : int_data;
}
bool Queue::isEmpty() const {
    return front == nullptr;
}
void Queue::display() const {
    QueueNode* current = front;
    while (current != nullptr) {
        if (current->data_char == 'F') {
            printf("IF");
        } else if (current->data_char == 'M') {
            printf("MIN");
        } else if (current->data_char == 'X') {
            printf("MAX");
        } else {
            if (current->data_char != 0) {
                printf("%c", current->data_char);
            } else {
                printf("%d", current->data_int);
            }
        }
        current = current->next;
    }
    printf("\n");
}
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}