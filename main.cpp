#include <iostream>

#include "ast/expr.hpp"
#include "ast/stmt.hpp"
#include "lexer/lexer.h"
#include "parser/parser.h"


int main() {
	Lexer::Token tok;

	while ((tok = Lexer::GetTok()) != Lexer::Token::Eof)
		std::cout << tok << std::endl;
}
