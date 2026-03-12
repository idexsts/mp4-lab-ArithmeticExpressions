#include "Calc.h"
using namespace std;

void Calc::doPostfix() {
		TStack<Token> st(infix.size());
		postfix.clear();

		for (size_t i = 0; i < infix.size(); i++) {
			if (infix[i].isTokenNum()) {
				postfix.push_back(infix[i]);
			}
			else if (infix[i].getVal() == 4) { // '('
				st.push(infix[i]);
			}
			else if (infix[i].getVal() == 5) { // ')'
				while (!st.isEmpty() && st.top().getVal() != 4) {
					postfix.push_back(st.pop());
				}
				if (!st.isEmpty()) {
					st.pop(); // удаляем '('
				}
			}
			else { // оператор
				//проверка, что стек не пуст!
				while (!st.isEmpty() &&
					st.top().getVal() != 4 &&
					infix[i].givePriority() <= st.top().givePriority()) {
					postfix.push_back(st.pop());
				}
				st.push(infix[i]);
			}
		}

		// Выталкиваем оставшиеся операторы
		while (!st.isEmpty()) {
			postfix.push_back(st.pop());
		}
	
}

int Calc::Calculate() {
	
	try
	{
		Lexer l(str);
		Syntaxer s(l.getTokens());
		infix = s.getTokens();
		doPostfix();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	

	vector<Token>_postfix(postfix);
	TStack<int> stack(_postfix.size());

		//стандартный постфиксный счет
		for (int i = 0; i < _postfix.size(); i++) {
			if (_postfix[i].isTokenNum()) {
				stack.push(_postfix[i].getVal());
			}
			else {
				int a = stack.pop();
				int b = stack.pop();
				int c;
				if (_postfix[i].getVal() == 0) {
					c = b + a;
				}
				else if (_postfix[i].getVal() == 1) {
					c = b - a;
				}
				else if (_postfix[i].getVal() == 2) {
					c = b * a;
				}
				else if (_postfix[i].getVal() == 3) {
					if (a == 0) {
						throw invalid_argument("Can't divide by zero");
					}
					c = b / a;
				}
				stack.push(c);
			}
		}
		res = stack.top();
		return res;
	
}
