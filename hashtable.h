#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 860063; 

class HashTable{
	
private:
	struct HashNode{
		int file;
		HashNode* next;
	};
	//size of the table and an unallocated tab;e
	int size;
	HashNode** table;

	void clearMemory();
	//table is a linked list at the nodes, methods to add data at a key
	void addToList(int key, int file){
		//if the list is empty, just add at head
		if(table[key] == NULL){
			HashNode* node = new HashNode;
			node->next = NULL;
			node->file = file;

			table[key] = node;
		}

		else{
			HashNode* head = table[key];
			//keep going until you find a node that points to nothing
			while(head->next != NULL){
				//if you find the same file already at a node, don't add anything new
				if(file == head->file){
					return;
				}
				head = head->next;
			}

			//if the file is unique, then add it
			HashNode* node = new HashNode;
			node->next = NULL;
			node->file = file;

			head->next = node;
		}
	}

public:
	//default, use size MAX_SIZE and every node is null
	HashTable(){
		size = MAX_SIZE;
		table = new HashNode*[size];
		for(int i = 0; i <  size; i++){
			table[i] = NULL;
		}	
	}
	//custom size
	HashTable(int size){
		this->size = size;

		table = new HashNode*[size];
		for(int i = 0; i <  size; i++){
			table[i] = NULL;
		}
	}
	//copy assignment operator for custom table size in PlagiarismCatcher
	HashTable& operator=(const HashTable& rhs){
		if(&rhs == this){
			return *this;
		}
		clearMemory(); // delete current Hashtable

		size = rhs.size;
		HashNode *ptr;
		HashNode *copyPtr;
		for(int i = 0; i < size; i++){
			if(rhs.table[i] != NULL){
				copyPtr = rhs.table[i];
				ptr = new HashNode;
				ptr->file = copyPtr->file;

				while(copyPtr->next != NULL){
					ptr->next = new HashNode;
					(ptr->next)->file = (copyPtr->next)->file;
					ptr = ptr->next;
					copyPtr = copyPtr->next;
				}
				ptr->next = copyPtr->next;
			}
			else{
				// copy null 
				table[i] = NULL;
			}			
		}

		return *this;
	}

	int getSize() const{
		return size;
	}
	//add an element at a key
	int addElement(int key, int file){
		if(key < size && key > 0)
			addToList(key, file);
	}
	//hashing function
	int hash(string s){
		//use long int to prevent overflow early
		unsigned long int hashedValue = 0;
		unsigned long int wordValue = 0;
		int j = 0;
		for(int i = 0; i < s.length(); i++){
			//spaces are the breaks between words
			if(s[i] == ' '){
				hashedValue += wordValue;
				j = 0;
				wordValue = 0;
			}

			//the letters in each word will be multiplied by powers of 7
			//the resulting word value is added to the hashedValue

			//if the letter is lower case, treat it as uppercase
			if((s[i] <= 'z' && s[i] >= 'a')){
				wordValue += pow(7,j) * (s[i] - 32);
				j++;
			}
			//all uppercase letters, numbers, and apostrophes will be considered as well
			else if((s[i] <= 'Z' && s[i] >= 'A') || (s[i] <= '9' && s[i] >= '0') || (s[i] == '\'')){
				wordValue += pow(7,j) * s[i];
				j++;
			}
		}
		//if there is overflow, then we might get a negative number
		//just multiply by -1 to get a positive number
		if(hashedValue < 0)
			hashedValue *= -1;
		//the key cannot be greater than the size
		hashedValue = hashedValue % size;
		//return the value (the cast will not have issues since size < MAX_INT)
		return (int) hashedValue;
	}
	//this will return a vector of all the files that collided at a certain key
	vector<int> getCollisionsAt(int index){
		vector<int> vec;
		//no entries. no collisions
		if(table[index] == NULL){
			return vec;
		}
		//one entry, no collisions
		else if((table[index])->next == NULL){
			return vec;
		}
		//2 or more entries need to be checked
		else{
			HashNode* i = table[index];
			//fill the vector with file names that collided
			while(i != NULL){
				vec.push_back(i->file);
				i = i->next;
			}
		}
		return vec;
	}

	~HashTable();
};

HashTable::~HashTable(){
	//delete all data in the lists
	clearMemory();
	//and delete the table that was allocated
	delete[] table;
}

void HashTable::clearMemory(){
	HashNode *ptr;
	HashNode *trail;
	//cout << "clears Memory";
	for(int i = 0; i < MAX_SIZE; i++){
		if(table[i] != NULL){
			ptr = table[i];
			trail = ptr;
			// delete all nodes until you reach NULL ptr
			while(ptr != NULL){
				ptr = trail->next;
				delete trail;
				trail = ptr;
			}
			delete trail;

			table[i] = NULL;  //head pointer set to null to show that the list is empty
		}
	}
}