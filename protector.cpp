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
	"int canary_val = 0;",
	"int get_canary_val() {",
	"\twhile (!canary_val)",
	"\t\tcanary_val = urandom();",
	"\treturn canary_val;",
	"}",
};

string line_first_word(string line) {
	string word;
	std::istringstream is;
	is.str(line);
	is >> word;
	return word;
}

bool is_else(string line) {
	return line_first_word(line) == "else";
}

bool is_declaration(string line) {
	const static vector<string> types = { "short",
		"long",
		"char",
		"int",
		"float",
		"double",
	};
	
	string word = line_first_word(line);

	for(auto it = types.begin() ; it != types.end() ; ++it) {
		if(word == *it)
			return true;
	}
	return false;
}

void print_sainity_check(ofstream& out_file, int nr_canaries) {
	for (int i = 0 ; i < nr_canaries ; i++) {
			out_file << "if (canary" + to_string(i) + " != get_canary_val()) {";
			out_file << "printf(\"Alert! Buffer Overflow detected.\");" << " exit(1); }" << endl;
	}
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
		string word = line_first_word(line);
		if(word.size() == 0)
			continue;
		
		if(line.find("{") != string::npos) {
			nesting_level ++;
			in_declarations = true;
			if(nesting_level == 1)
				nr_canaries = 0;
			out_file << line << endl;
			continue;
		}
		if(line.find("}") != string::npos) {
			nesting_level --;
			in_declarations = false;
			print_sainity_check(out_file, nr_canaries);
			out_file << line << endl;
			continue;
		}
		
		if(in_declarations) {
			if(!is_declaration(line)) {
				in_declarations = false;
				if(!is_else(line))
					print_sainity_check(out_file, nr_canaries);
				out_file << line << endl;
				continue;
			}
			
			out_file << "int canary" + to_string(nr_canaries) + " = get_canary_val();" << endl;
			nr_canaries++;
			out_file << line << endl;
			out_file << "int canary" + to_string(nr_canaries) + " = get_canary_val();" << endl;
			nr_canaries++;
		} else {
			if(nesting_level && !is_else(line)) {
				print_sainity_check(out_file, nr_canaries);
			}
			out_file << line << endl;
		}
    }
}
