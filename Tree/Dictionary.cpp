#include <iostream>
#include <string>
#include <stack>
#include <cstring>
using namespace std;
#include "Dictionary.h"

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
		if(R != NULL){ //something to copy
			if(R->left != NULL){
				inOrderString(s,R->left);
			}
			//s += R->key +" : " + std::to_string(R->val) + "\n";
			s.append(R->key);
			s.append(" : ");
			s.append(std::to_string(R->val));
			s.append("\n");
			if(R->right != NULL){
				inOrderString(s,R->right);
			}
		}
	}

	// preOrderString() *
	// Appends a string representation of the tree rooted at R to s. The appended
	// string consists of keys only, separated by "\n", with the order determined
	// by a pre-order tree walk.
	void Dictionary::preOrderString(std::string& s, Node* R) const{
		if(R != NULL){ //something to copy
			//s += R->key +"\n";
			s.append(R->key);
			s.append("\n");
			if(R->left != NULL){
				preOrderString(s,R->left);
			}
			if(R->right != NULL){
				preOrderString(s,R->right);
			}
		}
	}

	// preOrderCopy()
	// Recursively inserts a deep copy of the subtree rooted at R into this 
	// Dictionary. Recursion terminates at N.
	void Dictionary::preOrderCopy(Node* R, Node* N){
		if(R != NULL){ //something to copy
			if(N != NULL){
				//if(R->key != N->key && R->val != N->val){
				if(R->key.compare(N->key) != 0 && R->val != N->val){
					setValue(R->key,R->val);
					if(R->left != NULL){
						preOrderCopy(R->left, N);
					}
					if(R->right != NULL){
						preOrderCopy(R->right, N);
					}
				}
			} else{
				setValue(R->key,R->val);
				if(R->left != NULL){
					preOrderCopy(R->left, N);
				}
				if(R->right != NULL){
					preOrderCopy(R->right, N);
				}
			}
			if(R->parent !=NULL){
				R = R->parent;
			}
		}
	}

	// postOrderDelete()
	// Deletes all Nodes in the subtree rooted at R, sets R to nil.
	void Dictionary::postOrderDelete(Node* R){
		if(R != NULL){ //something to delete
			if(R->left != NULL){
				postOrderDelete(R->left);
			}
			if(R->right != NULL){
				postOrderDelete(R->right);
			}
			Node* hold = R;
			if(R->parent != NULL){
				R = R->parent;
			}
			delete hold; 
			hold = NULL;
			num_pairs--;
		}
	}

	// search() *
	// Searches the subtree rooted at R for a Node with key==k. Returns
	// the address of the Node if it exists, returns nil otherwise.
	Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
		if(R == NULL){
			return NULL;
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
		if(R == NULL){ // no node
			return NULL;
		} else if(R->left == NULL){
			return R;
		} else { //
			while (R->left != NULL){ 
				R = R->left;
			}			
		}	
		return R;
	}
	
	// findMax()
	// If the subtree rooted at R is not empty, returns a pointer to the 
	// rightmost Node in that subtree, otherwise returns nil.
	Dictionary::Node* Dictionary::findMax(Node* R){
		if(R == NULL){ // no node
			return NULL;
		} else if(R->right == NULL){
			return R;
		} else { //
			while (R->right!= NULL){ 
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
		   while( p != nil and N == p->right){
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
		   while( p != nil and N == p->left){
				N = p;
				p = p->parent;
		   }
		    return p;
	   }
	}


	// Class Constructors & Destructors ----------------------------------------
   
	// Creates new Dictionary in the empty state. 
	Dictionary::Dictionary(){
		nil = NULL;
		root = NULL;
		current = NULL;
		num_pairs = 0;
	}

	// Copy constructor.
	Dictionary::Dictionary(const Dictionary& D){
		nil = NULL;
		root = NULL;
		current = NULL;
		num_pairs = 0;
		
		Node* R = D.root;
		Node* N = NULL;
		preOrderCopy(R, N);
		
	}

	// Destructor
	Dictionary::~Dictionary(){
		clear();
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
		if(x == NULL){
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
		if(ret == NULL){
			throw std::invalid_argument("Dictionary: getValue(): invalid argument");
		} else{
			return ret->val;
		}
	}

	// hasCurrent() *
	// Returns true if the current iterator is defined, and returns false 
	// otherwise.
	bool Dictionary::hasCurrent() const{
	   if(current != NULL){
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
		nil = NULL;
		root = NULL;
		current = NULL;
		//num_pairs = 0;
	}

	// setValue()
	// If a pair with key==k exists, overwrites the corresponding value with v, 
	// otherwise inserts the new pair (k, v).
	void Dictionary::setValue(keyType k, valType v){
		
		Node* N = new Node(k,v); //z
		Node* temp = NULL; //y
		Node* curr = root; //x
		while(curr != NULL){
			//if(N->key == curr->key){
			//keyType tempK = N->key;
			if( N->key.compare(curr->key) == 0){
				curr->val = N->val;
				num_pairs--;
				break;
			//}else if(N->key < curr->key){
			}else if( N->key.compare(curr->key) < 0){
				temp = curr;
				curr = curr->left;
			//} else if(N->key > curr->key){
			} else if( N->key.compare(curr->key) > 0){
				temp = curr;
				curr = curr->right;
			}
		}
		N->parent = temp;
		if(temp == NULL){
			root = N;
		} else if(N->key.compare(temp->key) < 0){
			temp->left = N;
		} else{
			temp->right = N;
		}
		num_pairs++;
		
  /*
		int done = 0;
		Node* n = new Node(k,v);
		if(num_pairs == 0 && root == NULL){ // first node
			root = n;
			num_pairs++;
		} else { //
			Node* curr = root;
			while (done == 0){ 
				keyType tempK = n->key;
				if(tempK.compare(curr->key) == 0){
					curr->key = tempK;
					curr->val = n->val;
					done = 1;
				} else if(tempK.compare(curr->key) < 0){
					if(curr->left == NULL){
						n->parent = curr;
						curr->left = n;
						done = 1;
						num_pairs++;
					} else {
						curr = curr->left;
					}
				} else if(tempK.compare(curr->key) > 0){
					if(curr->right == NULL){
						n->parent = curr;
						curr->right = n;
						done = 1;
						num_pairs++;
					} else {
						curr = curr->right;
					}
				}
			}
		}*/
	}

	// remove()
	// Deletes the pair for which key==k. If that pair is current, then current
	// becomes undefined.
	// Pre: contains(k).
	void Dictionary::remove(keyType k){
		Node* tempCurr;
		Node* curr;
		//Node* fNode = search(root, k);
		Dictionary* D = new Dictionary();
		//int found = 0;
		//if(contains(k)){
			if(current != NULL){
				//if(current->key == k){
				if(k.compare(current->key) == 0){
					tempCurr = NULL;
				} else{
					tempCurr = current;
				}
			} else{
				tempCurr = NULL;
			}
			//if(fNode != NULL){
				curr = findMin(root);
				while(curr != NULL){
					if(k.compare(curr->key) == 0){ // skip this
					} else {
						D->setValue(curr->key,curr->val);
					}
					curr = findNext(curr);
				}
				//this->clear();
				*this = *D;
				num_pairs = D->num_pairs;
				root = D->root;
				current = tempCurr;
		//	}
		//}
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
		/*if(A.root->val != B.root->val || A.root->key != B.root->key){
			cout << "3\n";
			return false;
		}*/
		Node* bCurr = B.findMin(B.root);
		Node* aCurr = A.findMin(A.root);
		while(bCurr != NULL && aCurr != NULL){
			//if(bCurr->val != aCurr->val || bCurr->key != aCurr->key){
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
		nil = NULL;
		root = NULL;
		current = NULL;
		num_pairs = 0;
		
		Node* R = D.root;
		Node* N = NULL;
		preOrderCopy(R, N);
		
		return *this;
	}