#include "Parser.hpp"
#include <iostream>
#include <optional>
#include <map>
#include "FunctionDefinition.hpp"
#include "Statement.hpp"

namespace CParser {

	using namespace std;

	bool Parser::expectFunctionDefinition() {
		vector<Token>::iterator parseStart = mCurrentToken;
		//cheking if we are in a function - type name(
		optional<Type> possibleType = expectType();
		if (possibleType.has_value()) { //there is a type
			optional<Token> possibleName = expectTokenType(IDENTIFIER);

			if (possibleName.has_value()) { //there is a name
				optional<Token> possibleOperator = expectTokenType(OPERATOR, "(");

				if (possibleOperator.has_value()) { //there is a function
					
					FunctionDefinition func;
					func.mName = possibleName->mText;
					//cout << "Found a function: " << possibleName->mText << ".\n";
					
					while (!expectTokenType(OPERATOR, ")").has_value()) {
						optional<Type> possibleParamType = expectType();
						if (!possibleParamType.has_value()) {
							throw runtime_error("Expected a type at start of argument list.");
						}
						optional<Token> possibleVarName = expectTokenType(IDENTIFIER);

						ParameterDefinition param;
						param.mType = possibleParamType->mName;
						if (possibleVarName.has_value()) {
							param.mName = possibleVarName->mText;
						}
						func.mParameters.push_back(param);
						if (expectTokenType(OPERATOR, ")").has_value()) break;
						if (!expectTokenType(OPERATOR, ",").has_value()) {
							throw runtime_error("Expected ',' to seperate parameters of ')' to indicate end of argument list.");
						}
					}
					
					optional<vector<Statement>> statements = parseFunctionBody();
					if (!statements.has_value()) {
						mCurrentToken = parseStart;
						return false;
					}

					func.mStatements.insert(func.mStatements.begin(), statements->begin(), statements->end());
					mFunctions[func.mName] = func;
					return true;
				}
				else {
					mCurrentToken = parseStart;
				}
			}
			else {
				mCurrentToken = parseStart;
			}
		}
		return false;
	}

	void Parser::parse(vector<Token> &tokens)
	{
		mEndToken = tokens.end();
		mCurrentToken = tokens.begin();

		while (mCurrentToken != mEndToken) {
			if (expectFunctionDefinition()) {
			
			}
			else {
				cerr << "Unknown identifier " << mCurrentToken->mText << "." << endl;
				++mCurrentToken;
			}
			
		}
	}

	void Parser::debugPrint() const
	{
		for (auto funcPair : mFunctions) {
			funcPair.second.debugPrint();
		}
	}

	optional<vector<Statement>> Parser::parseFunctionBody() {
		if (!expectTokenType(OPERATOR, "{").has_value()) {
			return nullopt;
		}

		vector<Statement> statements;
		
		while (!expectTokenType(OPERATOR, "}").has_value()) {
			optional<Statement> statement = expectOneValue();
			if (statement.has_value()) {
				statements.push_back(statement.value());
			}

			if (!expectTokenType(OPERATOR, ";").has_value()) {
				throw runtime_error("Expected ';' at end of a statement");
			}

		}

		return statements;
	}

	optional<Statement> Parser::expectOneValue() {
		optional<Statement> result;
		if (mCurrentToken != mEndToken) {
			Statement literalStatement;
			literalStatement.mKind = StatementKind::LITERAL;
			literalStatement.mName = mCurrentToken->mText;

			switch (mCurrentToken->mType) {
			case DOUBLE_LITERAL:
				literalStatement.mType = Type("double", DOUBLE);
				result = literalStatement;
				++mCurrentToken;
				break;

			case INTEGER_LITERAL:
				literalStatement.mType = Type("signed integer", INT32);
				result = literalStatement;
				++mCurrentToken;
				break;

			case STRING_LITERAL:
				literalStatement.mType = Type("string", UINT8);
				result = literalStatement;
				++mCurrentToken;
				break;
			
			default:
				result = expectVariableDeclaration();
				break;
			}
		}

		if (!result.has_value()) {
			result = expectFunctionCall();
		}

		return result;
	}

	optional<Statement> Parser::expectFunctionCall() {
		vector<Token>::iterator startToken = mCurrentToken;
		optional<Token> possibleFuncName = expectTokenType(IDENTIFIER);
		if (!possibleFuncName.has_value()) {
			mCurrentToken = startToken;
			return nullopt;
		}

		if (!expectTokenType(OPERATOR, "(").has_value()) {
			mCurrentToken = startToken;
			return nullopt;
		}

		Statement functionCall;
		functionCall.mKind = StatementKind::FUNCTION_CALL;
		functionCall.mName = possibleFuncName->mText;

		while (!expectTokenType(OPERATOR, ")").has_value()) {
			optional<Statement> parameter = expectOneValue();
			if (!parameter.has_value()) {
				throw runtime_error("Expected expression as parameter.");
			}
			functionCall.mParameters.push_back(parameter.value());

			if (expectTokenType(OPERATOR, ")").has_value()) {
				break;
			}
			if (!expectTokenType(OPERATOR, ",").has_value()) {
				throw runtime_error("Expected ',' to separate parameters.");
			}
		}

		return functionCall;
	}

	optional<Statement> Parser::expectVariableDeclaration() {
		vector<Token>::iterator startToken = mCurrentToken;
		optional<Type> possibleType = expectType();
		if (!possibleType.has_value()) {
			mCurrentToken = startToken;
			return nullopt;
		}

		optional<Token> possibleVariableName = expectTokenType(IDENTIFIER);
		if (!possibleVariableName.has_value()) {
			mCurrentToken = startToken;
			return nullopt;
		}

		Statement statement;

		statement.mKind = StatementKind::VARIABLE_DECLARATION;
		statement.mName = possibleVariableName->mText;
		statement.mType = possibleType.value();

		if (expectTokenType(OPERATOR, "=").has_value()) {
			optional<Statement> initialValue = expectOneValue();
			if (!initialValue.has_value()) {
				throw runtime_error("Expected initial value after '=' in variable declaration.");
			}
			statement.mParameters.push_back(initialValue.value());
		}

		return statement;

	}

	optional<Type> Parser::expectType()
	{
		optional<Token> possibleType = expectTokenType(IDENTIFIER);
		if (!possibleType) { return nullopt; }

		map<string, Type>::iterator foundType = mTypes.find(possibleType->mText);
		if(foundType == mTypes.end()) { 
			--mCurrentToken;
			return nullopt; 
		}
		return foundType->second;
	}

	optional<Token> Parser::expectTokenType(TokenType type, const string& name)
	{
		if (mCurrentToken == mEndToken) { return nullopt; }
		if (mCurrentToken->mType != type) { return nullopt; }
		if (!name.empty() && mCurrentToken->mText != name) { return nullopt; }

		Token returnToken = *mCurrentToken;
		++mCurrentToken;
		return returnToken;
	}

	Parser::Parser()
	{
		mTypes["void"] = Type("void", VOID);
		mTypes["int"] = Type("signed int", INT32);
		mTypes["unsigned"] = Type("unsigned int", INT32);
		mTypes["char"] = Type("signed char", UINT8);
		mTypes["uint8_t"] = Type("uint8_t", INT8);
		mTypes["double"] = Type("double", DOUBLE);
	}
}

