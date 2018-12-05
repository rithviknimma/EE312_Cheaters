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

// function to get txt file names
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

// main engine, runs the hashing function
int main(int argc, char* argv[])
{
    if(argc < 4){ // needs at least 4 parameters
        cerr << "Please enter correct cmd line parameters" << endl;
    }
    else{
        double duration;
        clock_t start;

        string dir = string(argv[1]);
        int nword = atoi(argv[2]);
        int minCollisions = atoi(argv[3]);

        vector<string> files = vector<string>();

        getdir(dir,files,".txt");

        string fileName;
        int e; 

        // generate hash table for all txt files
        for (unsigned int i = 0; i < files.size();i++) { 
            fileName = dir;
            fileName.append(files[i]);
            files[i] = fileName;
        }

        start = clock();

        PlagiarismCatcher p(nword, files);
        p.generateHashtable();   
        vector<string> result = p.findCollisions(minCollisions);

        duration = (clock() - start)/(double) CLOCKS_PER_SEC;

        cout << result.size() << " matches found!" << endl;
        for(int i = 0; i < result.size(); i++){
            cout << result[i] << endl;
        }

        cout << "File reading, hashing, and collision finding took " << duration << " seconds." << endl;
    }
    return 0;
}

