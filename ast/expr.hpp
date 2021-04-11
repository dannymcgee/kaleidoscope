#ifndef KALEIDOSCOPE_EXPR_HPP
#define KALEIDOSCOPE_EXPR_HPP

#include <string>
#include <utility>
#include <memory>
#include <vector>


namespace AST {

	class Expr {
	  public:
		virtual ~Expr() = default;
	};


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
		std::unique_ptr<Expr> m_LHS, m_RHS;

	  public:
		BinaryExpr(char op, Expr* lhs, Expr* rhs)
			: m_Op(op)
			, m_LHS(lhs)
			, m_RHS(rhs)
		{}
	};


	class CallExpr : public Expr {
	  private:
		std::string m_Callee;
		std::vector<std::unique_ptr<Expr>> m_Args;

	  public:
		CallExpr(
			std::string callee,
			std::vector<std::unique_ptr<Expr>> args
		)
			: m_Callee(std::move(callee))
			, m_Args(std::move(args))
		{}
	};

}


#endif
