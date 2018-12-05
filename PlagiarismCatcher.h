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
	HashTable table;

	int numFiles;
	vector<string> files;

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
		tableSize = table.getSize();
	}

	PlagiarismCatcher(int n){
		numFiles = 0;

		this->n = n;
		this->tableSize = table.getSize();
	}

	PlagiarismCatcher(int n, int tableSize){
		numFiles = 0;

		this->n = n;
		this->tableSize = tableSize;
		table = *(new HashTable(tableSize));
	}

	int generateHashtable(string filename);
	void findCollisions(int thershold);

	~PlagiarismCatcher();
};

// function that converts vector<string> to String and returns it
string PlagiarismCatcher::vectorToString(const vector<string>& vec){
	string s = "";
	for(int  i = 0; i < vec.size(); i++){
		s.append(vec[i]);
		s.append(" ");
	}
	return s;
}

// generates hashtable
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
				table.addElement(table.hash(vectorToString(vec)), fileName);
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

void PlagiarismCatcher::findCollisions(int threshold){
	int collisions[numFiles][numFiles];
	for(int i = 0; i < numFiles; i++){
		for(int j = 0; j < numFiles; j++){
			collisions[i][j] = 0;
		}
	}

	HashTable::HashNode** hashTable = table.getTable();
	HashTable::HashNode* ptr;
	HashTable::HashNode* inside;
	
	for(int i = 0; i < table.getSize(); i++){
		ptr = hashTable[i];
		if(ptr != NULL) {
			if (ptr->next != NULL){  // do not record collision if less than two nodes are available
				while(ptr != NULL){
					inside = ptr->next;
					while(inside != NULL){
						// get index from vector and record collisions
						collisions[getFileIndex(ptr->file)][getFileIndex(inside->file)]++;
						collisions[getFileIndex(inside->file)][getFileIndex(ptr->file)]++;
						inside = inside->next;
					}		
					ptr = ptr->next;		
				}
			}
		}
	}

	// output all the collisions
	for(int i = 1; i < numFiles; i++){
		for(int j = 0; j < i; j++){
			if(collisions[i][j] > threshold){
				cout << collisions[i][j] << ": ";
				cout << files[i] << ", " ;
				cout << files[j];
				cout << endl;
			}
		}
	}
}

// given a string, return the index of where it is in a vector
int PlagiarismCatcher::getFileIndex(string s){
	int i = 0;
	while(files[i].compare(s) && i < files.size()){
		i++;
	}
	return i;
}

PlagiarismCatcher::~PlagiarismCatcher(){

}

