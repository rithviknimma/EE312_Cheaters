class HashTable{
private:
	struct HashNode{
		string s;
		string file;
		HashNode* next;
	};

	int size;
	HashNode* table[size];

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

