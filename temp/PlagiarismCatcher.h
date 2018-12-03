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
		int pos;

		while(getline(myFile, buf)){		
			pos = 0;
			while(pos < buf.size()){
				//push the words into the vector
				vec.push_back(getNextWord(buf, pos));
				//when the vector is "full"
				//get the n word sequence and delete the first word
				if(vec.size() == n){
					(*table).addElement((*table).hash(vec), fileName, vectorToString(vec));
					vec.erase(vec.begin());
				}	
			}
		}

	
		myFile.close();
		return SUCCESS;
	}

	else{
		return FILE_NOT_OPENED;
	}
}

void PlagiarismCatcher::findCollisions(int t){
	int collisions[numFiles][numFiles];

	HashTable::HashNode* p = (*table)[1];



}

PlagiarismCatcher::~PlagiarismCatcher(){

}

