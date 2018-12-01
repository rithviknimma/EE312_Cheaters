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

int main()
{
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files, ".txt");

    for (unsigned int i = 0; i < files.size();i++) {
        //cout << i << files[i] << endl;
    }

    PlagiarismCatcher p;
    p.generateSequences(files[0]);

    return 0;
}

