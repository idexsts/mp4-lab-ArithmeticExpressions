#include <gtest.h>

#include"Lexer.h"
#include"string"

TEST(Lexer, throws_when_nulnumber_error)
{
	string s = "009-4"; 
	EXPECT_ANY_THROW(Lexer ax(s));
}
TEST(Lexer, throws_when_symbol_incorrect)
{
	string s = "arrY"; 
	EXPECT_ANY_THROW(Lexer ax(s));
}
TEST(Lexer, passes_when_no_errors) {
	string s = "5+5*4";
	EXPECT_NO_THROW(Lexer ax(s));
}
