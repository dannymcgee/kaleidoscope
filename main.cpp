#include <iostream>

#include "lexer.hpp"
#include "ast/expr.hpp"
#include "ast/stmt.hpp"


int main() {
	Lexer::Token tok;

	while ((tok = Lexer::GetTok()) != Lexer::Token::Eof)
		std::cout << tok << std::endl;
}
