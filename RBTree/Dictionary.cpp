
#include <iostream>
#include <string>
#include <stack>
#include <cstring>
using namespace std;
#include "Dictionary.h"

#define BLACK -1
#define RED 1

	// Helper Functions (Optional) ---------------------------------------------
	// Node constructor   
	Dictionary::Node::Node(keyType k, valType v){
		key = k;
		val = v;
		parent = NULL;
		left = NULL;
		right = NULL;	
	}
	
	// inOrderString() *
	// Appends a string representation of the tree rooted at R to string s. The
	// string appended consists of: "key : value \n" for each key-value pair in
	// tree R, arranged in order by keys.
	void Dictionary::inOrderString(std::string& s, Node* R) const{
		if(R->key.compare(nil->key) != 0){ //something to copy
				inOrderString(s,R->left);
			s.append(R->key);
			s.append(" : ");
			s.append(std::to_string(R->val));
			s.append("\n");
			inOrderString(s,R->right);
		}
	}

	// preOrderString() *
	// Appends a string representation of the tree rooted at R to s. The appended
	// string consists of keys only, separated by "\n", with the order determined
	// by a pre-order tree walk.
	void Dictionary::preOrderString(std::string& s, Node* R) const{
		if(R->key.compare(nil->key) != 0){ //something to copy
			//s += R->key +"\n";
			s.append(R->key);
			s.append("\n");
			//if(R->left != NULL){
				preOrderString(s,R->left);
			//}
			//if(R->right != NULL){
				preOrderString(s,R->right);
			//}
		}
	}

	// preOrderCopy()
	// Recursively inserts a deep copy of the subtree rooted at R into this 
	// Dictionary. Recursion terminates at N.
	void Dictionary::preOrderCopy(Node* R, Node* N){
		if(R->key.compare(nil->key) != 0){ //something to copy
			if(N->key.compare(nil->key) != 0){
				if(R->key.compare(N->key) != 0){ //&& R->val != N->val){
					setValue(R->key,R->val);
					if(R->left->key.compare(nil->key) != 0){
						preOrderCopy(R->left, N);
					}
					if(R->right->key.compare(nil->key) != 0){
						preOrderCopy(R->right, N);
					}
				}
			} 
			if(R->parent != nil){
				R = R->parent;
			}
		}
	}

	// postOrderDelete()
	// Deletes all Nodes in the subtree rooted at R, sets R to nil.
	void Dictionary::postOrderDelete(Node* R){
		if(R->key.compare(nil->key) != 0){ //something to delete
			if(R->left->key.compare(nil->key) != 0){
				postOrderDelete(R->left);
			}
			if(R->right->key.compare(nil->key) != 0){
				postOrderDelete(R->right);
			}
			Node* hold = R;
			if(R->parent->key.compare(nil->key) != 0){
				R = R->parent;
			}
			delete hold; 
			hold = nil;
			num_pairs--;
		}
	}

	void Dictionary::LeftRotate(Node* N){
		Node* y = N->right; // set y
		N->right = y->left;  // turn y's left subtree into x's right subtree
		if(y->left != nil){     // not necessary if using sentinal nil node
			y->left->parent = N;
		}
		y->parent = N->parent; // link y's parent to x
		if(N->parent == nil){
			root = y;
		} else if(N == N->parent->left){
			N->parent->left = y;
		} else {
			N->parent->right = y;
		}
		y->left = N; // put x on y's left
		N->parent = y;
	}

	void Dictionary::RightRotate(Node* N){
		Node* y = N->left; // set y
		N->left = y->right; // turn y's right subtree into x's left subtree
		if(y->right != nil){  // not necessary if using sentinal nil node
			y->right->parent = N;
		}
		y->parent = N->parent; // link y's parent to x
		if(N->parent == nil){
			root = y;
		} else if(N == N->parent->right){
			N->parent->right = y;
		} else {
			N->parent->left = y;
		}
		y->right = N; // put x on y's right
		N->parent = y;
	}
	
	void Dictionary::insertNode(Node* R) {

	}	
	
	void Dictionary::RB_InsertFixUp(Node* N) {
		Node* y;
		//if(N->parent != NULL){
		while(N->parent->color == RED){
			//if(N->parent->parent != NULL){
			if(N->parent == N->parent->parent->left){
				y = N->parent->parent->right;
				if(y->color == RED){
					N->parent->color = BLACK;              // case 1
					y->color = BLACK;                     // case 1
					N->parent->parent->color = RED;         // case 1
					N = N->parent->parent;                 // case 1
				} else {
					if(N == N->parent->right){
					   N = N->parent;                     // case 2
					   LeftRotate(N);                 // case 2
					}
					N->parent->color = BLACK;              // case 3
					N->parent->parent->color = RED;         // case 3
					RightRotate(N->parent->parent);     // case 3
				}
			} else {
				y = N->parent->parent->left;
				if(y->color == RED){
					N->parent->color = BLACK;              // case 4
					y->color = BLACK;                     // case 4
					N->parent->parent->color = RED;         // case 4
					N = N->parent->parent;                 // case 4
				} else {
					if(N == N->parent->left){
					   N = N->parent;                     // case 5
					   RightRotate(N);                // case 5
					}
					N->parent->color = BLACK;              // case 6
					N->parent->parent->color = RED;         // case 6
					LeftRotate(N->parent->parent);     // case 6
				}
			}
		}
		root->color = BLACK;
	}
	
	void Dictionary::RB_Transplant(Node* u,Node* v) {
		if(u->parent == nil){
			root = v;
		} else if(u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
		
	}
	
	void Dictionary::RB_Delete(Node* N) {
	
	}
	
	void Dictionary::RB_DeleteFixUp(Node* N) {
		Node* w;
		while(N != root && N->color == BLACK){
			if(N == N->parent->left){
				w = N->parent->right;
				if(w->color == RED){
					w->color = BLACK;                        // case 1
					N->parent->color = RED;                   // case 1
					LeftRotate(N->parent);                // case 1
					w = N->parent->right;   				// case 1
				}					
				if(w->left->color == BLACK && w->right->color == BLACK){
					w->color = RED;                          // case 2
					N = N->parent;                           // case 2
				} else {
					if(w->right->color == BLACK){
					   w->left->color = BLACK;                // case 3
					   w->color = RED;                       // case 3
					   RightRotate(w);                   // case 3
					   w = N->parent->right;                  // case 3
					}
					w->color = N->parent->color;               // case 4
					N->parent->color = BLACK;                 // case 4
					w->right->color = BLACK ;                 // case 4
					LeftRotate(N->parent);                // case 4
					N = root;								// case 4
				}					
			} else {
				w = N->parent->left;
				if(w->color == RED){
					w->color = BLACK;                        // case 5
					N->parent->color = RED;                   // case 5
					RightRotate(N->parent);               // case 5
					w = N->parent->left;  					// case 5
				}                    
				if(w->right->color == BLACK && w->left->color == BLACK){
					w->color = RED;                          // case 6
					N = N->parent;                           // case 6
				} else {
					if(w->left->color == BLACK){
					   w->right->color = BLACK;               // case 7
					   w->color = RED;                       // case 7
					   LeftRotate(w);                    // case 7
					   w = N->parent->left;                   // case 7
					}
					w->color = N->parent->color;               // case 8
					N->parent->color = BLACK;                 // case 8
					w->left->color = BLACK;                   // case 8
					RightRotate(N->parent);               // case 8
					N = root;								// case 8
				}
		    }					
		}
		N->color = BLACK;		
	}
	
	// search() *
	// Searches the subtree rooted at R for a Node with key==k. Returns
	// the address of the Node if it exists, returns nil otherwise.
	Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
		if(R == nil){
			return nil;
		} else if(k.compare(R->key) == 0){
			return R;
		} else if(k.compare(R->key) < 0){
			return search(R->left,k);
		} else{
			return search(R->right,k);
		}	   
	}
	

	// findMin()
	// If the subtree rooted at R is not empty, returns a pointer to the 
	// leftmost Node in that subtree, otherwise returns nil.
	Dictionary::Node* Dictionary::findMin(Node* R){
		if(R == nil){ // no node
			return nil;
		} else if(R->left == nil){
			return R;
		} else { //
			while (R->left != nil){ 
				R = R->left;
			}			
		}	
		return R;
	}
	
	// findMax()
	// If the subtree rooted at R is not empty, returns a pointer to the 
	// rightmost Node in that subtree, otherwise returns nil.
	Dictionary::Node* Dictionary::findMax(Node* R){
		if(R == nil){ // no node
			return nil;
		} else if(R->right == nil){
			return R;
		} else { //
			while (R->right!= nil){ 
				R = R->right;
			}			
		}	
		return R;	   	   
	}

	// findNext()
	// If N does not point to the rightmost Node, returns a pointer to the
	// Node after N in an in-order tree walk.  If N points to the rightmost 
	// Node, or is nil, returns nil. 
	Dictionary::Node* Dictionary::findNext(Node* N){
	   if(N->right != nil){
		  return findMin(N->right);
	   } else {
		   Node* p = N->parent;
		   while( p != nil && N == p->right){
				N = p;
				p = p->parent;
		   }
		   return p;
	   }   
	}

	// findPrev()
	// If N does not point to the leftmost Node, returns a pointer to the
	// Node before N in an in-order tree walk.  If N points to the leftmost 
	// Node, or is nil, returns nil.
	Dictionary::Node* Dictionary::findPrev(Node* N){
	   if(N->left != nil){
		  return findMax(N->left);
	   } else {
		   Node* p = N->parent;
		   while( p != nil && N == p->left){
				N = p;
				p = p->parent;
		   }
		    return p;
	   }
	}

	// Class Constructors & Destructors ----------------------------------------
   
	// Creates new Dictionary in the empty state. 
	Dictionary::Dictionary(){
		nil = new Node("", -58);
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil;
		current = nil;
		num_pairs = 0;
	}

	// Copy constructor.
	Dictionary::Dictionary(const Dictionary& D){
		nil = new Node("", -58);
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil;
		current = nil;
		num_pairs = 0;
		
		Node* R = D.root;
		Node* N = nil;
		preOrderCopy(R, N);
		
	}

	// Destructor
	Dictionary::~Dictionary(){
		clear();
		delete nil;
		nil = NULL;
		root = NULL;
		current = NULL;
		num_pairs = 0;
	}


	// Access functions --------------------------------------------------------

	// size()
	// Returns the size of this Dictionary.
	int Dictionary::size() const{
	   return num_pairs;
	}

	// contains() *
	// Returns true if there exists a pair such that key==k, and returns false
	// otherwise.
	bool Dictionary::contains(keyType k) const{
		Node* x = search(root, k);
		if(x == nil){
			return false;
		} else{
			return true;
		}
	}

	// getValue() *
	// Returns a reference to the value corresponding to key k.
	// Pre: contains(k)
	valType& Dictionary::getValue(keyType k) const{
		Node* ret = search(root,k);
		if(ret == nil){
			throw std::invalid_argument("Dictionary: getValue(): invalid argument");
		} else{
			return ret->val;
		}
	}

	// hasCurrent() *
	// Returns true if the current iterator is defined, and returns false 
	// otherwise.
	bool Dictionary::hasCurrent() const{
	   if(current != nil){
		   return true;
	   }
	   return false;
	}

	// currentKey() *
	// Returns the current key.
	// Pre: hasCurrent() 
	keyType Dictionary::currentKey() const{
		if(hasCurrent() == false){
			throw std::invalid_argument("Dictionary: currentKey(): invalid argument");
		}
		return current->key;
	}

	// currentVal() *
	// Returns a reference to the current value.
	// Pre: hasCurrent()
	valType& Dictionary::currentVal() const{
		if(hasCurrent() == false){
			throw std::invalid_argument("Dictionary: currentVal(): invalid argument");
		}		
		return current->val;
	}


	// Manipulation procedures -------------------------------------------------

	// clear()
	// Resets this Dictionary to the empty state, containing no pairs.
	void Dictionary::clear(){
		postOrderDelete(root);
		//nil = NULL;
		root = nil;
		current = nil;
		//num_pairs = 0;
	}

	// setValue()
	// If a pair with key==k exists, overwrites the corresponding value with v, 
	// otherwise inserts the new pair (k, v).
	void Dictionary::setValue(keyType k, valType v){
		//cout << "here0\n";
		Node* R = new Node(k,v);
		Node* y = nil;
		Node* x = root;
		while(x->key.compare(nil->key) != 0){
			y = x;
			int temp = R->key.compare(x->key);
			if(temp == 0){
				x->val = R->val;
				num_pairs--;
				break;
			} else if(temp < 0){
				x = x->left;
			} else {
				x = x->right;
			}
		}
		R->parent = y;
		if(y->key.compare(nil->key) == 0){
			root = R;
		} else if(R->key.compare(y->key) < 0){
			y->left = R;
		} else {
			y->right = R;
		}
		R->left = nil;
		R->right = nil;
		R->color = RED;
		RB_InsertFixUp(R);
		num_pairs++;
	}

	// remove()
	// Deletes the pair for which key==k. If that pair is current, then current
	// becomes undefined.
	// Pre: contains(k).
	void Dictionary::remove(keyType k){
		Node* N = search(root, k);
		Node* y = N;
		Node* x;
		int y_original_color = y->color;
		if(current->key.compare(k) == 0){
			current = nil;
		}
		if(N->left == nil){
			x = N->right;
			RB_Transplant(N, N->right);
		} else if(N->right == nil){
			x = N->left;
			RB_Transplant(N, N->left);
		} else {
			y = findMin(N->right);
			y_original_color = y->color;
			x = y->right;
			if(y->parent == N){
				x->parent = y;
			} else { 
				RB_Transplant(y, y->right);
				y->right = N->right;
				y->right->parent = y;
			}
			RB_Transplant(N, y);
			y->left = N->left;
			y->left->parent = y;
			y->color = N->color;
		}
		if(y_original_color == BLACK){
			RB_DeleteFixUp(x);
		}
		delete N;
		num_pairs--;		
	}

	// begin()
	// If non-empty, places current iterator at the first (key, value) pair
	// (as defined by the order operator < on keys), otherwise does nothing. 
	void Dictionary::begin(){
	    current = findMin(root);
	}

	// end()
	// If non-empty, places current iterator at the last (key, value) pair
	// (as defined by the order operator < on keys), otherwise does nothing. 
	void Dictionary::end(){
	    current = findMax(root);	   
	}

	// next()
	// If the current iterator is not at the last pair, advances current 
	// to the next pair (as defined by the order operator < on keys). If 
	// the current iterator is at the last pair, makes current undefined.
	// Pre: hasCurrent()
	void Dictionary::next(){
		if(hasCurrent()){
			current = findNext(current);
		}
	}

	// prev()
	// If the current iterator is not at the first pair, moves current to  
	// the previous pair (as defined by the order operator < on keys). If 
	// the current iterator is at the first pair, makes current undefined.
	// Pre: hasCurrent()
	void Dictionary::prev(){
	   	if(hasCurrent()){
			current = findPrev(current);
		}	
	}


	// Other Functions ---------------------------------------------------------

	// to_string() *
	// Returns a string representation of this Dictionary. Consecutive (key, value)
	// pairs are separated by a newline "\n" character, and the items key and value 
	// are separated by the sequence space-colon-space " : ". The pairs are arranged 
	// in order, as defined by the order operator <.
	std::string Dictionary::to_string() const{
		std::string s;
		inOrderString(s,root);
		return s;	
	}

	// pre_string() *
	// Returns a string consisting of all keys in this Dictionary. Consecutive
	// keys are separated by newline "\n" characters. The key order is given
	// by a pre-order tree walk.
	std::string Dictionary::pre_string() const{
		std::string s;
		preOrderString(s,root);
		return s;
	}

	// equals()
	// Returns true if and only if this Dictionary contains the same (key, value)
	// pairs as Dictionary D.
	bool Dictionary::equals(const Dictionary& D) const{ 
		Dictionary A = *this;
		Dictionary B = D;
		
		if(A.num_pairs != B.num_pairs){
			return false;
		}
		if(A.num_pairs == 0 && B.num_pairs == 0){
			return true;
		}
		Node* bCurr = B.findMin(B.root);
		Node* aCurr = A.findMin(A.root);
		while(bCurr != nil && aCurr != nil){
			if(bCurr->val != aCurr->val || bCurr->key.compare(aCurr->key) != 0){
				return false;
			}
			bCurr = B.findNext(bCurr);
			aCurr = A.findNext(aCurr);
		}
		return true;
	}


	// Overloaded Operators ----------------------------------------------------
   
	// operator<<()
	// Inserts string representation of Dictionary D into stream, as defined by
	// member function to_string().
	std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	   return stream << D.Dictionary::to_string();
	}

	// operator==()
	// Returns true if and only if Dictionary A equals Dictionary B, as defined
	// by member function equals(). 
	bool operator==( const Dictionary& A, const Dictionary& B ){
	   return A.equals(B);
	}

	// operator=()
	// Overwrites the state of this Dictionary with state of D, and returns a
	// reference to this Dictionary.
	Dictionary& Dictionary::operator=( const Dictionary& D ){
		nil = new Node("", -58);
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil;
		current = nil;
		num_pairs = 0;		
		Node* R = D.root;
		Node* N = nil;
		preOrderCopy(R, N);
		return *this;
	}
	