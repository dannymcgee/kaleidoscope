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

	static int GetOpPrecedence() {
		switch (static_cast<char>(s_CurTok)) {
			case '<' :
			case '>' : return 10;
			case '+' :
			case '-' : return 20;
			case '*' : return 40;
			case '/' : return 50;
			default  : return -1;
		}
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
		auto lhs = Parse();
		if (!lhs) return nullptr;

		return ParseBinOpRhs(0, std::move(lhs));
	}


	AstNode ParseBinOpRhs(int exprPrecedence, AstNode lhs) {
		// If this is a binop, find its precedence
		while (true) {
			int opPrecedence = GetOpPrecedence();

			// If this is a binop that binds at least as tightly as the current binop,
			// consume it. Otherwise, we are done.
			if (opPrecedence < exprPrecedence)
				return lhs;

			// Okay, we know this is a binary operator.
			auto binOp = static_cast<char>(s_CurTok);
			GetNextToken(); // Consume the operator

			// Parse the primary expression after the binary operator
			auto rhs = Parse();
			if (!rhs) return nullptr;

			// If the current operator binds less tightly with rhs than the operator *after*
			// rhs, let the pending operator take rhs as its lhs.
			// TODO: This comment is word soup, just draw a diagram
			int nextPrecedence = GetOpPrecedence();
			if (opPrecedence < nextPrecedence) {
				rhs = ParseBinOpRhs(opPrecedence + 1, std::move(rhs));
				if (!rhs) return nullptr;
			}

			// Merge lhs/rhs
			lhs = std::make_unique<AST::BinaryExpr>(
				binOp,
				std::move(lhs),
				std::move(rhs));
		}
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
