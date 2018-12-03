#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 10007;

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

	void addToList(HashNode* head, string file){
		//if the list is empty, just add at head
		if(head == NULL){
			HashNode* node = new HashNode;
			node->next = NULL;
			node->file = file;

			head = node;
		}

		else{
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
				table[i] = NULL;
			}			
		}

		return *this;
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
				//only if the letter is lower case or an apostrophe
				if((word[j] < 123 && word[j] > 96) || word[j] == 39){
					wordValue += 3^(word.size() - j - 1) * word[j];
				}
			}

			hashedValue += 7^(s.size() - 1 - i) * wordValue;
		}

		return hashedValue % size;
		
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
	}

	HashNode* operator[](int i){
		return table[i];
	}

	~HashTable();
};

HashTable::~HashTable(){
	clearMemory();
}

void HashTable::clearMemory(){
	HashNode *ptr;
	HashNode *trail;

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

