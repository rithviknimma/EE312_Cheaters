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


	int generateSequences(string fileName){

		ifstream myFile(fileName);
		string buf;

		if(myFile.is_open()){

			while(getline(myFile, buf)){
				cout << buf << endl;
			}

			queue<string> q;
			int pos;
			int lastPos;

			pos = 0;

			myFile.close();
			return SUCCESS;
		}

		else{
			return FILE_NOT_OPENED;
		}
	}


};
