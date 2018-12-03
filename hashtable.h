#include <vector>
#include <string>
#include <cstdlib>

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
		const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227};

		int numPrimes = 50;

		srand(numPrimes);

		int hashedValue = rand();
		int wordValue;
		string word;

		for(int i = 0; i < s.size(); i++){
			wordValue = 0;
			word = s[i];
			for(int j = 0; j < word.size(); j++){
				wordValue += (primes[rand()%50] * j) - word[j];
			}

			hashedValue += (primes[rand()%50] * i) + wordValue;
		}

		return hashedValue % size;
		
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

