#pragma once

#include <memory>
#include <string>


// Fwd declaration
namespace AST {
	class Expr;
}


namespace Parser {

	using AstNode = std::unique_ptr<AST::Expr>;

	/** Primary := IdentExpr | NumberExpr | ParenExpr  */
	AstNode Parse();

	static AstNode ParseExpression();

	static AstNode ParseBinOpRhs(int exprPrecedence, AstNode lhs);

	/** NumberExpr := Number */
	static AstNode ParseNumberExpr();

	/** ParenExpr := '(' Expr ')' */
	static AstNode ParseParenExpr();

	/** IdentExpr := CallExpr | Ident */
	static AstNode ParseIdentExpr();

	/** CallExpr := Ident '(' ( Expr ( ',' Expr )* )? ')' */
	static AstNode ParseCallExpr(const std::string& funcName);

}
