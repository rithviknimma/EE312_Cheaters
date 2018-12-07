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

        //the the cmd line arguements
        string dir = string(argv[1]);
        int nword = atoi(argv[2]);
        int minCollisions = atoi(argv[3]);

        vector<string> files = vector<string>();
        //get the files in the directory
        getdir(dir,files,".txt");

        string fileName;

        // add the directories to the files
        for (unsigned int i = 0; i < files.size();i++) { 
            fileName = dir;
            fileName.append(files[i]);
            files[i] = fileName;
        }

        //create the PlagiarismCatcher object, specifiy n and files
        PlagiarismCatcher p(nword, files);
        //make the hashTable
        p.generateHashtable();   
        //get the collisions
        vector<string> result = p.findCollisions(minCollisions);


        //print the collsiions out
        for(int i = 0; i < result.size(); i++){
            cout << result[i] << endl;
        }

    }
    return 0;
}

