#pragma once

#include <string>
#include <iostream>


namespace Lexer {

	static std::string s_IdentStr;
	static double s_NumVal;


	enum class Token : int {
		Eof    = -1,
		// Commands
		Def    = -2,
		Extern = -3,
		// Primary
		Ident  = -4,
		Number = -5,
	};


	bool operator == (const Token& tok, const char& c);

	std::ostream& operator << (std::ostream& stream, const Token& tok);

	Token GetTok();

}
