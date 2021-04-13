#pragma once

#include <memory>
#include <string>
#include <vector>


namespace AST {

	class Expr;


	class Stmt {
	  public:
		virtual ~Stmt() = default;
		virtual void PrettyPrint(std::stringstream& output, int indent) = NULL;
	};


	struct FuncSignature {
	  private:
		std::string m_Name;
		std::vector<std::string> m_Params;

	  public:
		FuncSignature(
			std::string name,
			std::vector<std::string> params
		)
			: m_Name(std::move(name))
			, m_Params(std::move(params))
		{}

		void PrettyPrint(std::stringstream& output, int indent) {
			auto indentStr = Indent(indent);
			output
				<< indentStr << "FuncSignature {" << std::endl
				<< indentStr << "   Name: " << m_Name << std::endl
				<< indentStr << "   Params: [" << std::endl;

			for (const auto& param : m_Params) {
				output << indentStr << "      " << param << std::endl;
			}

			output
				<< indentStr << "   ]" << std::endl
				<< indentStr << "}" << std::endl;
		}
	};


	class FuncStmt : public Stmt {
	  private:
		std::unique_ptr<FuncSignature> m_Signature;
		std::unique_ptr<Expr> m_Body;

	  public:
		FuncStmt(
			std::unique_ptr<FuncSignature> signature,
			std::unique_ptr<Expr> body
		)
			: m_Signature(std::move(signature))
			, m_Body(std::move(body))
		{}

		void PrettyPrint(std::stringstream& output, int indent) override {
			auto indentStr = Indent(indent);
			output << indentStr << "FuncStmt {" << std::endl;
			m_Signature->PrettyPrint(output, indent + 1);
			m_Body->PrettyPrint(output, indent + 1);
			output << indentStr << "}" << std::endl;
		}
	};

}
