#include "Data.h"
#include "Tokenizer.hpp"
#include "Parser.hpp"

using namespace std;
using namespace CParser;

enum commands {
	NOT,
	HELP,
	TOKENS,
	PARSE,
	sFILE,
	EXIT
};

int main() {
	//setting the commands map
	map<string, commands> some;
	some["-help"] = HELP;
	some["-tokens"] = TOKENS;
	some["-parse"] = PARSE;
	some["-file"] = sFILE;
	some["-exit"] = EXIT;

	//file opening (the file contatins the c code)
	ifstream fh ("C:\\Users\\Dan\\source\\repos\\CParser\\CParser\\test.myc");
	string fileContents;
	string line;

	while (getline(fh, line)) {
		fileContents.append(line);
		fileContents.append("\n");
	}
	fh.close();
	
	//creating the tokens
	Tokenizer tokenizer;
	vector<Token> tokens = tokenizer.parse(fileContents);

	//creating the parsing tree
	Parser parser;
	parser.parse(tokens);
	
	string command;

	//main menu
	string TEXT = " ::::::::  :::::::::     :::     :::::::::   ::::::::  :::::::::: :::::::::  \n:+:    :+: :+:    :+:  :+: :+:   :+:    :+: :+:    :+: :+:        :+:    :+: \n+:+        +:+    +:+ +:+   +:+  +:+    +:+ +:+        +:+        +:+    +:+ \n+#+        +#++:++#+ +#++:++#++: +#++:++#:  +#++:++#++ +#++:++#   +#++:++#:  \n+#+        +#+       +#+     +#+ +#+    +#+        +#+ +#+        +#+    +#+ \n#+#    #+# #+#       #+#     #+# #+#    #+# #+#    #+# #+#        #+#    #+# \n ########  ###       ###     ### ###    ###  ########  ########## ###    ### ";
	cout << TEXT << "\n";
	cout << "\nThis is a C language parser\n\nMade by: Dan Samoilovitch\nVersion 1.0\n\n";
	cout << "For showing the commands write -help\n";
	cout << "\nType a command:\n";

	bool run = true;
	while (run) {
		cout << "> ";
		cin >> command;
		cout << "\n";
		switch (some[command]) {
		case HELP:
			cout << "[---COMMANDS---]\nyou can use the following commands:\n";
			cout << "\t-help - to get help. :D\n";
			cout << "\t-tokens - to get the code in tokens.\n";
			cout << "\t-parse - to get the code in parsed form.\n";
			cout << "\t-file - to get the code.\n";
			cout << "\t-exit - to exit.\n";
			cout << "\n";
			break;

		case TOKENS:
			cout << "[---TOKENS---]\n";
			for (Token currToken : tokens) {
				currToken.debugPrint();
			}
			cout << "\n";
			break;

		case PARSE:
			cout << "[---PARSED---]\n";
			parser.debugPrint();
			cout << "\n";
			break;

		case sFILE:
			cout << "[---THE CODE---]\n";
			cout << fileContents << endl;
			break;
		
		case EXIT:
			run = false;
			break;
		
		case NOT:
			cout << "Not a command. To see all the availble commands write -help\n";
			break;
		}
	}

	return 0;
}