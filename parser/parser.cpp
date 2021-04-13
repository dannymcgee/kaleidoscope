#include "parser.h"

#include <iostream>
#include <vector>

#include "../lexer/lexer.h"
#include "../ast/expr.hpp"
#include "../ast/stmt.hpp"


namespace Parser {

	// -- Implementation details -----------------------------------------------

	static void LogError(const std::string& msg) {
		std::cerr
			<< "LogError: " << msg << std::endl
			<< "Error at token: " << s_CurTok << std::endl;
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


	// -- Public API -----------------------------------------------------------

	Lexer::Token GetNextToken() {
		return (s_CurTok = Lexer::GetTok());
	}


	ExprNode ParsePrimary() {
		switch (s_CurTok) {
			case Lexer::Token::Ident  : return ParseIdentExpr();
			case Lexer::Token::Number : return ParseNumberExpr();
			default:
				if (s_CurTok == '(')     return ParseParenExpr();

				LogError("Unknown token when expecting an expression.");
				return nullptr;
		}
	}


	ExprNode ParseExpression() {
		auto lhs = ParsePrimary();
		if (!lhs) return nullptr;

		return ParseBinOpRhs(0, std::move(lhs));
	}


	ExprNode ParseBinOpRhs(int exprPrecedence, ExprNode lhs) {
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
			auto rhs = ParsePrimary();
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


	ExprNode ParseNumberExpr() {
		auto result = std::make_unique<AST::NumberExpr>(Lexer::s_NumVal);
		GetNextToken(); // Consume the number

		return std::move(result);
	}


	ExprNode ParseParenExpr() {
		GetNextToken(); // Consume '('
		auto v = ParseExpression();

		if (!v)
			return nullptr;

		if (s_CurTok != ')') {
			LogError("Expected ')'.");
			return nullptr;
		}

		GetNextToken(); // Consume ')'

		return v;
	}


	ExprNode ParseIdentExpr() {
		std::string identName = Lexer::s_IdentStr;
		GetNextToken(); // Consume identifier

		// Simple variable
		if (s_CurTok == '(')
			return ParseCallExpr(identName);

		return std::make_unique<AST::VariableExpr>(identName);
	}


	ExprNode ParseCallExpr(const std::string& funcName) {
		GetNextToken(); // Consume '('

		std::vector<ExprNode> args;
		if (s_CurTok != ')') {
			while (true) {
				if (auto arg = ParseExpression())
					args.push_back(std::move(arg));
				else
					return nullptr;

				if (s_CurTok == ')')
					break;

				if (s_CurTok != ',') {
					LogError("Expected ')' or ',' in argument list.");
					return nullptr;
				}

				GetNextToken();
			}
		}
		GetNextToken(); // Consume ')'

		return std::make_unique<AST::CallExpr>(funcName, std::move(args));
	}


	FuncSig ParseFuncSignature() {
		if (s_CurTok != Lexer::Token::Ident) {
			LogError("Expected function name in signature.");
			return nullptr;
		}

		std::string funcName = Lexer::s_IdentStr;
		GetNextToken(); // Consume '('

		if (s_CurTok != '(') {
			LogError("Expected '(' in function signature.");
			return nullptr;
		}

		std::vector<std::string> argNames;
		while (GetNextToken() == Lexer::Token::Ident)
			argNames.push_back(Lexer::s_IdentStr);

		if (s_CurTok != ')') {
			LogError("Expected ')' in function signature.");
			return nullptr;
		}

		GetNextToken(); // Consume ')'

		return std::make_unique<AST::FuncSignature>(
			std::move(funcName),
			std::move(argNames));
	}


	FuncSig ParseExtern() {
		GetNextToken(); // Consume 'extern'
		return ParseFuncSignature();
	}


	StmtNode ParseFuncStmt() {
		GetNextToken(); // Consume 'def'

		auto signature = ParseFuncSignature();
		if (!signature) return nullptr;

		auto body = ParseExpression();
		if (!body) return nullptr;

		return std::make_unique<AST::FuncStmt>(
			std::move(signature),
			std::move(body));
	}


	StmtNode ParseTopLevelExpr() {
		auto expr = ParseExpression();
		if (!expr) return nullptr;

		auto signature = std::make_unique<AST::FuncSignature>(
			"",
			std::vector<std::string>());

		return std::make_unique<AST::FuncStmt>(
			std::move(signature),
			std::move(expr));
	}

}
