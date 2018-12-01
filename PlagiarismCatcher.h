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
		cout << vec[i] << " ";
		// s.append(vec[i]);
		// s.append(" ");
	}
	cout << endl;
	return s;
}

int PlagiarismCatcher::generateSequences(string fileName){

		ifstream myFile(fileName);
		
		if(myFile.is_open()){

			vector<string> vec;
			string buf;
			int pos;



			while(getline(myFile, buf)){
				
				pos = 0;
//cout << buf.size() << endl;
				while(pos < buf.size()){
					string s;
					//look for spaces
					int i = buf.find(" ", pos);
					//if you found a space, get the word
					if(i != -1){
						s = buf.substr(pos, i-pos);
						//cout << s << " ";
						pos = i+1;
					}
					//otherwise, look for a newline
					else{
						i = buf.find('\r', pos);
						//if you found a newline, get the word
						if(i != -1){
							s = buf.substr(pos, i-pos);
							//cout << s << " ";
							pos = i+1;
						}
						
						else{
							i = buf.find('\n', pos);
							//if you found a newline, get the word
							if(i != -1){
								s = buf.substr(pos, i-pos);
								//cout << s << " ";
								pos = i+1;
							}

							else{
								pos++;
							}
						}
					}
					vec.push_back(s);

					if(vec.size() == n){
						for(int  j = 0; j < vec.size(); j++){
							cout << vec[j] << " ";
						}
						cout << endl;
						vec.erase(vec.begin());
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
