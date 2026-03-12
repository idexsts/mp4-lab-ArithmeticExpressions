#include <gtest.h>
#include"TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int>s(5));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int>s(MAX_STACK_SIZE + 1));
}
TEST(TStack, cant_create_stack_with_length_less_then_zero)
{
	ASSERT_ANY_THROW(TStack<int>s(-100));
}
TEST(TStack, can_copy_stack)
{
	TStack<int> st(10);
	ASSERT_NO_THROW(TStack<int> s1(st));
}
TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> st(2);
	st.push(3);
	st.push(4);
	TStack<int> st2(st);
	EXPECT_EQ(st.pop(), st2.pop());
	EXPECT_EQ(st.pop(), st2.pop());
}
TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> st(2);
	st.push(3);	
	st.push(4);	
	TStack<int> st2(st);
	st.pop();
	st.pop();
	st.push(0);
	st.push(0);
	EXPECT_NE(st.pop(), st2.pop());
	EXPECT_NE(st.pop(), st2.pop());
}

TEST(TStack, cant_push_when_full)
{
	TStack<int> s(2);
	s.push(3);
	s.push(4);
	ASSERT_ANY_THROW(s.push(0));
}
TEST(TStack, cant_pop_when_empty)
{
	TStack<int> s(2);
	ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, cant_top_when_empty)
{
	TStack<int> s(2);
	ASSERT_ANY_THROW(s.top());
}

