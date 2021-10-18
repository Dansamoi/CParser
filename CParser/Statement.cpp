#include "Statement.hpp"
#include <iostream>

namespace CParser {
	using namespace std;
	void Statement::debugPrint()
	{
		cout << "\t" << sStatementKindStrings[int(mKind)] << " ";
		cout << mType.mName << " " << mName << " (\n";
		for (Statement statement : mParameters) {
			cout << "\t";
			statement.debugPrint();
		}
		cout << "\t)" << endl;
	}
}


