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
#include <sstream>
#include "hashtable.h"
using namespace std;

class PlagiarismCatcher{
private:
	int n;

	HashTable table;
	vector<string> files;

	string vectorToString(const vector<string>& vec); 

public:
	//default, n words are zero
	PlagiarismCatcher(){
		n = 0;
	}
	//set n
	PlagiarismCatcher(int n){
		this->n = n;
	}
	//pass in files and n
	PlagiarismCatcher(int n, vector<string>& dir){
		this->n = n;

		files = dir;
	}

	void setFiles(vector<string>& dir){
		files = dir;
	};

	void setN(int n){
		this->n = n;
	}

	void generateHashtable();
	vector<string> findCollisions(int thershold);

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
//will create the hash table from all the files
void PlagiarismCatcher::generateHashtable(){
	//loop through all the files, and read them in
	for(int i = 0; i < files.size(); i++){
		ifstream myFile(files[i].c_str());

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
//find collisions between files and return a vector with the display data
vector<string> PlagiarismCatcher::findCollisions(int threshold){
	//2D array for all the collisions
	int collisions[files.size()][files.size()];
	//zero it out
	for(int i = 0; i < files.size(); i++){
		for(int j = 0; j < files.size(); j++){
			collisions[i][j] = 0;
		}
	}
	vector<int> vec;
	//get the collisions between the table entries
	for(int i = 0; i < table.getSize(); i++){
		vec = table.getCollisionsAt(i);

		if(vec.size() > 0){
			for(int j = 0; j < vec.size() - 1; j++){
				for(int k = j+1; k < vec.size(); k++){
					//update the 2d array for all the entries
					collisions[vec[k]][vec[j]]++;
					collisions[vec[j]][vec[k]]++;
				}
			}
		}
	}

	vector<string> colls;
	string s;
	//create the output data from the collisions
	for(int i = 1; i < files.size(); i++){
		for(int j = 0; j < i; j++){
			if(collisions[i][j] > threshold){
				s = "";

				ostringstream toInt;
				toInt << collisions[i][j];
				s.append(toInt.str());

				s.append(": ");
				s.append(files[i].substr(files[i].find("/")+1, files[i].size()-1));
				s.append(", ");
				s.append(files[j].substr(files[j].find("/")+1, files[j].size()-1));

				colls.push_back(s);
			}
		}
	}
	return colls;
}

//destructor since the hashtable needs to be destructed
PlagiarismCatcher::~PlagiarismCatcher(){

}

