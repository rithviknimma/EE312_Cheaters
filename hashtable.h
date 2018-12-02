class HashTable{
private:
	struct HashNode{
		string s;
		HashNode* next;
	};

	int size;
	HashNode* table[size];

	void addToList(HashNode* head, string s);

public:
	const int FAILURE = -1;
	const int SUCCESS = 0;

	HashTable(){
		size = 0;
	}

	HashTable(int size){
		this->size = size;

		for(int i = 0; i <  size; i++){
			table[i] = NULL;
		}
	}

	int getSize() const{
		return size;
	}

	int addElement(int key, string s);
};