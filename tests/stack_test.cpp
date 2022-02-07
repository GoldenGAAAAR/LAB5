// Copyright 2021 Your Name <your_email>

#include <gtest/gtest.h>
#include <stack.hpp>
#include <StackArgs.hpp>
#include <stdexcept>
#include <memory>
#include <type_traits>


TEST(Stack, TestOne) {
  Stack<int> stack;
  EXPECT_THROW(stack.pop(), std::exception);
  EXPECT_THROW(stack.head(), std::exception);
  int a = 10;
  int b = 20;
  stack.push(a);
  stack.push(b);
  EXPECT_EQ(20, stack.head());
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  stack.pop();
  EXPECT_EQ(10, stack.head());
  stack.pop();
  EXPECT_THROW(stack.head(), std::exception);

  Stack<std::string> stack_str;
  std::string str_a = "ababababab";
  std::string str_b = "fjslfhsl";
  std::string str_c = "";
  stack_str.push(std::move(str_a));
  stack_str.push(std::move(str_c));
  stack_str.push(std::move(str_b));

  EXPECT_EQ("fjslfhsl", stack_str.head());
  EXPECT_NE("fjslfhsl", str_b);
  EXPECT_EQ("", str_a);

  EXPECT_TRUE(std::is_move_constructible<Stack<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<std::string>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<std::string>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<std::string>>::value);
}

TEST(StackNoCopy, TestTwo) {
  {
    StackArgs<int> stack_n;
    EXPECT_THROW(stack_n.pop(), std::exception);
    EXPECT_THROW(stack_n.head(), std::exception);
    stack_n.push(10);
    EXPECT_EQ(stack_n.pop(), 10);
    EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
    EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
    EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
    EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  }
  StackArgs<std::unique_ptr<int>> test;
  int *i = new int(10);
  std::unique_ptr<int> uptr_1(i);
  test.push(std::move(uptr_1));
  EXPECT_EQ(uptr_1.get(), nullptr);
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

TEST(StackNoCopy, PushEmplace) {
  //  StackArgs<int> stackArgs;
  //  stackArgs.push_emplace(10);
  //  EXPECT_EQ(stackArgs.head(), 10);

  StackArgs<std::pair<int, int>> stackArgs;
  stackArgs.push_emplace(10, 20);
  EXPECT_EQ(stackArgs.head(), std::pair(10, 20));
}