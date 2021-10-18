#pragma once
#include <vector>
#include <string>

namespace CParser {
	
	using namespace std;

	enum TokenType {
		WHITESPACE, //no token ever has this type
		IDENTIFIER,
		INTEGER_LITERAL,
		DOUBLE_LITERAL,
		STRING_LITERAL,
		OPERATOR,
		STRING_ESCAPE_SEQUENCE,
		POTENTIAL_DOUBLE,
		POTENTIAL_COMMENT,
		COMMENT
	};

	static const char* sTokenTypeStrings[] = {
		"WHITESPACE", //no token ever has this type
		"IDENTIFIER",
		"INTEGER_LITERAL",
		"DOUBLE_LITERAL",
		"STRING_LITERAL",
		"OPERATOR",
		"STRING_ESCAPE_SEQUENCE",
		"POTENTIAL_DOUBLE",
		"POTENTIAL_COMMENT",
		"COMMENT"
	};

	class Token {
	public:
		enum TokenType mType {WHITESPACE};
		string mText;
		//size_t mStartOffset{0};
		//size_t mEndOffset{0};
		size_t mLineNumber{0};

		void debugPrint() const;
	};

	class Tokenizer {
	public:
		vector<Token> parse(const string &inProgram);
	private:
		void endToken(Token& token, vector<Token>& tokens);
	};

}


