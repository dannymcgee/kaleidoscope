#ifndef KALEIDOSCOPE_PARSER_HPP
#define KALEIDOSCOPE_PARSER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>


namespace Parser {

	static Lexer::Token s_CurTok;


	static Lexer::Token GetNextToken() {
		return (s_CurTok = Lexer::GetTok());
	}


	std::unique_ptr<AST::Expr> LogError(const std::string& msg) {
		std::cerr << "LogError: " << msg << std::endl;

		return nullptr;
	}

	std::unique_ptr<AST::FuncSignature> LogErrorP(const std::string& msg) {
		LogError(msg);

		return nullptr;
	}


	static std::unique_ptr<AST::Expr> ParseExpression() {
		return nullptr; // TODO
	}

	/** NumberExpr := Number */
	static std::unique_ptr<AST::Expr> ParseNumberExpr() {
		auto result = std::make_unique<AST::NumberExpr>(Lexer::s_NumVal);
		GetNextToken(); // Consume the number

		return std::move(result);
	}

	/** ParenExpr := '(' Expr* ')' */
	static std::unique_ptr<AST::Expr> ParseParenExpr() {
		GetNextToken(); // Consume '('
		auto v = ParseExpression();

		if (!v)
			return nullptr;

		if (s_CurTok != ')')
			return LogError("Expected ')'.");

		GetNextToken(); // Consume ')'

		return v;
	}

	// Foward declaration
	static std::unique_ptr<AST::Expr> ParseCallExpr(const std::string& funcName);

	/** IdentExpr := CallExpr | Ident */
	static std::unique_ptr<AST::Expr> ParseIdentExpr() {
		std::string identName = Lexer::s_IdentStr;
		GetNextToken(); // Consume identifier

		// Simple variable
		if (s_CurTok == '(')
			return ParseCallExpr(identName);

		return std::make_unique<AST::VariableExpr>(identName);
	}

	/** CallExpr := Ident '(' Expr* ')' */
	static std::unique_ptr<AST::Expr> ParseCallExpr(const std::string& funcName) {
		GetNextToken(); // Consume '('

		std::vector<std::unique_ptr<AST::Expr>> args;
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

	/** Primary := IdentExpr | NumberExpr | ParenExpr  */
	static std::unique_ptr<AST::Expr> ParsePrimary() {
		switch (s_CurTok) {
			case Lexer::Token::Ident  : return ParseIdentExpr();
			case Lexer::Token::Number : return ParseNumberExpr();
			default:
				if (s_CurTok == '(')     return ParseParenExpr();

				return LogError("Unknown token when expecting an expression.");
		}
	}

}


#endif
