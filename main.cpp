#include "lexer/lexer.h"
#include "parser/parser.h"
#include "repl/repl.hpp"


int main() {
	while (true) {
		REPL::Prompt();
		Parser::GetNextToken();

		switch (Parser::s_CurTok) {
			case Lexer::Token::Eof:
				return 0;
			case Lexer::Token::Def:
				REPL::HandleDefinition();
				break;
			case Lexer::Token::Extern:
				REPL::HandleExtern();
				break;
			default:
				if (static_cast<char>(Parser::s_CurTok) == ';') {
					Parser::GetNextToken();
					break;
				}
				REPL::HandleTopLevelExpr();
				break;
		}
	}
}
