#pragma once

#include <string>
#include <utility>
#include <memory>
#include <vector>


namespace AST {

	class Expr {
	  public:
		virtual ~Expr() = default;
	};


	using AstNode = std::unique_ptr<Expr>;


	class NumberExpr : public Expr {
	  private:
		double m_Val;

	  public:
		NumberExpr(double val)
			: m_Val(val) {};
	};


	class VariableExpr : public Expr {
	  private:
		std::string m_Name;

	  public:
		VariableExpr(std::string name)
			: m_Name(std::move(name)) {}
	};


	class BinaryExpr : public Expr {
	  private:
		char m_Op;
		AstNode m_LHS, m_RHS;

	  public:
		BinaryExpr(char op, AstNode lhs, AstNode rhs)
			: m_Op(op)
			, m_LHS(std::move(lhs))
			, m_RHS(std::move(rhs))
		{}
	};


	class CallExpr : public Expr {
	  private:
		std::string m_Callee;
		std::vector<AstNode> m_Args;

	  public:
		CallExpr(std::string callee, std::vector<AstNode> args)
			: m_Callee(std::move(callee))
			, m_Args(std::move(args))
		{}
	};

}
