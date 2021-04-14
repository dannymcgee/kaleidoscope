#pragma once

#include "../Common.h"
#include <map>


class Token {
  public:
	enum class Type {
		// Single-character tokens
		LeftParen, RightParen, LeftBrace, RightBrace, LeftBracket, RightBracket,
		Comma, Dot, Minus, Plus, Semicolon, Slash, Star,
		// 1- or 2-char tokens
		Bang, BangEqual, Equal, EqualEqual, Greater, GreaterEqual, Less, LessEqual,
		// Literals
		Identifier, String, Number,
		// Keywords
		And, Class, Else, False, Fn, For, If, Nil, Or, Print, Return, Super, This,
		True, Var, While,
		// Error
		Unknown,
		// Fin
		Eof,
	};

  private:
	static bool s_StaticsInitialized;
	static std::map<enum Type, const char*> s_StaticLexemes;

  public:
	virtual ~Token() = default;

	virtual Type Type() const = NULL;
	virtual const char* Lexeme() const = NULL;
	virtual int Line() const = NULL;
	virtual int Start() const = NULL;
	virtual string ToString() const = NULL;

  protected:
	static const char* StaticLexeme(enum Type type);

  private:
	static void InitializeStatics();
};


std::ostream& operator << (std::ostream&, enum Token::Type);


#define TOKEN_DEFAULTS \
  private:                                                         \
   const char* m_Lexeme;                                           \
   const enum Token::Type m_Type;                                  \
   const int m_Line;                                               \
	const int m_Start;                                              \
                                                                   \
  public:                                                          \
	enum Token::Type Type() const override { return m_Type; }       \
   const char* Lexeme() const override { return m_Lexeme; }        \
	int Line() const override { return m_Line; }                    \
	int Start() const override { return m_Start; }                  \
	string ToString() const override;


class Operator : public Token {
	TOKEN_DEFAULTS

  public:
	Operator(enum Token::Type type, int line, int start)
		: m_Type(type)
		, m_Lexeme(Token::StaticLexeme(type))
		, m_Line(line)
		, m_Start(start)
	{}

};

DEF_LOGGABLE(Operator);


class Punctuation : public Token {
	TOKEN_DEFAULTS

  public:
	Punctuation(enum Token::Type type, int line, int start)
		: m_Type(type)
		, m_Lexeme(Token::StaticLexeme(type))
		, m_Line(line)
		, m_Start(start)
	{}
};

DEF_LOGGABLE(Punctuation);


class Keyword : public Token {
	TOKEN_DEFAULTS

  public:
	Keyword(enum Token::Type type, int line, int start)
		: m_Type(type)
		, m_Lexeme(Token::StaticLexeme(type))
		, m_Line(line)
		, m_Start(start)
	{}
};

DEF_LOGGABLE(Keyword);


class Ident : public Token {
	TOKEN_DEFAULTS

  public:
	Ident(const char* name, int line, int start)
		: m_Type(Token::Type::Identifier)
		, m_Lexeme(name)
		, m_Line(line)
		, m_Start(start)
	{}

	const char* Name() const { return m_Lexeme; }
};

DEF_LOGGABLE(Ident);


template <typename T>
class Literal : public Token {
	TOKEN_DEFAULTS

  private:
	T m_Value;

  public:
	Literal(
		enum Token::Type type,
		T value,
		const char* lexeme,
		int line,
		int start
	)
		: m_Type(type)
		, m_Value(value)
		, m_Lexeme(lexeme)
		, m_Line(line)
		, m_Start(start)
	{}

	const T& Value() const {
		return m_Value;
	}
};

DEF_LOGGABLE(Literal<string>);
DEF_LOGGABLE(Literal<float>);
