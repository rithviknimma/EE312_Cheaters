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
	int tableSize;
	HashTable *table;

	int numFiles;
	vector<string> files;

	string getNextWord(string s, int& pos);
	string vectorToString(const vector<string>& vec); 
	int getFileIndex(string s);

public:
	const int FAILURE = -1;
	const int SUCCESS = 0;
	const int FILE_TOO_SMALL = 1;
	const int FILE_NOT_OPENED = 2;

	PlagiarismCatcher(){
		numFiles = 0;
		n = 0;
		tableSize = table->getSize();
	}

	PlagiarismCatcher(int n, int tableSize){
		numFiles = 0;

		this->n = n;
		this->tableSize = tableSize;
		table = new HashTable(tableSize);
	}

	int generateHashtable(string filename);
	void findCollisions(int thershold);

	~PlagiarismCatcher();
};

string PlagiarismCatcher::getNextWord(string s, int& pos){
	string word;
	//first look for a space
	int finder = s.find(" ", pos);
	bool found = true;

	if(finder == string::npos){
		//then check for a carriage return
		finder = s.find("\r", pos);

		if(finder == string::npos){
			//finally look for a newline
			finder = s.find("\n", pos);

			//if you still didn't find anything, that's a problem
			if(finder == string::npos){
				found = false;
			}
		}
	}
	//if you found a valid word, return it
	if(found){
		word = s.substr(pos, finder-pos);
		pos = finder+1;
	}
	//otherwise, return the empty string and increment your position
	else{
		word = "";
		pos++;
	}

	return word;
}

string PlagiarismCatcher::vectorToString(const vector<string>& vec){
	string s = "";
	for(int  i = 0; i < vec.size(); i++){
		s.append(vec[i]);
		s.append(" ");
	}
	return s;
}

int PlagiarismCatcher::generateHashtable(string fileName){
	ifstream myFile(fileName);

	if(myFile.is_open()){
		files.push_back(fileName);
		numFiles++;

		vector<string> vec;
		string buf;

		myFile >> buf;

		while(myFile){		
			//push the words into the vector
			vec.push_back(buf);
			//when the vector is "full"
			//get the n word sequence and delete the first word
			if(vec.size() == n){
				(*table).addElement((*table).hash(vec), fileName);
				vec.erase(vec.begin());
			}	

			myFile >> buf;
		}
		myFile.close();
		return SUCCESS;
	}

	else{
		return FILE_NOT_OPENED;
	}
}

// void PlagiarismCatcher::findCollisions(int threshold){
// 	int collisions[numFiles][numFiles];
// 	vector<string> vec;

// 	for(int i = 0; i < table->getSize(); i++){
// 		vec = table->getCollisionsAt(i);

// 		if(vec[i] != ""){
// 			for(int j = 0; j < vec.size() - 1; j++){
// 				for(int k = j+1; k < vec.size(); k++){
					
// 				}
// 			}
// 		}
// 	}
// }

void PlagiarismCatcher::findCollisions(int threshold){
	int collisions[numFiles][numFiles];

	for(int i = 0; i < numFiles; i++){
		for(int j = 0; j < numFiles; j++){
			collisions[i][j] = 0;
		}
	}

	HashTable::HashNode** hashTable = table->getTable();
	HashTable::HashNode* ptr;
	HashTable::HashNode* inside;
	for(int i = 0; i < table->getSize(); i++){
		ptr = hashTable[i];
		if(ptr != NULL || ptr->next != NULL){
			while(ptr != NULL){
				inside = ptr->next;
				while(inside != NULL){
					// get index from vector
					collisions[getFileIndex(ptr->file)][getFileIndex(inside->file)]++;
					collisions[getFileIndex(inside->file)][getFileIndex(ptr->file)]++;
					inside = inside->next;
				}		
				ptr = ptr->next;		
			}
		}
	}
}

int PlagiarismCatcher::getFileIndex(string s){
	int i = 0;
	while(files[i] != s && i < files.size()){
		i++;
	}
	return i;
}

PlagiarismCatcher::~PlagiarismCatcher(){

}

