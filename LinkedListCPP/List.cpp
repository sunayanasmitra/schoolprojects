
#include <cstring>
#include "List.h"
#include <iostream>
using namespace std;


	// Class Constructors & Destructors ----------------------------------------
	// Node constructor   
	List::Node::Node(ListElement x){
		data = x;
		next = NULL;
		prev = NULL;
	}
	
	// Creates new List in the empty state.
	List::List(){
		frontDummy = new Node(-1);
		backDummy = new Node(-1);
		frontDummy->next = backDummy;
		frontDummy->prev = NULL;
		backDummy->prev = frontDummy;
		backDummy->next = NULL;
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		pos_cursor = 0;
		num_elements = 0;
	} 

	// Copy constructor.
	List::List(const List& L){
		// make this an empty List
		pos_cursor = 0;
		num_elements = 0;
		
		Node* FN = L.frontDummy->next;
		frontDummy = new Node(-1);
		backDummy = new Node(-1);
		frontDummy->prev = NULL;
		backDummy->next = NULL;
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		while( FN != L.backDummy  ){
			this->insertBefore(FN->data);
			FN = FN->next;
		}	
	}

	// Destructor
	List::~List(){
		Node* FN = frontDummy->next;
	   	while( FN != backDummy ) { 
			Node* hold = FN;
			FN = FN->next;
			delete hold; 
		}
		delete frontDummy;
		delete backDummy;
		frontDummy = NULL;
		backDummy = NULL;
		beforeCursor = NULL;
		afterCursor = NULL;
	}

	// Access functions --------------------------------------------------------

	// length()
	// Returns the length of this List.
	int List::length() const{
		return this->num_elements;
	}

	// front()
	// Returns the front element in this List.
	// pre: length()>0
	ListElement List::front() const{
		if(this->num_elements < 1){
			throw std::length_error("List: front(): empty list");
		}
		//if list size is more than 0 frontDummy->next is a real node
		if(frontDummy->next == backDummy){
			return -2;
		}
		return frontDummy->next->data;
	}

	// back()
	// Returns the back element in this List.
	// pre: length()>0
	ListElement List::back() const{
		if(this->num_elements < 1){
			throw std::length_error("List: front(): empty list");
		}
		//if list size is more than 0 backDummy->prev is a real node
		if(backDummy->prev == frontDummy){
			return -2;
		}
		return backDummy->prev->data;
	}

	// position()
	// Returns the position of cursor in this List: 0 <= position() <= length().
	int List::position() const{
		/*if(num_elements < 1){
			throw std::length_error("List: position(): empty list");
		}	*/	
		if(pos_cursor > num_elements){
			throw std::out_of_range("List: position(): illegal position");
		}
		//if list size is more than 0 and less than length, it is a real node
		return pos_cursor;
	}
	
	// peekNext()
	// Returns the element after the cursor.
	// pre: position()<length()
	ListElement List::peekNext() const{
		if(this->position() >= this->length()){
			throw std::out_of_range("List: peekNext(): illegal position");
		}
		//if list size is more than 0 and less than length, it is a real node
		if(afterCursor == backDummy){
			return -3;
		}
		return afterCursor->data;
	}
	
	// peekPrev()
	// Returns the element before the cursor.
	// pre: position()>0
	ListElement List::peekPrev() const{
		if(this->position() < 1){
			throw std::out_of_range("List: peekPrev(): illegal position");
		}		
		//if list size is more than 0 and less than length, it is a real node
		if(beforeCursor == frontDummy){
			return -3;
		}
	   	return beforeCursor->data;
	}


	// Manipulation procedures -------------------------------------------------

	// clear()
	// Deletes all elements in this List, setting it to the empty state.
	void List::clear(){
	   	Node* FN = frontDummy->next;
	   	while( FN != backDummy ) { 
			Node* hold = FN;
			FN = FN->next;
			delete hold; num_elements--;
		}
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		pos_cursor = 0;
	}

	// moveFront()
	// Moves cursor to position 0 in this List.
	void List::moveFront(){
	    beforeCursor = frontDummy;
		afterCursor = frontDummy->next;// can be backDummy
		pos_cursor = 0;
	}

	// moveBack()
	// Moves cursor to position length() in this List.
	void List::moveBack(){
		afterCursor = backDummy;
	   	beforeCursor = backDummy->prev; //can be frontDummy
		pos_cursor = this->length();
	}

	// moveNext()
	// Advances cursor to next higher position. Returns the List element that
	// was passed over. 
	// pre: position()<length() 
	ListElement List::moveNext(){
	   	if(this->position() >= this->length()){
			throw std::out_of_range("List: moveNext(): illegal position");
		}
		Node* N = afterCursor;
		if(afterCursor->next == backDummy){ //last one already, no room for move
			afterCursor = backDummy;
		} else {	
			afterCursor = afterCursor->next;
		}
		beforeCursor = N; 
		pos_cursor++;
		return N->data;
	}

	// movePrev()
	// Advances cursor to next lower position. Returns the List element that
	// was passed over. 
	// pre: position()>0
	ListElement List::movePrev(){
	   	if(this->position() < 1){
			throw std::out_of_range("List: movePrev(): illegal position");
		}
		Node* N = beforeCursor;
		if( beforeCursor == frontDummy){ //first one already, no room for move
			//beforeCursor = frontDummy;
		} else {
			beforeCursor = beforeCursor->prev;
		}
		afterCursor = N;
		pos_cursor--;
		return N->data;		
	}

	// insertAfter()
	// Inserts x after cursor.
	void List::insertAfter(ListElement x){
		Node* N = new Node(x);
		if(afterCursor == backDummy){
			N->next = backDummy;
			N->prev = beforeCursor;
			backDummy->prev = N;
			beforeCursor->next = N;
			afterCursor = N;
		} else{
			N->next = afterCursor;
			N->prev = beforeCursor;
			afterCursor->prev = N;
			beforeCursor->next = N;
			afterCursor = N;
		}
		
		num_elements++;
		
	}

	// insertBefore()
	// Inserts x before cursor.
	void List::insertBefore(ListElement x){
		Node* N = new Node(x);
		if(beforeCursor == frontDummy){
			N->prev = frontDummy;
			N->next = afterCursor;
			frontDummy->next = N;
			afterCursor->prev = N;
			beforeCursor = N;
		} else{
			N->prev = beforeCursor;
			N->next = afterCursor;
			beforeCursor->next = N;
			afterCursor->prev = N;
			beforeCursor = N;
		}
		pos_cursor++;
		num_elements++;
	}

	// setAfter()
	// Overwrites the List element after the cursor with x.
	// pre: position()<length()
	void List::setAfter(ListElement x){
	   	if(this->position() >= this->length()){
			throw std::out_of_range("List: setAfter(): illegal position");
		}		
	   afterCursor->data = x;
	}

	// setBefore()
	// Overwrites the List element before the cursor with x.
	// pre: position()>0
	void List::setBefore(ListElement x){
	   	if(this->position() < 1){
			throw std::out_of_range("List: setBefore(): illegal position");
		}		
	   beforeCursor->data = x;
	}

	// eraseAfter()
	// Deletes element after cursor.
	// pre: position()<length()
	void List::eraseAfter(){
		if(this->position() >= this->length()){
			throw std::out_of_range("List: eraseAfter(): illegal position");
		}
		if(afterCursor == backDummy){ // nothing can be deleted
			
		} else{
			Node* N = afterCursor;
			beforeCursor->next = afterCursor->next;
			afterCursor->next->prev = beforeCursor;
			afterCursor = afterCursor->next;
			delete N;
			num_elements--;
		}
	}

	// eraseBefore()
	// Deletes element before cursor.
	// pre: position()>0
	void List::eraseBefore(){
	   	if(this->position() < 1){
			throw std::out_of_range("List: eraseBefore(): illegal position");
		}	
	   	if(beforeCursor == frontDummy){ // nothing can be deleted
			
		} else{
			Node* N = beforeCursor;
			afterCursor->prev = beforeCursor->prev;
			beforeCursor->prev->next = afterCursor;
			beforeCursor = beforeCursor->prev;
			delete N;
			pos_cursor--;
			num_elements--;
		}
	}

	// Other Functions ---------------------------------------------------------

	// findNext()
	// Starting from the current cursor position, performs a linear search (in 
	// the direction front-to-back) for the first occurrence of element x. If x
	// is found, places the cursor immediately after the found element, then 
	// returns the final cursor position. If x is not found, places the cursor 
	// at position length(), and returns -1. 
	int List::findNext(ListElement x){
	   	int found = -1;
		int pos = position();
		Node* N = afterCursor;
		
	   	while( N != backDummy && found == -1) { 
			if(N->data == x){
				beforeCursor = N;
				afterCursor = N->next;
				found = 1;
			} else{
				N = N->next;
			}
			pos++;
		}
		if(found == -1){
			this->moveBack();
			return -1;
		} else{
			pos_cursor = pos;
			return pos;
		}
	}

	// findPrev()
	// Starting from the current cursor position, performs a linear search (in 
	// the direction back-to-front) for the first occurrence of element x. If x
	// is found, places the cursor immediately before the found element, then
	// returns the final cursor position. If x is not found, places the cursor 
	// at position 0, and returns -1. 
	int List::findPrev(ListElement x){
	   	int found = -1;
		int pos = position();
		Node* N = beforeCursor;
		
	   	while( N != frontDummy && found == -1) { 
			if(N->data == x){
				afterCursor = N;
				beforeCursor = N->prev;
				found = 1;
			} else{
				N = N->prev; 
			}
			pos--;
		}
		if(found == -1){
			this->moveFront();
			return -1;
		} else{
			pos_cursor = pos;
			return pos;
		}
	}

	// cleanup()
	// Removes any repeated elements in this List, leaving only unique elements.
	// The order of the remaining elements is obtained by retaining the frontmost 
	// occurrance of each element, and removing all other occurances. The cursor 
	// is not moved with respect to the retained elements, i.e. it lies between 
	// the same two retained elements that it did before cleanup() was called.
	void List::cleanup(){
		Node* curr;
		Node* dupCheck;
		int pos = 0;
		Node* N = frontDummy->next;
		int lastPos = position();
		
		while(N != backDummy){
			curr = N;
			dupCheck = curr->next;
			pos++;
			while(dupCheck != backDummy){
				if(N->data == dupCheck->data){
					dupCheck->prev->next = dupCheck->next;
					dupCheck->next->prev = dupCheck->prev;
					if(dupCheck == beforeCursor){
						beforeCursor = beforeCursor->prev;
					} else if(dupCheck == afterCursor){
						afterCursor = afterCursor->next;
					}
					delete dupCheck;
					dupCheck = curr->next;
					num_elements--;
					if(pos < pos_cursor){
						pos_cursor--;
					}
					if(pos < lastPos){
						lastPos--;
					}
				} else {
					curr = curr->next;
					dupCheck = dupCheck->next;
				}
			}
			N = N->next;
		}
		
	}
	
 
	// concat()
	// Returns a new List consisting of the elements of this List, followed by
	// the elements of L. The cursor in the returned List will be at postion 0.
	List List::concat(const List& L) const{
		List J;
		//List K;
		Node* N = frontDummy->next;
		Node* PL = L.frontDummy->next;
		while(N != backDummy){
			J.insertAfter(N->data);
			N = N->next;
		}
		while(PL != L.backDummy){
			J.insertAfter(PL->data);
			PL = PL->next;
		}
		return J;
		
	}

	// to_string()
	// Returns a string representation of this List consisting of a comma 
	// separated sequence of elements, surrounded by parentheses.
	std::string List::to_string() const{
		int cnt = 0;
		Node* N = frontDummy->next;
		std::string s = "";
		
		while( N != backDummy && cnt <= num_elements){
			s += std::to_string(N->data);
			N = N->next;
			if(cnt < num_elements - 1){
				s +=',';
			}
			cnt++;
		}
		return s;
	}

	// equals()
	// Returns true if and only if this List is the same integer sequence as R.
	// The cursors in this List and in R are unchanged.
	bool List::equals(const List& R) const{
		int eq = true;
		int done = 0;
		
		if(num_elements != R.num_elements){ // not same size
			eq = false;
		} else {
			Node* N = frontDummy->next;
			Node* RN = R.frontDummy->next;
			while( N != backDummy && done == 0 ){
				if(N->data != RN->data){
					eq = false;
					done = 1;
				}
				N = N->next;
				RN = RN->next;
			}	
		}
		return eq;
	}


	// Overriden Operators -----------------------------------------------------
   
	// operator<<()
	// Inserts string representation of L into stream.
	std::ostream& operator<<( std::ostream& stream, const List& L ){
		return stream << L.List::to_string();
		/*
	   	Node* N = L.frontDummy->next;
		while( L.frontDummy->next != L.backDummy && cnt < L.num_elements){
			output << N->data;
			if(cnt < L.num_elements - 1){
				output << ',';
			}
			N = N->next;
		}	
        return output;*/
	}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
    bool operator==( const List& A, const List& B ){
		return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ){
	    //this->clear(); // empty list
	   	// make this an empty List
		frontDummy = new Node(-1);
		backDummy = new Node(-1);
		frontDummy->prev = NULL;
		backDummy->next = NULL;
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		
		Node* F = L.frontDummy->next;
		Node* B = L.backDummy;
		while( F != B  ){
			this->insertBefore(F->data);
			F = F->next;
		}
	    return *this; 
   }
   