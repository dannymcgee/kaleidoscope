#ifndef KALEIDOSCOPE_LEXER_HPP
#define KALEIDOSCOPE_LEXER_HPP

#include <string>
#include <iostream>


namespace Lexer {

	static std::string IdentStr;
	static double NumVal;

	enum class Token : int {
		Eof    = -1,
		// Commands
		Def    = -2,
		Extern = -3,
		// Primary
		Ident  = -4,
		Number = -5,
	};

	static Token GetTok() {
		static int LastChar = ' ';

		// Ignore whitespace
		while (isspace(LastChar))
			LastChar = getchar();

		// Ident: [a-zA-Z][a-zA-Z0-9]*
		if (isalpha(LastChar)) {
			IdentStr = static_cast<char>(LastChar);

			while (isalnum((LastChar = getchar())))
				IdentStr += static_cast<char>(LastChar);

			if (IdentStr == "def")
				return Token::Def;
			if (IdentStr == "extern")
				return Token::Extern;

			return Token::Ident;
		}

		// Number
		if (isdigit(LastChar) || LastChar == '.') {
			std::string NumStr;

			do {
				NumStr += static_cast<char>(LastChar);
				LastChar = getchar();
			} while (isdigit(LastChar) || LastChar == '.');

			NumVal = strtod(NumStr.c_str(), nullptr);

			return Token::Number;
		}

		// Comment
		if (LastChar == '#') {
			do LastChar = getchar();
			while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

			if (LastChar != EOF)
				return GetTok();
		}

		// EOF
		if (LastChar == EOF)
			return Token::Eof;

		// Fallback -- just return the character as its ascii value
		int ThisChar = LastChar;
		LastChar = getchar();
		return static_cast<Token>(ThisChar);
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
				stream << "Ident: " << IdentStr;
				break;
			case Token::Number:
				stream << "Number: " << NumVal;
				break;
			default:
				stream << "Unknown: " << static_cast<char>(tok);
				break;
		}

		return stream;
	}

}


#endif
