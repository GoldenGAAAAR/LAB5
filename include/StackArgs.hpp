//
// Created by Pavel Toshchakov on 07.02.2022.
//

#ifndef TEMPLATE_STACKARGS_HPP
#define TEMPLATE_STACKARGS_HPP
#include <iostream>

template <typename T>
class StackArgs
{
 public:
  struct Node{
    T data;
    Node* next;
  };

  StackArgs() : top(nullptr){};
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
    Node* new_node = new Node{std::move<T>(value), top};
    top = new_node;
  }

  const T& head() const {
    if (!top){
      throw std::out_of_range("Stack is empty");
    }
    return top->data;
  }

  T pop() {
    if (!top) {
      throw std::out_of_range("Stack is empty");
    } else {
      T data = top->data;
      Node* temp = top;
      top = top->Next;
      delete temp;
      return data;
    }
  }

  private:
  Node* top;
};


#endif  // TEMPLATE_STACKARGS_HPP
