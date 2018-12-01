/* plagiarism.h

  Name: Rithvik Baddam
  UT eid: rrb2442

  Name: Arul Saraf
  UT eid: as75789
*/

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class PlagiarismCatcher{
private:
	int n;

	string getNextWord(string s, int& pos);

public:
	const int SUCCESS = 0;
	const int FILE_TOO_SMALL = 1;
	const int FILE_NOT_OPENED = 2;

	PlagiarismCatcher(){
		n = 0;
	}

	PlagiarismCatcher(int n){
		this->n = n;
	}

	int generateSequences(string filename);
};

string PlagiarismCatcher::getNextWord(string s, int& pos){
	int space = s.find(" ", pos);
	string word = s.substr(pos, space);
	pos = space;

	return word;
}

int PlagiarismCatcher::generateSequences(string fileName){

		ifstream myFile(fileName);
		

		if(myFile.is_open()){

			queue<string> q;
			string buf;
			int pos;
			int lastPos;

			int space;
			string word;

			while(getline(myFile, buf)){
				pos = 0;

				while(q.size() < n){
					q.push(getNextWord(buf, pos));
				}

				q.pop();



			}

			

			myFile.close();
			return SUCCESS;
		}

		else{
			return FILE_NOT_OPENED;
		}
	}
