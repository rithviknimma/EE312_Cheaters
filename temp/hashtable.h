#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class HashTable{
private:
	struct HashNode{
		string s;
		string file;
		HashNode* next;
	};

	int size;
	HashNode** table;

	void addToList(HashNode* head, string file, string s){
		//create the new node
		HashNode* node = new HashNode;
		node->next = NULL;
		node->s = s;
		node->file = file;
		//if the head is NULL, then this is the first node
		if(head == NULL){
			head = node;
		}
		//otherwise, add it to the first empty position
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
		size = 0;
		table = NULL;
	}

	HashTable(int size){
		this->size = size;

		table = new HashNode*[size];

		for(int i = 0; i < size; i++){
			table[i] = NULL;
		}
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

	int hash(string s){
		//some algo
	}

	~HashTable();
};

