// stack_queue.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <exception>


template<typename T>
class Item {
    template <typename> friend class Stack;
    template <typename> friend class Queue;
private:
    T data;
    Item<T>* next;
    Item<T>* prev;
public:
    Item() : data(T()), next(nullptr), prev(nullptr) {}
    Item(T _data): data(_data), next(nullptr), prev(nullptr) {}
    Item(T _data, Item<T>* _next) :data(_data), next(_next), prev(nullptr) {}
    Item(T _data, Item<T>* _next, Item<T>* _prev) 
        :data(_data), next(_next), prev(_prev) {}
};

template<typename T> class Stack {
private:
    Item<T>* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { while (!empty()) pop(); }
    bool empty() { return top == nullptr; }
    T pop() {
        if (empty()) throw std::exception();
        T data = top->data;
        Item<T>* old = top;
        top = top->next;
        delete old;
        return data;
    }
    void push(T data) {
        top = new Item<T>(data, top);
    }
};

template<typename T> class Queue {
private:
    Item<T>* top;
    Item<T>* bottom;
public:
    Queue() :top(nullptr), bottom(nullptr) {}
    ~Queue() { while (!empty()) pop(); }

    bool empty() {
        return top == nullptr;
    }

    void push(T data) {
        if (empty()) {
            bottom = new Item<T>(data, bottom);
            top = bottom;
        }
        else {
            bottom->prev = new Item<T>(data, bottom);
            bottom = bottom->prev;
        }
    }

    T pop() {
        T data = top->data;
        Item<T>* old = top;
        top = top->prev;
        delete old;
        if (empty()) {
            bottom = nullptr;
        }
        return data;
    }
};


int main()
{
    Stack<double> stack;
    stack.push(3);
    stack.push(3.1);
    stack.push(3.14);
    stack.push(3.141);
    stack.push(3.1415);
    stack.push(3.14159);
    stack.push(3.141592);
    while (!stack.empty()) {
        std::cout << stack.pop() << std::endl;
    }

    Queue<double> queue;
    queue.push(3);
    queue.push(3.1);
    queue.push(3.14);
    queue.push(3.141);
    queue.push(3.1415);
    queue.push(3.14159);
    queue.push(3.141592);
    while (!queue.empty()) {
        std::cout << queue.pop() << std::endl;
    }
    return 0;
}

