#include "Queue.h"
Queue::Queue(int size) {
    data = new int[size];
    front = 0;
    rear = -1;
    capacity = size;
    count = 0;
}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(int value) {
    if (count == capacity) {
        return;
    }
    rear = (rear + 1) % capacity;
    data[rear] = value;
    count++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    int value = data[front];
    front = (front + 1) % capacity;
    count--;
    return value;
}

bool Queue::isEmpty() const {
    return count == 0;
}

void Queue::clear() {
    delete[] data;
    front = 0;
    rear = -1;
    count = 0;
}