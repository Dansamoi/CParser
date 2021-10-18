#include "FunctionDefinition.hpp"
#include <iostream>


namespace CParser {
	using namespace std;

	void ParameterDefinition::debugPrint() const
	{
		cout << mType.mName << " " << mName << endl;
	}
	
	void FunctionDefinition::debugPrint() const
	{
		cout << mName << "(\n";

		for (ParameterDefinition param : mParameters) {
			param.debugPrint();
		}

		cout << ")" << "{" << endl;
		for (Statement statement : mStatements) {
			statement.debugPrint();
		}
		cout << "}" << endl;
	}
}
