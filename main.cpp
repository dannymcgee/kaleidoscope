#include "Common.h"
#include <iostream>

#include "Token/Token.h"


int main() {
	vector<Operator> ops;
	vector<Punctuation> puncs;
	vector<Keyword> keywords;

#define EMPLACE(type) \
	ops.emplace_back(Operator(Token::Type::##type, 0, 0))
	EMPLACE(Bang);
	EMPLACE(BangEqual);
	EMPLACE(Dot);
	EMPLACE(Equal);
	EMPLACE(EqualEqual);
	EMPLACE(Greater);
	EMPLACE(GreaterEqual);
	EMPLACE(Less);
	EMPLACE(LessEqual);
	EMPLACE(Minus);
	EMPLACE(Plus);
	EMPLACE(Slash);
	EMPLACE(Star);
#undef EMPLACE

#define EMPLACE(type) \
	puncs.emplace_back(Punctuation(Token::Type::##type, 0, 0))
	EMPLACE(LeftParen);
	EMPLACE(RightParen);
	EMPLACE(LeftBrace);
	EMPLACE(RightBrace);
	EMPLACE(LeftBracket);
	EMPLACE(RightBracket);
	EMPLACE(Comma);
	EMPLACE(Semicolon);
#undef EMPLACE

#define EMPLACE(type) \
	keywords.emplace_back(Keyword(Token::Type::##type, 0, 0))
	EMPLACE(And);
	EMPLACE(Class);
	EMPLACE(Else);
	EMPLACE(False);
	EMPLACE(Fn);
	EMPLACE(For);
	EMPLACE(If);
	EMPLACE(Nil);
	EMPLACE(Or);
	EMPLACE(Print);
	EMPLACE(Return);
	EMPLACE(Super);
	EMPLACE(This);
	EMPLACE(True);
	EMPLACE(Var);
	EMPLACE(While);
#undef EMPLACE

	for (const auto& op : ops)
		std::cout << op << std::endl;
	for (const auto& punc : puncs)
		std::cout << punc << std::endl;
	for (const auto& kw : keywords)
		std::cout << kw << std::endl;

	auto ident = Ident("foo", 0, 0);
	std::cout << ident << std::endl;

	auto str = Literal<string>(
		Token::Type::String,
		"Lorem Ipsum",
		"\"Lorem Ipsum\"",
		0,
		0);
	std::cout << str << std::endl;

	auto num = Literal<float>(
		Token::Type::Number,
		42,
		"42",
		0,
		0);
	std::cout << num << std::endl;
}
