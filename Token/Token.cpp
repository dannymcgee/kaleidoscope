#include "Token.h"

#include <iostream>
#include <sstream>


std::map<enum Token::Type, const char*> Token::s_StaticLexemes; // NOLINT(cert-err58-cpp)
bool Token::s_StaticsInitialized;


const char* Token::StaticLexeme(enum Token::Type type) {
	if (!Token::s_StaticsInitialized)
		Token::InitializeStatics();

	if (!Token::s_StaticLexemes.contains(type)) {
		std::cerr
			<< "ERROR: Could not find static lexeme for "
			<< type
			<< std::endl;

		return "ERROR";
	}

	return Token::s_StaticLexemes[type];
}


void Token::InitializeStatics() {
#define INSERT(key, val) \
	s_StaticLexemes.insert(std::pair(Type::##key, ##val))

	// Punctuation
	INSERT(Comma, ",");
	INSERT(LeftParen, "(");
	INSERT(RightParen, ")");
	INSERT(LeftBrace, "{");
	INSERT(RightBrace, "}");
	INSERT(LeftBracket, "[");
	INSERT(RightBracket, "]");
	INSERT(Semicolon, ";");

	// Operators
	INSERT(Bang, "!");
	INSERT(BangEqual, "!=");
	INSERT(Dot, ".");
	INSERT(Equal, "=");
	INSERT(EqualEqual, "==");
	INSERT(Greater, ">");
	INSERT(GreaterEqual, ">=");
	INSERT(Less, "<");
	INSERT(LessEqual, "<=");
	INSERT(Minus, "-");
	INSERT(Plus, "+");
	INSERT(Slash, "/");
	INSERT(Star, "*");

	// Keywords
	INSERT(And, "and");
	INSERT(Class, "class");
	INSERT(Else, "else");
	INSERT(False, "false");
	INSERT(Fn, "fn");
	INSERT(For, "for");
	INSERT(If, "if");
	INSERT(Nil, "nil");
	INSERT(Or, "or");
	INSERT(Print, "print");
	INSERT(Return, "return");
	INSERT(Super, "super");
	INSERT(This, "this");
	INSERT(True, "true");
	INSERT(Var, "var");
	INSERT(While, "while");

	// EOF
	INSERT(Eof, "");

#undef INSERT

	Token::s_StaticsInitialized = true;
}


std::ostream& operator << (std::ostream& stream, enum Token::Type type) {
	switch (type) {
		case Token::Type::LeftParen    : stream << "LeftParen"; break;
		case Token::Type::RightParen   : stream << "RightParen"; break;
		case Token::Type::LeftBrace    : stream << "LeftBrace"; break;
		case Token::Type::RightBrace   : stream << "RightBrace"; break;
		case Token::Type::LeftBracket  : stream << "LeftBracket"; break;
		case Token::Type::RightBracket : stream << "RightBracket"; break;
		case Token::Type::Comma        : stream << "Comma"; break;
		case Token::Type::Dot          : stream << "Dot"; break;
		case Token::Type::Minus        : stream << "Minus"; break;
		case Token::Type::Plus         : stream << "Plus"; break;
		case Token::Type::Semicolon    : stream << "Semicolon"; break;
		case Token::Type::Slash        : stream << "Slash"; break;
		case Token::Type::Star         : stream << "Star"; break;
		case Token::Type::Bang         : stream << "Bang"; break;
		case Token::Type::BangEqual    : stream << "BangEqual"; break;
		case Token::Type::Equal        : stream << "Equal"; break;
		case Token::Type::EqualEqual   : stream << "EqualEqual"; break;
		case Token::Type::Greater      : stream << "Greater"; break;
		case Token::Type::GreaterEqual : stream << "GreaterEqual"; break;
		case Token::Type::Less         : stream << "Less"; break;
		case Token::Type::LessEqual    : stream << "LessEqual"; break;
		case Token::Type::Identifier   : stream << "Identifier"; break;
		case Token::Type::String       : stream << "String"; break;
		case Token::Type::Number       : stream << "Number"; break;
		case Token::Type::And          : stream << "And"; break;
		case Token::Type::Class        : stream << "Class"; break;
		case Token::Type::Else         : stream << "Else"; break;
		case Token::Type::False        : stream << "False"; break;
		case Token::Type::Fn           : stream << "Fn"; break;
		case Token::Type::For          : stream << "For"; break;
		case Token::Type::If           : stream << "If"; break;
		case Token::Type::Nil          : stream << "Nil"; break;
		case Token::Type::Or           : stream << "Or"; break;
		case Token::Type::Print        : stream << "Print"; break;
		case Token::Type::Return       : stream << "Return"; break;
		case Token::Type::Super        : stream << "Super"; break;
		case Token::Type::This         : stream << "This"; break;
		case Token::Type::True         : stream << "True"; break;
		case Token::Type::Var          : stream << "Var"; break;
		case Token::Type::While        : stream << "While"; break;
		case Token::Type::Unknown      : stream << "Unknown"; break;
		case Token::Type::Eof          : stream << "Eof"; break;
	}

	return stream;
}

string Operator::ToString() const {
	std::stringstream stream;
	stream
		<< "Operator {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Operator, tok) {
	stream << tok.ToString();
	return stream;
}


string Punctuation::ToString() const {
	std::stringstream stream;
	stream
		<< "Punctuation {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Punctuation, tok) {
	stream << tok.ToString();
	return stream;
}


string Keyword::ToString() const {
	std::stringstream stream;
	stream
		<< "Keyword {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Keyword, tok) {
	stream << tok.ToString();
	return stream;
}


string Ident::ToString() const {
	std::stringstream stream;
	stream
		<< "Ident {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Name: " << Name() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Ident, tok) {
	stream << tok.ToString();
	return stream;
}


template<>
string Literal<string>::ToString() const {
	std::stringstream stream;
	stream
		<< "Literal {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Value: " << Value() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Literal<string>, tok) {
	stream << tok.ToString();
	return stream;
}


template<>
string Literal<float>::ToString() const {
	std::stringstream stream;
	stream
		<< "Literal {" << std::endl
		<< "   Type: " << Type() << std::endl
		<< "   Value: " << Value() << std::endl
		<< "   Lexeme: " << Lexeme() << std::endl
		<< "   Line: " << Line() << std::endl
		<< "   Start: " << Start() << std::endl
		<< "}";

	return stream.str();
}

IMPL_LOGGABLE(Literal<float>, tok) {
	stream << tok.ToString();
	return stream;
}

