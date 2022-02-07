//Copyright 2021 Pavel Toshchakov

#ifndef INCLUDE_STACKARGS_HPP_
#define INCLUDE_STACKARGS_HPP_

#include <iostream>
#include <exception>

template <typename T>
class StackArgs
{
 public:
  struct Node{
    T data;
    Node* next;
  };

  StackArgs() : top(nullptr){}
  StackArgs(StackArgs&& stack) : top(stack.top) { stack.top = nullptr;}

  ~StackArgs(){
    while (top != nullptr) {
      Node* tmp = top;
      top = top->next;
      delete tmp;
    }
  }
  StackArgs& operator=(StackArgs&& stack) {
    if (this == &stack) {
      return *this;
    }
    top = stack.top;
    stack.top = nullptr;
    return *this;
  }

  StackArgs(const StackArgs& stack) = delete;
  StackArgs& operator=(const StackArgs& stack) = delete;

  template <typename ... Args>

  void push_emplace(Args&&... arg){
    Node* tmp = top;
    top = new Node{{std::forward<Args>(arg)...}, tmp};
  }

  void push(T&& value){
    Node* new_node = new Node{std::forward<T>(value), top};
    top = new_node;
  }

  const T& head() const {
    if (!top){
      throw std::exception();
    }
    return top->data;
  }

  T pop() {
    if (!top) {
      throw std::exception();
    } else {
      T data = top->data;
      Node* temp = top;
      top = top->next;
      delete temp;
      return data;
    }
  }

  private:
  Node* top;
};


#endif  // TEMPLATE_STACKARGS_HPP
