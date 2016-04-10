#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;


vector<string> prologue = {
	"#include <stdio.h>",
	"#include <stdlib.h>",
	"/* best random source on UNIX-like systems. */",
	"int urandom() {",
	"#ifdef __unix__",
	"\tint var;",
	"\tFILE *fd = fopen(\"/dev/urandom\", \"r\");",
	"\tfread(&var, sizeof(int), 1, fd);",
	"\tfclose(fd);",
	"\treturn var;",
	"#else",
	"\treturn 4;",
	"#endif",
	"}",
	"int canary_val = urandom();",
};

bool is_declaration(string str) {
	if(regex_match ("str", std::regex("(( |\t)*)(short) (.*)"))) return true;
	if(regex_match ("str", std::regex("(( |\t)*)(long) (.*)"))) return true;
	if(regex_match ("str", std::regex("(( |\t)*)(char) (.*)"))) return true;
	if(regex_match ("str", std::regex("(( |\t)*)(int) (.*)"))) return true;
	if(regex_match ("str", std::regex("(( |\t)*)(float) (.*)"))) return true;
	if(regex_match ("str", std::regex("(( |\t)*)(double) (.*)"))) return true;
	return false;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "argc != 2" << endl;
		return 1;
	}
	ifstream in_file;
	ofstream out_file;
	in_file.open(argv[1]);
	out_file.open("protected_" + string(argv[1]));
    std::string line; 
    
    for(auto it = prologue.begin() ; it != prologue.end() ; ++it) {
		out_file << *it << endl;
	}
    
    
    int nesting_level = 0;
    int nr_canaries = 0;
    bool in_declarations = false;
    while (std::getline(in_file, line))
    {
		if(line.find("{") != string::npos) {
			nesting_level ++;
			in_declarations = true;
			nr_canaries = 0;
			continue;
		}
		if(line.find("}") != string::npos) {
			nesting_level --;
			in_declarations = false;
			continue;
		}
		
		if(in_declarations) {
			if(!is_declaration(line)) {
				in_declarations = false;
				continue;
			}
			
			out_file << "int canary" + to_string(nr_canaries) + " = canary_val;" << endl;
			nr_canaries++;
			out_file << line << endl;
			out_file << "int canary" + to_string(nr_canaries) + " = canary_val;" << endl;
			nr_canaries++;
		} else {
			out_file << line << endl;
			for (int i = 0 ; i < nr_canaries ; i++) {
				out_file << "if (canary" + to_string(i) + " != canary_val";
				out_file << "printf(\"Alert! Buffer Overflow detected.\");" << " exit(1);" << endl;
			}
		}
    }
}
