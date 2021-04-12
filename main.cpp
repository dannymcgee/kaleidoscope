#include <iostream>

#include "ast/expr.hpp"
#include "ast/stmt.hpp"
#include "lexer.hpp"
#include "parser.hpp"


int main() {
	Lexer::Token tok;

	while ((tok = Lexer::GetTok()) != Lexer::Token::Eof)
		std::cout << tok << std::endl;
}
