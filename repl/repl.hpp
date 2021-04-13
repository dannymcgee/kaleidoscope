#pragma once

#include <iostream>

#include "../ast/expr.hpp"
#include "../ast/stmt.hpp"
#include "../parser/parser.h"


namespace REPL {

	static void Prompt() {
		std::cout << " > ";
	}

	static void HandleDefinition() {
		if (auto ast = Parser::ParseFuncStmt()) {
			std::stringstream ss;
			ast->PrettyPrint(ss, 0);
			std::cout << ss.str();
		}
		else Parser::GetNextToken();
	}


	static void HandleExtern() {
		if (auto ast = Parser::ParseExtern()) {
			std::stringstream ss;
			ast->PrettyPrint(ss, 0);
			std::cout << ss.str();
		}
		else Parser::GetNextToken();
	}


	static void HandleTopLevelExpr() {
		if (auto ast = Parser::ParseTopLevelExpr()) {
			std::stringstream ss;
			ast->PrettyPrint(ss, 0);
			std::cout << ss.str();
		}
		else Parser::GetNextToken();
	}

}
