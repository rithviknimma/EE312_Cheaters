#include <vector>
#include <string>
using namespace std;

class HashTable{
private:
	struct HashNode{
		string s;
		string file;
		HashNode* next;
	};

	const static int MAX_SIZE = 10000;
	HashNode* table[MAX_SIZE];

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
		// size = 0;
		// table[size] = new HashNode;

	}

	HashTable(int size){
		// this->size = size;

		// for(int i = 0; i <  size; i++){
		// 	table[i] = NULL;
		// }
	}

	int getSize() const{
		return MAX_SIZE;
	}

	int addElement(int key, string file, string s){
		if(key >= MAX_SIZE){
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

