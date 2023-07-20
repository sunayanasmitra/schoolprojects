
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#include "Dictionary.h"

int main(int argc, char * argv[]){
	int token_count, line_count;
	size_t begin, end, line_length;
	ifstream fin;
	ofstream fout;
	string line;
	string tokenBuffer;
	string token;
	Dictionary* D = new Dictionary();
	
	if( argc != 3 ){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	
	fin.open(argv[1]);
	if( !fin.is_open() ){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	fout.open(argv[2]);
	if( !fout.is_open() ){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}
	
	line_count = 0;
	while(getline(fin, line)){
		line_count++;
		line_length = line.length();
		
		token_count = 0;
		tokenBuffer = "";

		begin = min(line.find_first_not_of(" \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789", 0), line_length);
		end = min(line.find_first_of(" \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789", begin), line_length);
		token = line.substr(begin, end-begin);
	
		while( token!="" ){
			std::string s = ""+token+"";
			tokenBuffer.append(s);
			tokenBuffer.append("\n");
			token_count++;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			if(D->contains(s)){
				D->getValue(s)++;
			} else{
				D->setValue(s,1);
			}
			begin = min(line.find_first_not_of(" \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789", end+1), line_length);
			end = min(line.find_first_of(" \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789", begin), line_length);
			token = line.substr(begin, end-begin);
		}
	}
	
	fout << D->to_string();
	
	// close files 
	fin.close();
	fout.close();
	
	delete D;
	
	exit(0);
}