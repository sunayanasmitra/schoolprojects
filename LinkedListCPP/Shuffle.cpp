
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "List.h"

void shuffle(List& D);

int main(int argc, char** argv){
	int count;
	List L;
	List temp;
	int shuffles = 0;
	
	if( argc != 2 ){
		fprintf(stderr, "%s", "ERROR: Incorrect number of arguments! We need an integer to be input after ./Shuffle!\n");
		return (0);
	}
	
	count = atoi(argv[1]);
	
	cout << "deck size       shuffle count\n";
	cout << "------------------------------\n";
	
	for(int j = 1; j <= count; j++){
		shuffles = 0;
		for(int i = 1; i <= j; i++){
			L.insertBefore(i);
		}
		
		temp = L;
		shuffle(L);
		shuffles++;

		while(!(temp == L)){
			shuffle(L);
			shuffles++;
		}

		cout << "" << j << "               " << shuffles << "\n";
		L.clear();
		temp.clear();
	}
	
	
	
	return 0;
}

void shuffle(List& D){
	int len = D.length();
	int t;
	List firstHalf;
	List secondHalf;
	
	D.moveFront();
	for(int l = 0; l < len/2; l++){
		t = D.moveNext();
		firstHalf.insertAfter(t);
		if(firstHalf.length() == 0){
			firstHalf.moveFront();
		} else if(firstHalf.length() > 0){
			firstHalf.moveNext();
		}
	}
	for(int l = len/2; l < len; l++){
		t = D.moveNext();
		secondHalf.insertAfter(t);
		if(secondHalf.length() == 0){
			secondHalf.moveFront();
		} else if(secondHalf.length() > 0){
			secondHalf.moveNext();
		}
	}
	
	if(D.length() > 0 && secondHalf.length() > 0 && firstHalf.length() > 0){
		D.moveFront();
		secondHalf.moveFront();
		firstHalf.moveFront();
		
		while(firstHalf.position() < firstHalf.length()){
			D.moveNext();
			D.setBefore(secondHalf.moveNext());
			D.moveNext();
			D.setBefore(firstHalf.moveNext());
		}
	}
	
}