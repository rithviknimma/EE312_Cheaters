#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

const int MAX_SIZE = 50000;

class HashTable{

public:
	struct HashNode{
		string file;
		HashNode* next;
	};

private:
	int size;
	HashNode** table;

	void clearMemory();

	void deleteList(HashNode* head);

	void addToList(HashNode* head, string file){
		//if the list is empty, just add at head
		if(head == NULL){
			HashNode* node = new HashNode;
			node->next = NULL;
			node->file = file;

			head = node;
		}

		else{
			HashNode *ptr = head;
			//keep going until you find a node that points to nothing
			while(ptr->next != NULL){
				//if you find the same file already at a node, don't add anything new
				if(file.compare(ptr->file) == 0){
					return;
				}
				ptr = ptr->next;
			}

			//if the file is unique, then add it
			HashNode* node = new HashNode;
			node->next = NULL;
			node->file = file;

			ptr->next = node;
		}
	}

public:
	const int FAILURE = -1;
	const int SUCCESS = 0;

	HashTable(){
		size = MAX_SIZE;
		table = new HashNode*[size];

		for(int i = 0; i < size; i++){
			table[i] = NULL;
		}	
	}

	HashTable(int size){
		this->size = size;

		table = new HashNode*[size];
		for(int i = 0; i <  size; i++){
			table[i] = NULL;
		}
	}

	HashTable& operator=(const HashTable& rhs){
		// if(&rhs == this){
		// 	return *this;
		// }
		// clearMemory(); // delete current Hashtable

		// size = rhs.size;
		// HashNode *ptr;
		// HashNode *copyPtr;
		// for(int i = 0; i < size; i++){
		// 	if(rhs.table[i] != NULL){
		// 		copyPtr = rhs.table[i];
		// 		ptr = new HashNode;
		// 		ptr->file = copyPtr->file;
		// 		ptr->next = copyPtr->next;
		// 		this->table[i] = ptr;

		// 		copyPtr = copyPtr->next;

		// 		while(copyPtr != NULL){
		// 			ptr = new HashNode;
		// 			ptr->file = copyPtr->file;
		// 			ptr->next = copyPtr->next;

		// 			copyPtr = copyPtr->next;
		// 		}
		// 		// ptr->next = copyPtr->next;
		// 	}
		// 	else{
		// 		this->table[i] = NULL;
		// 	}			
		// }

		// return *this;

		//delete all things in the table
		// clearMemory();
		// //then delete the pointer at the table
		// delete table;
		// //set the size of the table
		// size = rhs.size;
		// table = new HashNode*[size];

		// for(int i = 0; i < size; i++){
		// 	HashNode* node = new HashNode;
		// 	node->file = rhs[i]->file;
		// 	table[i] = node;

		// 	HashNode* ptr = rhs[i]->next;
		// 	while(ptr != NULL){

		// 		HashNode* newNode = new HashNode;
		// 		node->file = ptr->file;
		// 		node->next = ptr->next;


		// 	}


		// }


	}

	int getSize() const{
		return size;
	}

	int addElement(int key, string file){
		if(key >= size){
			return FAILURE;
		}

		addToList(table[key], file);
		return SUCCESS;
	}

	int hash(vector<string> s){
		int hashedValue = 0;
		int wordValue;
		string word;

		for(int i = 0; i < s.size(); i++){
			wordValue = 0;
			word = s[i];
			for(int j = 0; j < word.size(); j++){
				//change upper case to lower case
				if((word[j] < 91 && word[j] > 64)){
					word[j] = word[j] + 32;
				}
				//only if the letter is not lower case o
				else if(!(word[j] < 123 && word[j] > 96) && !(word[j] < 58 && word[j] > 47) && !(word[j] == 39)){
					word.erase(word.begin() + j);
				}
			}

			for(int j = 0; j < word.size(); j++){
				wordValue += 37^(word.size() - 1 - j) * word[j];
			}


			hashedValue += wordValue^2;
		}

		hashedValue = hashedValue % size;

		cout << hashedValue << endl;

		return hashedValue;
		
	}

	int getNumNodes(int index){
		int numNodes = 0;

		HashNode* ptr = table[index];
		while(ptr != NULL){
			numNodes++;
			ptr = ptr->next;
		}

		return numNodes;
	}

	vector<string> getCollisionsAt(int index){
		vector<string> vec;

		if(getNumNodes(index) < 2){
			vec.push_back("");
			return vec;
		}
		else{
			cout << "Collision found" << endl;
			HashNode* i = table[index];
			
			while(i->next != NULL){
				vec.push_back(i->file);
				i = i->next;
			}
		}

		return vec;
	}

	HashNode* operator[](int i){
		return table[i];
	}

	HashNode** getTable(){
		return table;
	}

	~HashTable();
};

HashTable::~HashTable(){
	clearMemory();
}

// void HashTable::clearMemory(){
// 	HashNode *ptr;
// 	HashNode *trail;

// 	for(int i = 0; i < MAX_SIZE; i++){
// 		if(table[i] != NULL){
// 			ptr = table[i];
// 			trail = ptr;
// 			// delete all nodes until you reach NULL ptr
// 			while(ptr != NULL){
// 				ptr = trail->next;
// 				delete trail;
// 				trail = ptr;
// 			}
// 			delete trail;

// 			table[i] = NULL;  //head pointer set to null to show that the list is empty
// 		}
// 	}
// }

void HashTable::clearMemory(){
	for(int i = 0; i < size; i++){
		deleteList(table[size]);
	}
}

void HashTable::deleteList(HashNode* ptr){
	if(ptr != NULL){
		deleteList(ptr->next);
		delete ptr;	
	}
}

