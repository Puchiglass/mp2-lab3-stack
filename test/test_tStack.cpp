#include "gtest.h"
#include "TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> v(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> v(-2));
}

TEST(TStack, can_copy_other_stack_and_have_different_address)
{
  TStack<int> a(5);
  a.Push(3);
  a.Push(3);
  TStack<int> b(a);
  TStack<int>* c = &a;
  TStack<int>* d = &b;
  EXPECT_EQ(2, b.Size());
  EXPECT_NE(c, d);
}

TEST(TStack, can_get_size_of_stack)
{
  TStack<int> a(5);
  EXPECT_EQ(0, a.Size());
  a.Push(3);
  a.Push(3);
  EXPECT_EQ(2, a.Size());
}

TEST(TStack, can_check_is_empty_stack)
{
  TStack<int> a(5);
  EXPECT_EQ(true, a.isEmpty());
}

TEST(TStack, can_check_is_empty_stack_but_stack_isnt_empty)
{
  TStack<int> a(4);
  for (int i = 0; i < 3; i++)
    a.Push(i + 6);
  EXPECT_EQ(false, a.isEmpty());
  EXPECT_EQ(false, a.isFull());
}

TEST(TStack, can_check_is_full_stack)
{
  TStack<int> a(4);
  for (int i = 0; i < 4; i++)
    a.Push(i + 6);
  EXPECT_EQ(true, a.isFull());
}

TEST(TStack, can_push_element_in_stack)
{
  TStack<int> a(4);
  a.Push(2);
  EXPECT_EQ(2, a.Top());
  a.Push(6);
  EXPECT_EQ(6, a.Top());
  a.Pop();
  EXPECT_EQ(2, a.Top());
}

TEST(TStack, can_pop_element_in_stack)
{
  TStack<int> a(4);
  a.Push(2);
  a.Push(6);
  EXPECT_EQ(6, a.Pop());
  EXPECT_EQ(2, a.Top());
  EXPECT_EQ(2, a.Pop());
}

TEST(TStack, can_check_top_element_in_stack)
{
  TStack<int> a(4);
  a.Push(2);
  a.Push(6);
  EXPECT_EQ(6, a.Top());
  a.Push(17);
  EXPECT_EQ(17, a.Top());
  a.Pop();
  EXPECT_EQ(6, a.Top());
}