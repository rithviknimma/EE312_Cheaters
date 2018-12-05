#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>\

using namespace std;

const int MAX_SIZE = 100007;

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

	void addToList(int key, string file){
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
				if(file.compare(head->file) == 0){
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
	const int FAILURE = -1;
	const int SUCCESS = 0;

	HashTable(){
		size = MAX_SIZE;
		table = new HashNode*[size];
		for(int i = 0; i <  size; i++){
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

	int addElement(int key, string file){
		// key cannot be out of bounds of the hash table
		if(key >= size || key < 0){
			return FAILURE;
		}
		addToList(key, file);
		return SUCCESS;
	}

	int hash(string s){
		int hashedValue = 37;
		int wordValue = 0;

		for(int i = 0; i < s.length(); i++){
			if(s[i] == ' '){
				wordValue = 0;
			}

			if((s[i] < 91 && s[i] > 64)){
				s[i] = s[i] + 32;
			}
			
			wordValue += 7^i * s[i];

			hashedValue += wordValue;
		}

		hashedValue = hashedValue % size;

		return hashedValue;
	}

	int getNumNodes(int index) const{
		int numNodes = 0;

		HashNode* ptr = table[index];
		while(ptr != NULL){
			numNodes++;
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
			HashNode* i = table[index];
			
			while(i->next != NULL){
				vec.push_back(i->file);
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

