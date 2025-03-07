#ifndef QUEUE_H
#define QUEUE_H
class Queue {
private:
    int* data;
    int front;
    int rear;
    int capacity;
    int count;

public:
    explicit Queue(int size);
    ~Queue();

    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
    void clear();
};

#endif // QUEUE_H