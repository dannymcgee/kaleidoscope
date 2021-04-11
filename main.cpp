#include <iostream>

#include "lexer.hpp"


int main() {
	Lexer::Token tok;

	while ((tok = Lexer::GetTok()) != Lexer::Token::Eof)
		std::cout << tok << std::endl;
}
