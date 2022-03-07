/*
 * SixDegrees.h
 * SixDegrees header file
 * Author: Blake Watabe, CS15 Fall 2021
 */
 
#ifndef _SIXDEGREES_H_
#define _SIXDEGREES_H_

#include "CollabGraph.h"
#include "Artist.h"
 
#include <vector>
#include <iostream>

using namespace std;
 
class SixDegrees{
    public:
        /* CONSTRUCTORS */
        SixDegrees();
        
        /* RUN FUNCTIONS */
        void run(string text_file);
        void run(string text_file, string commands_file);
        void run(string text_file, string commands_file, string output_file);
        
        /* COMMAND LOOP */
        void readCommands(istream &input, ostream &output);
        
        /* READING FUNCTION */
        vector<Artist> read_artists(string filename);
        
        /* BFS */
        void BFS(string source, string destination, ostream &output);
        
        /* DFS */
        void DFS(string source, string destination, ostream &output);
        
        /* NOT */
        void NOT(string source, string destination, vector<string> exclude,
        ostream &output);
        
        /* Helper */
        void Path_Print(stack<Artist> path, ostream &output);
    
    private:
        CollabGraph collab_graph;
        
        
        
};
#endif