#pragma once
#include "Data.h"
#include "Tokenizer.hpp"
#include "Statement.hpp"
#include "FunctionDefinition.hpp"

namespace CParser {

	using namespace std;

	class Parser {
	public:
		Parser();
		
		void parse(vector<Token> &tokens);

		void debugPrint() const;

	private:
		optional<Type> expectType();

		optional<vector<Statement>> parseFunctionBody();
		optional<Statement> expectOneValue();

		optional<Statement> expectVariableDeclaration();
		optional<Statement> expectFunctionCall();
		bool expectFunctionDefinition();

		optional<Token> expectTokenType(TokenType type, const string& name = string());

		vector<Token>::iterator mEndToken;
		vector<Token>::iterator mCurrentToken;
		map<string, Type> mTypes;
		map<string, FunctionDefinition> mFunctions;
	};
}


