// Copyright 2021 Pavel Toshchakov

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_
#include <iostream>
#include <exception>
#include <utility>

template <typename T>
class Stack {
 public:
  struct Node{
    T data; // данные
    Node* next; // указатель на следующий элемент стека
  };

  Stack() : top(nullptr){};
  Stack(Stack &&stack):top(stack.top){stack.top = nullptr;}

  Stack& operator=(Stack&& stack){
    if (this == &stack){
      return *this;
    }
    top = stack.top;
    stack.top = nullptr;
    return *this;
  }

  Stack(const Stack& stack) = delete; //некопируемый
  Stack& operator=(const Stack& stack) = delete; //некопируемый

  ~Stack(){
    while (top != nullptr){
      Node *tmp = top;
      top = top->next;
      delete tmp;
    }
  }

  void push(T&& value){
    Node* new_node = new Node{std::forward<T>(value), top};
    top = new_node;
  }

  void push(const  T& value){
    Node* new_node = new Node{value, top};
    top = new_node;
  }

  void pop(){
    if (!top){
      throw std::exception();
    } else {
      Node* tmp = top;
      top = top->next;
      delete tmp;
    }
  }

  const T& head() const{
    if (!top){
      throw std::exception();
    }
    return top->data;
  }

 private:
  Node* top; //вершина стека
};


#endif // INCLUDE_EXAMPLE_HPP_
