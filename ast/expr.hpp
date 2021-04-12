#pragma once

#include <string>
#include <sstream>
#include <utility>
#include <memory>
#include <vector>


namespace AST {

	class Expr {
	  public:
		virtual ~Expr() = default;
		virtual void PrettyPrint(std::stringstream& output, int indent) = NULL;
	};


	using AstNode = std::unique_ptr<Expr>;


	static std::string Indent(int level) {
		std::string result;
		for (int i = 0; i < level; i++)
			result += "   ";

		return result;
	}


	class NumberExpr : public Expr {
	  private:
		double m_Val;

	  public:
		NumberExpr(double val)
			: m_Val(val) {};

		void PrettyPrint(std::stringstream& output, int indent) override {
			auto indentStr = Indent(indent);
			output
				<< indentStr << "NumberExpr {" << std::endl
				<< indentStr << "   Value: " << m_Val << std::endl
				<< indentStr << "}" << std::endl;
		}
	};


	class VariableExpr : public Expr {
	  private:
		std::string m_Name;

	  public:
		VariableExpr(std::string name)
			: m_Name(std::move(name)) {}

		void PrettyPrint(std::stringstream& output, int indent) override {
			auto indentStr = Indent(indent);
			output
				<< indentStr << "VariableExpr {" << std::endl
				<< indentStr << "   Name: " << m_Name << std::endl
				<< indentStr << "}" << std::endl;
		}
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

		void PrettyPrint(std::stringstream& output, int indent) override {
			auto indentStr = Indent(indent);
			output << indentStr << "BinaryExpr {" << std::endl;
			m_LHS->PrettyPrint(output, indent + 1);
			output << indentStr << "   Operator: " << m_Op << std::endl;
			m_RHS->PrettyPrint(output, indent + 1);
			output << indentStr << "}" << std::endl;
		}
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

		void PrettyPrint(std::stringstream& output, int indent) override {
			auto indentStr = Indent(indent);
			output
				<< indentStr << "CallExpr {" << std::endl
				<< indentStr << "   Function: " << m_Callee << std::endl
				<< indentStr << "   Args: [" << std::endl;

			for (const auto& arg : m_Args) {
				arg->PrettyPrint(output, indent + 1);
			}

			output
				<< indentStr << "   ]" << std::endl
				<< indentStr << "}" << std::endl;
		}
	};

}
