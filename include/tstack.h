// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
const int size = 100;
template<typename T, int size>
class TStack {
 private:
     T arr[size];
     int top = -1;

 public:
     TStack():top(-1) {}
     bool isEmpty() {
       return top == -1;
     }
     bool isFull() {
       return top == size - 1;
     }
     void push(T value) {
         if (!isFull()) 
             arr[++top] = value;
         else
             throw "Full!";
     }
     T get() {
         if (!isEmpty())
             return arr[top];
         else
             throw "Empty!";
     }
     void pop() {
         if (!isEmpty())
             --top;
         else
             throw "Empty!";
     }
     int getSize() {
         return top + 1;
     }
};
#endif  // INCLUDE_TSTACK_H_
