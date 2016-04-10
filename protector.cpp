#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "argc != 2" << endl;
		return 1;
	}
	std::ifstream in_file;
	in_file.open(argv[1]);
    std::string line; 
    
    int nesting_level = 0;
    while (std::getline(in_file, line))
    {
		if(line.find("{") != string::npos) {
			nesting_level ++;
			continue;
		}
		if(line.find("}") != string::npos) {
			nesting_level --;
			continue;
		}
		
		int l = line.find("int") - line.begin()
		
		
		
    }
}
