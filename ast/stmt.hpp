#pragma once

#include <memory>
#include <string>
#include <vector>


namespace AST {

	class Expr;


	class Stmt {
	  public:
		virtual ~Stmt() = default;
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
	};

}
