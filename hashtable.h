#include <vector>
#include <string>
using namespace std;

const int MAX_SIZE = 10000;

class HashTable{
private:
	struct HashNode{
		string s;
		string file;
		HashNode* next;
	};

	
	// HashNode* table[MAX_SIZE];


	int size;
	HashNode** table;

	void clearMemory();

	void addToList(HashNode* head, string file, string s){
		HashNode* node = new HashNode;
		node->next = NULL;
		node->s = s;
		node->file = file;

		if(head == NULL){
			head = node;
		}

		else{
			while(head->next != NULL){
				head = head->next;
			}
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
				ptr->s = copyPtr->s;
				ptr->file = copyPtr->file;

				while(copyPtr->next != NULL){
					ptr->next = new HashNode;
					(ptr->next)->s = (copyPtr->next)->s;
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

	int addElement(int key, string file, string s){
		if(key >= size){
			return FAILURE;
		}

		addToList(table[key], file, s);
		return SUCCESS;
	}

	int hash(vector<string> s){
		//some algo
		return 0;
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

