
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

int main(int argc, char* argv[]) {
	FILE *fin;
	FILE *fout;
	int lineLen = 1000;
	int recordLen = 1100;
	char *inBuffer;
	List outList = newList();
	char *indexList[recordLen];
	int lineCount = 0;
	int listData;
	int lineDone = 0;
	
	
	if( argc != 3 ){
		fprintf(stderr, "%s", "ERROR: Incorrect number of arguments! We need 2 files to be input after ./Lex!\n");
		return (0);
	}
	
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w+");
	
	if( fin == NULL ){
		fprintf(stderr, "%s", "ERROR: File could not be opened!!\n");
		return (0);
	}
	
	inBuffer = malloc(sizeof(lineLen));
	while( fgets(inBuffer, lineLen, fin) != NULL ){
		indexList[lineCount] = malloc(sizeof(inBuffer));
		strcpy(indexList[lineCount], inBuffer);
		
		if( length(outList) == 0 ){
			prepend(outList,lineCount);
		}else{
			moveFront(outList);
			lineDone = 0;
			while( index(outList) >= 0 && lineDone == 0 ){
				listData = get(outList);
				
				if( strcmp(indexList[lineCount], indexList[listData]) < 0 ){
					insertBefore(outList,lineCount);
					lineDone = 1;
				}else if( strcmp(indexList[lineCount], indexList[listData]) > 0 ){
					if( get(outList) == back(outList) ){
						insertAfter(outList, lineCount);
						lineDone = 1;
					}
				} else{
					insertAfter(outList,lineCount);
					lineDone = 1;
				}
				moveNext(outList);
			}
		}
		
		lineCount = lineCount + 1;
	}
	
	
	moveFront(outList);
	for( int i = 0; i < length(outList); i++ ){
		fprintf(fout, "%s", indexList[get(outList)]);
		moveNext(outList);
	}
	
	
	fclose(fin);
	fclose(fout);
	
	
	if (inBuffer){
		free(inBuffer);
	}
	
	for( int i = 0; i < lineCount; i++ ){
		free(indexList[i]);
	}
	
	freeList(&outList);
	
	
	return (0);
}