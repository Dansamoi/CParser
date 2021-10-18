#pragma once
#include "Tokenizer.hpp"
#include "FunctionDefinition.hpp"
#include <optional>
#include <string>
#include <map>
#include <vector>
#include "Type.hpp"
#include "Statement.hpp"

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
		/*
		//name has no value => any identifier
		optional<Token> expectIdentifier(const string& name = string());
		
		//name has no value => any operator
		optional<Token> expectOperator(const string& name = string());\
		*/
		//name has no value => any operator
		optional<Token> expectTokenType(TokenType type, const string& name = string());

		vector<Token>::iterator mEndToken;
		vector<Token>::iterator mCurrentToken;
		map<string, Type> mTypes;
		map<string, FunctionDefinition> mFunctions;
	};
}


