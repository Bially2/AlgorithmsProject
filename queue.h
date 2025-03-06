#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
    char data_char;
    int data_int;
    QueueNode* next;
    explicit QueueNode(char data) : data_char(data), data_int(0), next(nullptr) {}
    explicit QueueNode(int data) : data_char(0), data_int(data), next(nullptr) {}
};

class Queue {
public:
    QueueNode* front;
    QueueNode* rear;
    Queue();
    ~Queue();
    unsigned char enqueue(char data);
    unsigned char enqueue(int data);
    unsigned char dequeue();
    [[nodiscard]] bool isEmpty() const;
    void display() const;
};

#endif // QUEUE_H