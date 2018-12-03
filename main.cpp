/* main.cpp

  a simple driver for plagiarism

  Name: Rithvik Baddam
  UT eid: rrb2442

  Name: Arul Saraf
  UT eid: as75789
*/

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include "PlagiarismCatcher.h"

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files, string ext)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        string fileName = string(dirp->d_name);
        if(fileName.find(ext) != string::npos)
            files.push_back(fileName);
    }
    closedir(dp);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc < 3){
        cerr << "Please enter correct cmd line parameters" << endl;
    }
    else{
        //string dir = string("sm_doc_set");
        string dir = string(argv[1]);
        PlagiarismCatcher p(stoi(string(argv[2])), 10000);
        vector<string> files = vector<string>();

        getdir(dir,files, ".txt");

        string fileName;
        int e; 

        for (unsigned int i = 0; i < files.size();i++) {
            fileName = dir;
            //fileName.append("/");
            fileName.append(files[i]);

            e = p.generateSequences(fileName);

            if(e != 0){
                cout << fileName << " messed up" << endl;
            }
        }
    }


    return 0;
}

