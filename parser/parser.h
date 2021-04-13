#pragma once

#include <memory>
#include <string>


// Fwd declarations
namespace AST {
	class Expr;
	class FuncSignature;
	class Stmt;
}
namespace Lexer {
	enum class Token;
}


namespace Parser {

	// Type aliases for readability
	using ExprNode = std::unique_ptr<AST::Expr>;
	using FuncSig = std::unique_ptr<AST::FuncSignature>;
	using StmtNode = std::unique_ptr<AST::Stmt>;


	static Lexer::Token s_CurTok;

	Lexer::Token GetNextToken();

	ExprNode ParsePrimary();
	ExprNode ParseExpression();
	ExprNode ParseBinOpRhs(int exprPrecedence, ExprNode lhs);
	ExprNode ParseNumberExpr();
	ExprNode ParseParenExpr();
	ExprNode ParseIdentExpr();
	ExprNode ParseCallExpr(const std::string& funcName);
	FuncSig ParseFuncSignature();
	FuncSig ParseExtern();
	StmtNode ParseFuncStmt();
	StmtNode ParseTopLevelExpr();

}
