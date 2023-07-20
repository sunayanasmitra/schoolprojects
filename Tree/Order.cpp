
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
	Dictionary D;
	
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
		
		// get tokens in this line
		token_count = 0;
		tokenBuffer = "";

		// get first token
		begin = min(line.find_first_not_of(" ", 0), line_length);
		end = min(line.find_first_of(" ", begin), line_length);
		token = line.substr(begin, end-begin);
	
		while( token!="" ){  // we have a token
			// update token buffer
			std::string s = ""+token+"";
			//tokenBuffer += s + "\n";
			tokenBuffer.append(s);
			tokenBuffer.append("\n");
			token_count++;
			//cout << " token in " <<  s  << "\n";
			s.erase(remove(s.begin(), s.end(), '\r'), s.end());
			//cout << s << " " << line_count << " tokencount\n";
			D.setValue(s,line_count);
			begin = min(line.find_first_not_of(" ", end+1), line_length);
			end = min(line.find_first_of(" ", begin), line_length);
			token = line.substr(begin, end-begin);
		}
	}
	
	fout << D.to_string();
	fout << "\n";
	fout << D.pre_string();
	
	// close files 
	fin.close();
	fout.close();
	
	exit(0);
}