/*
 * SixDegrees.cpp
 * SixDegrees class implementation
 * Author: Blake Watabe, CS15 Fall 2021
 */
 
#include "SixDegrees.h"
#include "CollabGraph.h"
#include "Artist.h"

#include <queue>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <fstream>

/*********************************************************************\
*                         Constructors                               *
\*********************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @function: Nullary constructor
 * @purpose: initialize a SixDegrees instance
 *
 * @preconditions: none
 * @postconditions: none
 *
 * @parameters: none
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SixDegrees::SixDegrees()
{
    //Empty, nothing needed to be done
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/********************************************************************\
*                   Command Loop - Only Text File                   *
\********************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @function: command loop function
 * @purpose: allows the program to take in 1 line of input
 *
 * @preconditions: none
 * @postconditions: none
 *
 * @parameters: none
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SixDegrees::run(string text_file)
{
    //read in the Artists.txt from argv[1]
    vector<Artist> v1 = read_artists(text_file);
    //populate the graph
    collab_graph.populate_graph(v1);
    
    //run from cin
    readCommands(cin,cout);
}
/********************************************************************\
*              Command Loop - Text File and Command File             *
\********************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @function: command loop function
 * @purpose: allows the program to take in 2 lines of input
 *
 * @preconditions: none
 * @postconditions: none
 *
 * @parameters: none
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SixDegrees::run(string text_file, string commands_file)
{
    //read in the Artists.txt from argv[1]
    vector<Artist> v1 = read_artists(text_file);
    //populate the graph
    collab_graph.populate_graph(v1);
    
    ifstream infile;
    infile.open(commands_file);
    if(!infile.is_open()){
        cerr << commands_file << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    //run from commandfile
    readCommands(infile,cout);
    infile.close();
}
/********************************************************************\
*        Command Loop - Text File, Command File, and Output File    *
\********************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @function: command loop function
 * @purpose: allows the program to take in 3 lines of input
 *
 * @preconditions: none
 * @postconditions: none
 *
 * @parameters: none
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SixDegrees::run(string text_file, string commands_file,
string output_file)
{
    //read in the Artists.txt from argv[1]
    vector<Artist> v1 = read_artists(text_file);
    //populate the graph
    collab_graph.populate_graph(v1);
    
    ifstream infile;
    infile.open(commands_file);
    if(!infile.is_open()){
        cerr << commands_file << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    ofstream outfile;
    outfile.open(output_file);
    if(!outfile.is_open()){
        cerr << output_file << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    //run from commandfile
    readCommands(infile,outfile);
    outfile.close();
    infile.close();
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/********************************************************************\
*                           Reading files                            *
\********************************************************************/
/* Description: read Artists function */
/* Purpose: Function to read in and populate the vector of Artists      */
/* Arguments: a string for the file name                                */
/* Returns: none                                                        */
vector<Artist> SixDegrees::read_artists(string filename)
{
    vector<Artist> artists;
    //declare the ifstream
    ifstream filestream;
    //set the file name equal to the first argument in command line
    string artists_file = filename;
    //open the file
    filestream.open(artists_file);
    //error checking
    if(! filestream.is_open()){
        cerr << artists_file << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    string artist_name;
    string song_name;
    //read through file
    while(getline(filestream, artist_name)){
        Artist new_artist;
        new_artist.set_name(artist_name);
        getline(filestream,song_name);
        while(song_name != "*"){
            new_artist.add_song(song_name);
            getline(filestream, song_name);
        }
        artists.push_back(new_artist);
    }
    //close file
    filestream.close();
    return artists;
}

/********************************************************************\
*                        Reading Commands                            *
\********************************************************************/
/* Description: read commands from cin or a file */
/* Purpose: Function to read in and execute commands from input         */
/* Arguments: a ifstream                                                */
/* Returns: none                                                        */
void SixDegrees::readCommands(istream &input, ostream &output)
{
    string line;
    //run while not end of input and not quit command
    while(getline(input,line) && line != "quit"){
        if(line == "print"){
            collab_graph.print_graph(output);
        }
        //bfs 
        else if(line == "bfs"){
            string artist1;
            string artist2;
            getline(input,artist1);
            getline(input,artist2);
            BFS(artist1,artist2,output);
        }
        //dfs
        else if(line == "dfs"){
            string artist1;
            string artist2;
            getline(input,artist1);
            getline(input,artist2);
            DFS(artist1,artist2,output);
        }
        //not command
        else if(line == "not"){
            string artist1;
            string artist2;
            getline(input,artist1);
            getline(input,artist2);
            
            //artists to exclude
            vector<string> exclude;
            string x_artist;
            while(getline(input,x_artist) && x_artist != "*"){
                exclude.push_back(x_artist);
            }
            NOT(artist1,artist2,exclude,output);
        }
        else{
            output << line << " is not a command. Please try again." << endl;
        }
    }
}

/********************************************************************\
*                           BFS Command                             *
\********************************************************************/
/* Description: a breadth first search for a path between two Artists   */
/* Purpose: Function marks the shortest path from one artist to another */
/* Arguments: the two artists as string from command line, the output   */
/* Returns: none                                                        */
void SixDegrees::BFS(string source, string destination, ostream &output)
{
    // queue of Artists
    Artist a1(source);
    Artist a2(destination);
    bool error = false;
    
    //error if artist1 = artist2
    if(source == destination){
        output << "A path does not exist between " << "\"" <<
        source << "\"" << " and " << "\"" << destination << "\"" 
        << ".\n";
        error = true;
    }
    
    //error checking
    if(!collab_graph.is_vertex(a1)){
        output << "\"" << a1.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(!collab_graph.is_vertex(a2)){
        output << "\"" << a2.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(error){
        return;
    }
    
    //unmark all vertices to redo a path
    collab_graph.clear_metadata();
    
    //a queue to store Artists for traversal
    queue<Artist> q;
    bool found = false;
    //add the source to the queue
    q.push(a1);
    while (! q.empty() && !found){
        collab_graph.mark_vertex(a1);
        Artist elem = q.front();
        q.pop();
        vector<Artist> v_neighbors = collab_graph.get_vertex_neighbors(elem);
        //iterate through the vector of neighbors
        int v_size = v_neighbors.size();
        for(int i = 0; i < v_size; i++){
            if(! collab_graph.is_marked(v_neighbors.at(i))){
                Artist neighbor = v_neighbors.at(i);
                collab_graph.mark_vertex(neighbor);
                collab_graph.set_predecessor(neighbor, elem);
                q.push(neighbor);
                //check if it is destination
                if(neighbor.get_name() == destination){
                    found = true;
                }
            }
        }
    }
    stack<Artist> path = collab_graph.report_path(a1, a2);
    //if no path exists
    if(path.size() <= 1){
        output << "A path does not exist between " << "\"" << a1 << "\""
        << " and " << "\"" << a2 << "\"" << "." << endl;
        return;
    }
    Path_Print(path,output);
    
}
/********************************************************************\
*                           Path printer                            *
\********************************************************************/
/* Description: prints the results of BFS                                   */
/* Purpose: Function to read in path from report path and print to output   */
/* Arguments: a stack from report path, ostream                             */
/* Returns: none                                                            */
void SixDegrees::Path_Print(stack<Artist> path, ostream &output)
{
    while(path.size() > 1){
        Artist artist1 = path.top();
        path.pop();
        Artist artist2 = path.top();
        output << "\"" << artist1.get_name() << "\"" << " collaborated with " 
        << "\"" << artist2.get_name() << "\"" << " in " << "\""
        << collab_graph.get_edge(artist1, artist2) << "\"." << endl;
    }
    output << "***" << endl;
}
/************************************************************************\
*                             DFS Command                               *
\************************************************************************/
/* Description: a depth first search for a path between two Artists     */
/* Purpose: Function marks the path from one artist to another          */
/* Arguments: the two artists as string from command line, the output   */
/* Returns: none                                                        */
void SixDegrees::DFS(string source, string destination, ostream &output)
{
    // queue of Artists
    Artist a1(source);
    Artist a2(destination);
    bool error = false;
    
    //error if artist1 = artist2
    if(source == destination){
        output << "A path does not exist between " << "\"" <<
        source << "\"" << " and " << "\"" << destination << "\"" 
        << ".\n";
        error = true;
    }
    
    //error checking
    if(!collab_graph.is_vertex(a1)){
        output << "\"" << a1.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(!collab_graph.is_vertex(a2)){
        output << "\"" << a2.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(error){
        return;
    }
    
    //unmark all vertices to redo a path
    collab_graph.clear_metadata();
    
    //a queue to store Artists for traversal
    stack<Artist> s;
    bool found = false;
    s.push(a1);
    while (! s.empty() && !found){
        Artist elem = s.top();
        s.pop();
        vector<Artist> v_neighbors = collab_graph.get_vertex_neighbors(elem);
        //iterate through the vector of neighbors
        int v_size = v_neighbors.size();
        
        for(int i = 0; i < v_size; i++){
            if(! collab_graph.is_marked(v_neighbors.at(i))){
                Artist neighbor = v_neighbors.at(i);
                collab_graph.mark_vertex(neighbor);
                // cerr << "elem is: " << elem.get_name() << endl;
                // cerr << "neighbor is: " << neighbor.get_name() << endl;
                collab_graph.set_predecessor(neighbor, elem);
                s.push(neighbor);
                //check if it is destination
            }
            if(elem.get_name() == destination){
                found = true;
            }
        }    
    }
    stack<Artist> path = collab_graph.report_path(a1, a2);
    //if no path exists
    if(path.size() <= 1){
        output << "A path does not exist between " << "\"" << a1 << "\""
        << " and " << "\"" << a2 << "\"" << "." << endl;
        return;
    }
    Path_Print(path,output);
}
/************************************************************************\
*                           Not Command                                 *
\************************************************************************/
/* Description: a breadth first search for a path between two Artists   */
/* excluding the artists included in the command line                   */
/* Purpose: Function marks the shortest path from one artist to another */
/* Arguments: the two artists as string from command line, the output   */
/* Returns: none                                                        */
void SixDegrees::NOT(string source, string destination, vector<string> exclude,
ostream &output)
{
    // queue of Artists
    Artist a1(source);
    Artist a2(destination);
    
    bool error = false;
    //error if artist1 = artist2
    if(source == destination){
        output << "A path does not exist between " << "\"" <<
        source << "\"" << " and " << "\"" << destination << "\"" 
        << ".\n";
        error = true;
    }
    
    //error checking
    if(!collab_graph.is_vertex(a1)){
        output << "\"" << a1.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(!collab_graph.is_vertex(a2)){
        output << "\"" << a2.get_name() << "\"" 
        << " was not found in the dataset :(" << endl;
        error = true;
    }
    if(error){
        return;
    }
    
    //unmark all vertices to redo a path
    collab_graph.clear_metadata();
    
    //mark the Artists to exclude
    int x_size = exclude.size();
    for(int i = 0; i < x_size; i++){
        Artist xArtist(exclude.at(i));
        //check if Artist is a vertex in the graph
        if(!collab_graph.is_vertex(xArtist)){
            return;
        }
        collab_graph.mark_vertex(xArtist);
    }
    
    //a queue to store Artists for traversal
    queue<Artist> q;
    bool found = false;
    //add the source to the queue
    q.push(a1);
    while (! q.empty() && !found){
        collab_graph.mark_vertex(a1);
        Artist elem = q.front();
        q.pop();
        vector<Artist> v_neighbors = collab_graph.get_vertex_neighbors(elem);
        //iterate through the vector of neighbors
        int v_size = v_neighbors.size();
        for(int i = 0; i < v_size; i++){
            if(! collab_graph.is_marked(v_neighbors.at(i))){
                Artist neighbor = v_neighbors.at(i);
                collab_graph.mark_vertex(neighbor);
                collab_graph.set_predecessor(neighbor, elem);
                q.push(neighbor);
                //check if it is destination
                if(neighbor.get_name() == destination){
                    found = true;
                }
            }
        }
    }
    stack<Artist> path = collab_graph.report_path(a1, a2);
    //if no path exists
    if(path.size() <= 1){
        output << "A path does not exist between " << "\"" << a1 << "\""
        << " and " << "\"" << a2 << "\"" << "." << endl;
        return;
    }
    Path_Print(path,output);
    
} 