#include "parser.h"

#include <iostream>
#include <vector>

#include "../lexer/lexer.h"
#include "../ast/expr.hpp"
#include "../ast/stmt.hpp"


namespace Parser {

	static Lexer::Token s_CurTok;


	// -- Implementation details -----------------------------------------------

	static AstNode LogError(const std::string& msg) {
		std::cerr << "LogError: " << msg << std::endl;
		return nullptr;
	}

	static std::unique_ptr<AST::FuncSignature> LogErrorP(const std::string& msg) {
		LogError(msg);
		return nullptr;
	}

	static Lexer::Token GetNextToken() {
		return (s_CurTok = Lexer::GetTok());
	}


	// -- Entry Point / Dispatcher ---------------------------------------------

	AstNode Parse() {
		switch (s_CurTok) {
			case Lexer::Token::Ident  : return ParseIdentExpr();
			case Lexer::Token::Number : return ParseNumberExpr();
			default:
				if (s_CurTok == '(')     return ParseParenExpr();

				return LogError("Unknown token when expecting an expression.");
		}
	}


	// -- (Not) Visitors -------------------------------------------------------

	AstNode ParseExpression() {
		return nullptr; // TODO
	}


	AstNode ParseNumberExpr() {
		auto result = std::make_unique<AST::NumberExpr>(Lexer::s_NumVal);
		GetNextToken(); // Consume the number

		return std::move(result);
	}


	AstNode ParseParenExpr() {
		GetNextToken(); // Consume '('
		auto v = ParseExpression();

		if (!v)
			return nullptr;

		if (s_CurTok != ')')
			return LogError("Expected ')'.");

		GetNextToken(); // Consume ')'

		return v;
	}


	AstNode ParseIdentExpr() {
		std::string identName = Lexer::s_IdentStr;
		GetNextToken(); // Consume identifier

		// Simple variable
		if (s_CurTok == '(')
			return ParseCallExpr(identName);

		return std::make_unique<AST::VariableExpr>(identName);
	}


	AstNode ParseCallExpr(const std::string& funcName) {
		GetNextToken(); // Consume '('

		std::vector<AstNode> args;
		if (s_CurTok != ')') {
			while (true) {
				if (auto arg = ParseExpression())
					args.push_back(std::move(arg));
				else
					return nullptr;

				if (s_CurTok == ')')
					break;

				if (s_CurTok != ',')
					return LogError("Expected ')' or ',' in argument list.");

				GetNextToken();
			}
		}
		GetNextToken(); // Consume ')'

		return std::make_unique<AST::CallExpr>(funcName, std::move(args));
	}

}
