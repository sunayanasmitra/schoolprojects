
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char* argv[]){
	int i;
	List A = newList();
	List B = newList();

	for(i=1; i<=10; i++){
		append(A, i);
		append(B, 11-i);
   }
   
   printf("Sara's Tests:\n");
   
   
   
   if( length(A) == length(B) ){
	   printf("TEST: length passed\n");
   } else{
	   printf("TEST: length failed\n");
   }
   
   deleteBack(B);
   
   if( length(A) > length(B) ){
	   printf("TEST: length passed\n");
   } else{
	   printf("TEST: length failed\n");
   }
   
   if( index(A) == -1 ){
	   printf("TEST: index passed\n");
   } else{
	   printf("TEST: index failed\n");
   }
   
   moveFront(A);
   
   if( index(A) == 0 ){
	   printf("TEST: index passed\n");
   } else{
	   printf("TEST: index failed\n");
   }
   
   if( front(A) == 1 ){
	   printf("TEST: front passed\n");
   } else{
	   printf("TEST: front failed\n");
   }
   
   if( front(B) == 10 ){
	   printf("TEST: front passed\n");
   } else{
	   printf("TEST: front failed\n");
   }
   
   if( back(A) == 10 ){
	   printf("TEST: back passed\n");
   } else{
	   printf("TEST: back failed\n");
   }
   
   if( back(B) == 2 ){
	   printf("TEST: back passed\n");
   } else{
	   printf("TEST: back failed\n");
   }
   
   if( get(A) == 1 ){
	   printf("TEST: get passed\n");
   } else{
	   printf("TEST: get failed\n");
   }
   
   moveNext(A);
   moveNext(A);
   
   if( get(A) == 3 ){
	   printf("TEST: get passed\n");
   } else{
	   printf("TEST: get failed\n");
   }
   
   if( equals(A,B) != true ){
	   printf("TEST: equals passed\n");
   } else{
	   printf("TEST: equals failed\n");
   }
   
   
   deleteBack(A);
   List C = copyList(A);
   
   if( equals(A,C) == true ){
	   printf("TEST: equals passed\n");
   } else{
	   printf("TEST: equals failed\n");
   }
   
   
   set(A,7);
   
   
   if( get(A) == 7 ){
	   printf("TEST: set passed\n");
   } else{
	   printf("TEST: set failed\n");
   }
   
   moveNext(A);
   set(A,8);
   
   if( get(A) == 8 ){
	   printf("TEST: set passed\n");
   } else{
	   printf("TEST: set failed\n");
   }
   
   moveFront(A);
   moveFront(B);
   
   if( get(A) == front(A) ){
	   printf("TEST: moveFront passed\n");
   } else{
	   printf("TEST: moveFront failed\n");
   }
   
   if( get(B) == front(B) ){
	   printf("TEST: moveFront passed\n");
   } else{
	   printf("TEST: moveFront failed\n");
   }
   
   moveBack(A);
   moveBack(B);
   
   if( get(A) == back(A) ){
	   printf("TEST: moveBack passed\n");
   } else{
	   printf("TEST: moveBack failed\n");
   }
   
   if( get(B) == back(B) ){
	   printf("TEST: moveBack passed\n");
   } else{
	   printf("TEST: moveBack failed\n");
   }
   
   movePrev(A);
   movePrev(B);
   
   if( get(A) == 9 ){
	   printf("TEST: movePrev passed\n");
   } else{
	   printf("TEST: movePrev failed\n%d\n", get(B));
   }
   
   if( get(B) == 2 ){
	   printf("TEST: movePrev passed\n");
   } else{
	   printf("TEST: movePrev failed\n%d\n", get(B));
   }
   
   moveFront(A);
   moveFront(B);
   
   moveNext(A);
   moveNext(B);
   
   if( get(A) == back(A) ){
	   printf("TEST: moveNext passed\n");
   } else{
	   printf("TEST: moveNext failed\n");
   }
   
   if( get(B) == back(B) ){
	   printf("TEST: moveNext passed\n");
   } else{
	   printf("TEST: moveNext failed\n");
   }
   
   prepend(A,3);
   prepend(B,7);
   
   if( front(A) == 3 ){
	   printf("TEST: prepend passed\n");
   } else{
	   printf("TEST: prepend failed\n");
   }
   
   if( front(B) == 7 ){
	   printf("TEST: prepend passed\n");
   } else{
	   printf("TEST: prepend failed\n");
   }
   
   append(A,3);
   append(B,7);
   
   if( back(A) == 3 ){
	   printf("TEST: append passed\n");
   } else{
	   printf("TEST: append failed\n");
   }
   
   if( back(B) == 7 ){
	   printf("TEST: append passed\n");
   } else{
	   printf("TEST: append failed\n");
   }
   
   moveFront(A);
   moveBack(B);
   
   insertBefore(A,5);
   insertBefore(B,10);
   
   moveFront(A);
   movePrev(B);
   
   if( get(A) == 5 ){
	   printf("TEST: insertBefore passed\n");
   } else{
	   printf("TEST: insertBefore failed\n");
   }
   
   if( get(B) == 10 ){
	   printf("TEST: insertBefore passed\n");
   } else{
	   printf("TEST: insertBefore failed\n");
   }
   
   insertAfter(A,10);
   insertAfter(B,5);
   
   moveNext(A);
   moveNext(B);
   
   if( get(A) == 5 ){
	   printf("TEST: insertAfter passed\n");
   } else{
	   printf("TEST: insertAfter failed\n");
   }
   
   if( get(B) == 10 ){
	   printf("TEST: insertAfter passed\n");
   } else{
	   printf("TEST: insertAfter failed\n");
   }
   
   delete(A);
   delete(B);
   
   if( get(A) == NULL && index(A) == -1 ){
	   printf("TEST: delete passed\n");
   } else{
	   printf("TEST: delete failed\n");
   }
   
   if( get(B) == NULL && index(B) == -1 ){
	   printf("TEST: delete passed\n");
   } else{
	   printf("TEST: delete failed\n");
   }
   
   int tFrontA = front(A);
   int tFrontB = front(B);
   
   deleteFront(A);
   deleteFront(B);
   
   if( front(A) != tFrontA ){
	   printf("TEST: deleteFront passed\n");
   } else{
	   printf("TEST: deleteFront failed\n");
   }
   
   if( front(B) != tFrontB ){
	   printf("TEST: deleteFront passed\n");
   } else{
	   printf("TEST: deleteFront failed\n");
   }
   
   int tBackA = back(A);
   int tBackB = back(B);
   
   deleteBack(A);
   deleteBack(B);
   
   if( back(A) != tBackA ){
	   printf("TEST: deleteFront passed\n");
   } else{
	   printf("TEST: deleteFront failed\n");
   }
   
   if( back(B) != tBackB ){
	   printf("TEST: deleteFront passed\n");
   } else{
	   printf("TEST: deleteFront failed\n");
   }
   
   
   freeList(&A);
   freeList(&B);

   return(0);
}