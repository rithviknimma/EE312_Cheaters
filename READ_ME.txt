1) To compile the code, go to the directory with all the files and type "make"

2) To run the file, type in "./plagiarismCatcher" followed by the name of the directory with all the txt files and a forward slash. The number of n word sequences and the threshold number for the minimum number of matches to check for between the docs follows next.

   Ex: "./plagiarismCatcher med_doc_set/ 10 200"

3) This will output all the files in the directory "med_doc_set/" with at least 200 10-word sequences in common.