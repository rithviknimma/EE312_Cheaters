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

using namespace std;

class PlagiarismCatcher{
private:
	int n;

	string getNextWord(string s, int& pos);
	string vectorToString(vector<string> vec); 

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

// string PlagiarismCatcher::getNextWord(string s, int& pos){
// 	int space = s.find(" ", pos);	

// 	if(pos == space){
// 		space = s.find("\n", pos);
// 	}

// 	string word = s.substr(pos, space-pos);

// 	pos = space;
// cout << space << endl;
// 	return word;
// }

string PlagiarismCatcher::vectorToString(vector<string> vec){
	string s = "";
	for(int  i = 0; i < vec.size(); i++){
		s.append(vec[i]);
		s.append(" ");
	}

	return s;
}

int PlagiarismCatcher::generateSequences(string fileName){

		ifstream myFile(fileName);
		
		if(myFile.is_open()){

			vector<string> vec;
			vec.push_back("hi");
			string buf;
			int pos;



			while(getline(myFile, buf)){
				pos = 0;
cout << buf.size() << endl;
				while(pos < buf.size()){
					int i = buf.find(" ", pos);
					if(i != -1){
						string s = buf.substr(pos, i-pos);
						cout << s << " ";
						pos = i+1;
					}

					else{
						int i = buf.find("\n", pos);
						string s = buf.substr(pos, i-pos);
						cout << s << " ";
						pos = i+1;
					}
					
				}

				cout << endl;

			}

		
			myFile.close();
			return SUCCESS;
		}

		else{
			return FILE_NOT_OPENED;
		}
	}
