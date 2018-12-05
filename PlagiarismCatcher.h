/* plagiarism.h

  Name: Rithvik Baddam
  UT eid: rrb2442

  Name: Arul Saraf
  UT eid: as75789
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "hashtable.h"
using namespace std;

class PlagiarismCatcher{
private:

	int n;

	HashTable table;
	vector<string> files;

	// string getNextWord(string s, int& pos);
	string vectorToString(const vector<string>& vec); 
	int getFileIndex(string s);

public:
	PlagiarismCatcher(){
		n = 0;
	}

	PlagiarismCatcher(int n){
		this->n = n;
	}

	PlagiarismCatcher(int n, vector<string>& dir){
		this->n = n;

		files = dir;
	}

	PlagiarismCatcher(int n, int tableSize){
		this->n = n;
		table = *(new HashTable(tableSize));
	}

	void setFiles(vector<string>& s);
	void generateHashtable();
	vector<string> findCollisions(int thershold);

	~PlagiarismCatcher();
};

void PlagiarismCatcher::setFiles(vector<string>& dir){
	files = dir;
}

string PlagiarismCatcher::vectorToString(const vector<string>& vec){
	string s = "";
	for(int  i = 0; i < vec.size(); i++){
		s.append(vec[i]);
		s.append(" ");
	}
	return s;
}

void PlagiarismCatcher::generateHashtable(){
	for(int i = 0; i < files.size(); i++){
		ifstream myFile(files[i]);

		if(myFile.is_open()){
			vector<string> vec;
			string buf;

			myFile >> buf;

			while(myFile){		
				//push the words into the vector
				vec.push_back(buf);
				//when the vector is "full"
				//get the n word sequence and delete the first word
				if(vec.size() == n){
					table.addElement(table.hash(vectorToString(vec)), i);
					vec.erase(vec.begin());
				}	

				myFile >> buf;
			}

			myFile.close();
		}

	}
}

vector<string> PlagiarismCatcher::findCollisions(int threshold){
	vector<string> colls;

	int collisions[files.size()][files.size()];

	for(int i = 0; i < files.size(); i++){
		for(int j = 0; j < files.size(); j++){
			collisions[i][j] = 0;
		}
	}

	vector<int> vec;

	for(int i = 0; i < table.getSize(); i++){
		vec = table.getCollisionsAt(i);

		if(vec.size() > 0){
			for(int j = 0; j < vec.size() - 1; j++){
				for(int k = j+1; k < vec.size(); k++){
					collisions[vec[k]][vec[j]]++;
					collisions[vec[j]][vec[k]]++;
				}
			}
		}
	}
	string s;
	for(int i = 1; i < files.size(); i++){
		for(int j = 0; j < i; j++){
			if(collisions[i][j] > threshold){
				s = "";
				s.append(to_string(collisions[i][j]));
				s.append(": ");
				s.append(files[i]);
				s.append(", ");
				s.append(files[j]);

				colls.push_back(s);
			}
		}
	}

	return colls;
}

// void PlagiarismCatcher::findCollisions(int threshold){
// 	int collisions[numFiles][numFiles];
// 	for(int i = 0; i < numFiles; i++){
// 		for(int j = 0; j < numFiles; j++){
// 			collisions[i][j] = 0;
// 		}
// 	}

// 	HashTable::HashNode** hashTable = table.getTable();
// 	HashTable::HashNode* ptr;
// 	HashTable::HashNode* inside;

// 	// for(int i = 0; i < table->getSize(); i++){
// 	// 	ptr = hashTable[i];
// 	// 	if(ptr != NULL){
// 	// 		cout << "works" << endl;
// 	// 	}
// 	// }

	
// 	for(int i = 0; i < table.getSize(); i++){
// 		ptr = hashTable[i];
// 		if(ptr != NULL) {
// 			if (ptr->next != NULL){
// 				while(ptr != NULL){
// 					inside = ptr->next;
// 					while(inside != NULL){
// 						// get index from vector
// 						collisions[getFileIndex(ptr->file)][getFileIndex(inside->file)]++;
// 						collisions[getFileIndex(inside->file)][getFileIndex(ptr->file)]++;
// 						inside = inside->next;
// 					}		
// 					ptr = ptr->next;		
// 				}
// 			}
// 		}
// 	}


// 	for(int i = 1; i < numFiles; i++){
// 		for(int j = 0; j < i; j++){
// 			if(collisions[i][j] > threshold){
// 				cout << collisions[i][j] << ": ";
// 				cout << files[i] << ", " ;
// 				cout << files[j];
// 				cout << endl;
// 			}
// 		}
// 	}
// }

// int PlagiarismCatcher::getFileIndex(string s){
// 	int i = 0;
// 	while(files[i].compare(s) && i < files.size()){
// 		i++;
// 	}
// 	return i;
// }

PlagiarismCatcher::~PlagiarismCatcher(){

}

