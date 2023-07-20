
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#include "Dictionary.h"

int main(int argc, char * argv[]){
	Dictionary A;
	//Dictionary B;
	/*
    A.setValue("hello", 1);
    A.setValue("my", 5);
    A.setValue("name", 10);
    A.setValue("is", 15);
    A.setValue("sara", 20);
    A.setValue("lol", 25);
    A.begin();
    A.remove("sara");
	
	cout << A.pre_string();
	*/
	/*string ideal1 = "d\nb\nc\nf\ne\ng\n";
    string ideal2 = "e\nb\nc\nf\ng\n";
    string ideal3 = "e\nb\nc\nf\n";
    A.setValue("d", 1);
    A.setValue("b", 5);
    A.setValue("a", 10);
    A.setValue("c", 15);
    A.setValue("f", 20);
    A.setValue("e", 25);
    A.setValue("g", 30);
    A.begin();
    A.remove("a");
	
    if (A.hasCurrent()){
		cout << "FAIL\n";
	} else{
		cout << "PASS\n";
	}
	
    if (A.pre_string() != ideal1){
		cout << A.pre_string() << " FAIL\n";
	} else{
		cout << "PASS\n";
	}
	
    A.end();
    A.remove("d");
    if (A.currentKey() != "g" || A.currentVal() != 30){
		cout << "FAIL\n";
	} else{
		cout << "PASS\n";
	}
	
    if (A.pre_string() != ideal2){
		cout << A.pre_string() << " FAIL\n";
	} else{
		cout << "PASS\n";
	}
	
    A.remove("g");
    if (A.hasCurrent()){
		cout << "FAIL\n";
	} else{
		cout << "PASS\n";
	}
	
    if (A.pre_string() != ideal3){
		cout << A.pre_string() << " FAIL\n";
	} else{
		cout << "PASS\n";
	}
	*/
	
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
	
	k = "earth";
	v = 2;
	A.setValue(k,v);
	
	if(A.size() == 3){
		cout << "SIZE TEST 2: passed\n";
	} else{
		cout << "SIZE TEST 2: failed\n";
	}
	
	if(A.contains(k) == true){
		cout << "CONTAINS TEST 1: passed\n";
	} else{
		cout << "CONTAINS TEST 1: failed\n";
	}
	
	k = "fire";
	
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