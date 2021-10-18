#pragma once
#include <string>
#include <vector>
#include "Type.hpp"
#include "Statement.hpp"

namespace CParser {

	using namespace std;

	class ParameterDefinition {
	public:
		string mName; //empty string means no name given
		Type mType;

		void debugPrint() const;
	};

	class FunctionDefinition
	{
	public:
		string mName;
		vector<ParameterDefinition> mParameters;
		vector<Statement> mStatements;

		void debugPrint() const;
	};

}
