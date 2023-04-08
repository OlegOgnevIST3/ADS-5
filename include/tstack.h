// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
  // добавьте код стека
 private:
    T arr[100];
    int top;
 public:
    Tstack() :top(-1) {}
    void push(T val) {
      if (isFull()) {
        throw std::string("Stack is full");
      } else {
        arr[++top] = val;
      }
    }
      const T& pop() {
      if (isEmpty()) {
        throw std::string("Stack is empty");
      } else {
        return arr[top--];
      }
    }
    bool isEmpty()const {
      return top == -1;
    }

    bool isFull()const {
      return top == size - 1;
    }
    const T& get()const {
      return arr[top];
    }
};

#endif  // INCLUDE_TSTACK_H_
