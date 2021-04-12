#ifndef KALEIDOSCOPE_LEXER_HPP
#define KALEIDOSCOPE_LEXER_HPP

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

	bool operator == (const Token& tok, const char& c) {
		return static_cast<char>(tok) == c;
	}

	std::ostream& operator << (std::ostream& stream, const Token& tok) {
		switch (tok) {
			case Token::Eof:
				stream << "EOF";
				break;
			case Token::Def:
				stream << "def";
				break;
			case Token::Extern:
				stream << "extern";
				break;
			case Token::Ident:
				stream << "Ident: " << s_IdentStr;
				break;
			case Token::Number:
				stream << "Number: " << s_NumVal;
				break;
			default:
				stream << "Unknown: " << static_cast<char>(tok);
				break;
		}
		return stream;
	}


	static Token GetTok() {
		static int s_lastChar = ' ';

		// Ignore whitespace
		while (isspace(s_lastChar))
			s_lastChar = getchar();

		// Ident: [a-zA-Z][a-zA-Z0-9]*
		if (isalpha(s_lastChar)) {
			s_IdentStr = static_cast<char>(s_lastChar);

			while (isalnum((s_lastChar = getchar())))
				s_IdentStr += static_cast<char>(s_lastChar);

			if (s_IdentStr == "def")
				return Token::Def;
			if (s_IdentStr == "extern")
				return Token::Extern;

			return Token::Ident;
		}

		// Number
		if (isdigit(s_lastChar) || s_lastChar == '.') {
			std::string numStr;

			do {
				numStr += static_cast<char>(s_lastChar);
				s_lastChar = getchar();
			} while (isdigit(s_lastChar) || s_lastChar == '.');

			s_NumVal = strtod(numStr.c_str(), nullptr);

			return Token::Number;
		}

		// Comment
		if (s_lastChar == '#') {
			do s_lastChar = getchar();
			while (s_lastChar != EOF && s_lastChar != '\n' && s_lastChar != '\r');

			if (s_lastChar != EOF)
				return GetTok();
		}

		// EOF
		if (s_lastChar == EOF)
			return Token::Eof;

		// Fallback -- just return the character as its ascii value
		int thisChar = s_lastChar;
		s_lastChar = getchar();
		return static_cast<Token>(thisChar);
	}

}


#endif
