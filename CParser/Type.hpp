#pragma once
#include "Data.h"

namespace CParser {
	
	using namespace std;
	
	enum BUILTIN_TYPE {
		VOID,
		INT8,
		UINT8,
		INT16,
		UINT16,
		INT32,
		UINT32,
		DOUBLE,
		STRUCT
	};

	class Type {
	public:
		Type(const string& name = string(), enum BUILTIN_TYPE type = VOID) : mName(name), mType(type) {}

		string mName;
		enum BUILTIN_TYPE mType;
		vector<Type> mField; //for struct only
	};

}
