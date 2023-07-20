
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "List.h"

int main(int argc, char** argv){
	List* L1 = new List();
	List* L2 = new List();
	List* L3P = new List();
	
	List L3 = *L3P;
	
	if(L1->length() == 0){
		cout << "LENGTH TEST 1: passed\n";
	} else{
		cout << "LENGTH TEST 1: failed\n";
	}
	
	for(int i = 0; i < 3; i++){
		L1->insertAfter(i);
	}
	
	if(L1->length() == 3){
		cout << "LENGTH TEST 2: passed\n";
	} else{
		cout << "LENGTH TEST 2: failed\n";
	}
	
	for(int i = 0; i < 5; i++){
		L2->insertBefore(i);
	}
	
	if(L2->length() == 5){
		cout << "LENGTH TEST 3: passed\n";
	} else{
		cout << "LENGTH TEST 3: failed\n";
	}
	
	if(L1->front() == 2){
		cout << "FRONT TEST 1: passed\n";
	} else{
		cout << L1->front() << "FRONT TEST 1: failed\n";
	}
	
	if(L2->front() == 0){
		cout << "FRONT TEST 2: passed\n";
	} else{
		cout << L2->front() << "FRONT TEST 2: failed\n";
	}
	
	if(L1->back() == 0){
		cout << "BACK TEST 1: passed\n";
	} else{
		cout << "BACK TEST 1: failed\n";
	}
	
	if(L2->back() == 4){
		cout << "BACK TEST 2: passed\n";
	} else{
		cout << "BACK TEST 2: failed\n";
	}
	
	L1->moveFront();
	L2->moveFront();
	
	if(L1->position() == 0){
		cout << "POSITION TEST 1: passed\n";
	} else{
		cout << "POSITION TEST 1: failed\n";
	}
	
	L2->moveNext();
	L2->moveNext();
	
	if(L2->position() == 2){
		cout << "POSITION TEST 2: passed\n";
	} else{
		cout << "POSITION TEST 2: failed\n";
	}
	
	if(L1->peekNext() == 2){
		cout << "PEEK NEXT TEST 1: passed\n";
	} else{
		cout << "PEEK NEXT TEST 1: failed\n";
	}
	
	L1->moveNext();
	
	if(L1->peekNext() == 1){
		cout << "PEEK NEXT TEST 1: passed\n";
	} else{
		cout << "PEEK NEXT TEST 1: failed\n";
	}
	
	if(L1->peekPrev() == 2){
		cout << "PEEK PREV TEST 1: passed\n";
	} else{
		cout << "PEEK PREV TEST 1: failed\n";
	}
	
	if(L2->peekPrev() == 1){
		cout << "PEEK PREV TEST 2: passed\n";
	} else{
		cout << "PEEK PREV TEST 2: failed\n";
	}
	
	L3.insertBefore(1);
    L3.insertBefore(2);
    L3.insertBefore(3);
    L3.insertBefore(5);
    L3.insertBefore(12);
	
	List A;
	List B;
	
	A.insertAfter(16);
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    A.findNext(16);
	
    if (A.position() != 3){
		cout << "FIND NEXT TEST 1: failed\n";
	} else{
		cout << "FIND NEXT TEST 1: passed\n";
	}

    A.movePrev();
    A.insertBefore(225);
    if (A.position() != 3){
		cout << "FIND NEXT TEST 2: failed\n";
	} else{
		cout << "FIND NEXT TEST 2: passed\n";
	}
	
	B.insertBefore(1);
    B.insertBefore(5);
    B.insertBefore(16);
    B.insertBefore(176);
    B.insertBefore(200);
    B.insertBefore(16);
	
    B.findPrev(16);
    if (B.position() != 5){
		cout << "FIND PREV TEST 1: failed\n";
	} else{
		cout << "FIND PREV TEST 1: passed\n";
	}

    B.moveNext();
    B.insertAfter(225);
    if (B.position() != 6){
		cout << "FIND PREV TEST 2: failed\n";
	} else{
		cout << "FIND PREV TEST 2: passed\n";
	}
	
	List D;
	List E;
	
	D.insertAfter(2);
    D.insertAfter(1);
    E = D;
	
    if (!D.equals(E)){
		cout << "EQUAL TEST: failed\n";
	} else{
		cout << "EQUAL TEST: passed\n";
	}
	
	delete L1;
	delete L2;
	delete L3P;
	
	exit(0);
}