/* 
 * main.cpp
 */
 #include "SixDegrees.h"
 #include "CollabGraph.h"
 #include "Artist.h"
 #include <iostream>
 
 using namespace std;
 
 int main(int argc, char *argv[]){
     
     //initialize a SixDegrees
     SixDegrees s1;
     //pre-simulation, user types in on command line
     //error message if arguments is greater than 4 or less than 3
     if(argc < 2 || argc > 4){
         cerr << "Usage: SixDegrees dataFile [commandFile] [outputFile]"
         << endl;
         exit(EXIT_FAILURE);
     }
     //run if the number of files is only 1
     else if(argc == 2){
         s1.run(argv[1]);
     }
      //run if the number of files is 2
     else if(argc == 3){
         s1.run(argv[1], argv[2]);
     }
     //run if the number of files is 3
     else{
         s1.run(argv[1], argv[2], argv[3]);
     }
     return 0;
 }