#include <gtest.h>

#include"Calc.h"
#include"string"

TEST(Calc, throws_when_lex_error)
{
	string s = "abc"; Calc ax(s);
	EXPECT_ANY_THROW(ax.Calculate());
}
TEST(Calc, throws_when_synt_error)
{
	string s = ")6--)"; Calc ax(s);
	EXPECT_ANY_THROW(ax.Calculate());
}
TEST(Calc, counts_the_answer) {
	string s= "5+5*4";
	Calc ax(s);
	EXPECT_EQ(ax.Calculate(), 25);
}

