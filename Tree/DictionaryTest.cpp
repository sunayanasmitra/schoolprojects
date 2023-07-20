
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#include "Dictionary.h"

int main(int argc, char * argv[]){
	Dictionary A;
	//Dictionary B;
	
	
	if(A.size() == 0){
		cout << "SIZE TEST 1: passed\n";
	} else{
		cout << "SIZE TEST 1: failed\n";
	}
	
	keyType k = "air";
	valType v = 1;
	A.setValue(k,v);
	
	k = "water";
	v = 2;
	A.setValue(k,v);
	
	if(A.size() == 2){
		cout << "SIZE TEST 2: passed\n";
	} else{
		cout << "SIZE TEST 2: failed\n";
	}
	
	if(A.contains(k) == true){
		cout << "CONTAINS TEST 1: passed\n";
	} else{
		cout << "CONTAINS TEST 1: failed\n";
	}
	
	k = "earth";
	
	if(A.contains(k) == false){
		cout << "CONTAINS TEST 2: passed\n";
	} else{
		cout << "CONTAINS TEST 2: failed\n";
	}
	
	k = "air";
	
	if(A.getValue(k) == 1){
		cout << "GET VALUE TEST 1: passed\n";
	} else{
		cout << "GET VALUE TEST 1: failed\n";
	}
	
	k = "water";
	
	if(A.getValue(k) == 2){
		cout << "GET VALUE TEST 2: passed\n";
	} else{
		cout << "GET VALUE TEST 2: failed\n";
	}
	
	if(A.hasCurrent() == false){
		cout << "HAS CURRENT TEST 1: passed\n";
	} else{
		cout << "HAS CURRENT TEST 1: failed\n";
	}
	
	A.begin();
	
	if(A.hasCurrent() == true){
		cout << "HAS CURRENT TEST 2: passed\n";
	} else{
		cout << "HAS CURRENT TEST 2: failed\n";
	}
	
	k = "air";
	
	if(A.currentKey() == k){
		cout << "CURRENT KEY TEST 1: passed\n";
	} else{
		cout << "CURRENT KEY TEST 1: failed\n";
	}
	
	A.end();
	k = "water";
	
	if(A.currentKey() == k){
		cout << "CURRENT KEY TEST 2: passed\n";
	} else{
		cout << "CURRENT KEY TEST 2: failed\n";
	}
	
	if(A.currentVal() == 2){
		cout << "CURRENT VAL TEST 1: passed\n";
	} else{
		cout << "CURRENT VAL TEST 1: failed\n";
	}
	
	A.begin();
	
	if(A.currentVal() == 1){
		cout << "CURRENT VAL TEST 2: passed\n";
	} else{
		cout << "CURRENT VAL TEST 2: failed\n";
	}
	
	A.clear();
	
	if(A.size() == 0){
		cout << "CLEAR TEST: passed\n";
	} else{
		cout << "CLEAR TEST: failed\n";
	}
	
	k = "air";
	v = 1;
	A.setValue(k,v);
	
	if(A.size() == 1){
		cout << "SET VALUE TEST 1: passed\n";
	} else{
		cout << "SET VALUE TEST 1: failed\n";
	}
	
	k = "water";
	v = 2;
	A.setValue(k,v);
	
	if(A.size() == 2){
		cout << "SET VALUE TEST 2: passed\n";
	} else{
		cout << "SET VALUE TEST 2: failed\n";
	}
	
	A.remove(k);
	
	if(A.size() == 1){
		cout << "REMOVE TEST 1: passed\n";
	} else{
		cout << "REMOVE TEST 1: failed\n";
	}
	
	k = "air";
	A.remove(k);
	
	if(A.size() == 0){
		cout << "REMOVE TEST 2: passed\n";
	} else{
		cout << "REMOVE TEST 2: failed\n";
	}
	
	exit(0);
}