#include <gtest.h>

#include"Syntaxer.h"
#include "Token.h"
#include <vector>
#include"string"


TEST(Syntaxer, throws_when_syntax_error)
{
	vector<Token> infix;
	infix.push_back(Token('-'));
	infix.push_back(Token(8));
	infix.push_back(Token(')'));

	EXPECT_ANY_THROW(Syntaxer s(infix));
}

TEST(Syntaxer, passes_when_no_errors) {
	vector<Token> infix;
	infix.push_back(Token('('));
	infix.push_back(Token('-'));
	infix.push_back(Token(8));
	infix.push_back(Token(')'));
	EXPECT_NO_THROW(Syntaxer s(infix));
}