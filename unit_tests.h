/* 
 * unit_tests.h
 * 
 * CS 15 Project 2
 * by Blake Watabe, December 2021
 * 
 */
 
#include "SixDegrees.h"
#include "CollabGraph.h"
#include "Artist.h"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/***************************************************************************\
*                              CollabGraph                                 *
\***************************************************************************/
/* populate graph test
 * Testing to make sure that given a vector of Artists, the populate graph 
 * function will insert artists as vertexes and collaborations as edges
 */
void populate_graph_test()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3;
    a1.set_name("Drake");
    a1.add_song("Jungle");
    a2.set_name("Joji");
    a2.add_song("Afterthought");
    a3.set_name("Benne");
    a3.add_song("Afterthought");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.print_graph(cout);    
}
/* populate graph test 2
 * Same test but checking if it works with even more artists, multiple people
 * on collabs
 */
void populate_graph_test2()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3;
    a1.set_name("Bladee");
    a1.add_song("Western Union");
    a2.set_name("Ecco2k");
    a2.add_song("Western Union");
    a3.set_name("Thaiboy Digital");
    a3.add_song("Western Union");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.print_graph(cout);    
}
/* populate graph test 3
 * Same test but checking if it works with even more artists, multiple collabs
 */
void populate_graph_test3()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3,a4,a5;
    a1.set_name("Future");
    a1.add_song("Codeine Crazy");
    a2.set_name("Playboi Carti");
    a2.add_song("No Time");
    a3.set_name("Gunna");
    a3.add_song("No Time");
    a3.add_song("Ski");
    a4.set_name("Young Thug");
    a4.add_song("Ski");
    a5.set_name("Rico Nasty");
    a5.add_song("Rage");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    test_artists.push_back(a4);
    test_artists.push_back(a5);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.print_graph(cout);    
}
/* report path test 
 * Test the report path function given a path to see if it returns the proper
 * path from a to b
 */
void report_path_test()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3,a4,a5;
    a1.set_name("Future");
    a1.add_song("Codeine Crazy");
    a2.set_name("Playboi Carti");
    a2.add_song("No Time");
    a3.set_name("Gunna");
    a3.add_song("No Time");
    a3.add_song("Ski");
    a4.set_name("Young Thug");
    a4.add_song("Ski");
    a4.add_song("Circle of Bosses");
    a5.set_name("Quavo");
    a5.add_song("Circle of Bosses");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    test_artists.push_back(a4);
    test_artists.push_back(a5);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.set_predecessor(a3,a2);
    test_graph.set_predecessor(a4,a3);
    test_graph.set_predecessor(a5,a4);
    // test_graph.print_graph(cout);
    stack<Artist> results = test_graph.report_path(a2,a5);
    int stack_size = results.size();
    cout << "stack size is: " << stack_size << endl;
    while(! results.empty()){
        Artist artist = results.top();
        string name = artist.get_name();
        cout << name << " ";
        results.pop();
    }
}
/* report path test 2
 * Test the report path function given a path to see if it returns the proper
 * path from a to b
 */
void report_path_test2()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3,a4,a5;
    a1.set_name("Future");
    a1.add_song("Codeine Crazy");
    a2.set_name("Playboi Carti");
    a2.add_song("No Time");
    a3.set_name("Gunna");
    a3.add_song("No Time");
    a3.add_song("Ski");
    a4.set_name("Young Thug");
    a4.add_song("Ski");
    a4.add_song("Circle of Bosses");
    a5.set_name("Quavo");
    a5.add_song("Circle of Bosses");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    test_artists.push_back(a4);
    test_artists.push_back(a5);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.set_predecessor(a3,a2);
    test_graph.set_predecessor(a4,a3);
    test_graph.set_predecessor(a5,a4);
    // test_graph.print_graph(cout);
    stack<Artist> results = test_graph.report_path(a3,a4);
    int stack_size = results.size();
    cout << "stack size is: " << stack_size << endl;
    while(! results.empty()){
        Artist artist = results.top();
        string name = artist.get_name();
        cout << name << " ";
        results.pop();
    }
}
/* get vertex neighbors test 
 * Test the get_vertex_neighbors function given a populated graph to see if it
 * returns the proper neighbors (connected edges)
 */
void get_vertex_neighbors_test()
{
    vector<Artist> test_artists;
    Artist a1,a2,a3,a4,a5;
    a1.set_name("Future");
    a1.add_song("Codeine Crazy");
    a2.set_name("Playboi Carti");
    a2.add_song("No Time");
    a3.set_name("Gunna");
    a3.add_song("No Time");
    a3.add_song("Ski");
    a4.set_name("Young Thug");
    a4.add_song("Ski");
    a4.add_song("Circle of Bosses");
    a5.set_name("Quavo");
    a5.add_song("Circle of Bosses");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    test_artists.push_back(a4);
    test_artists.push_back(a5);
    
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    vector<Artist> v1 = test_graph.get_vertex_neighbors(a3);
    for(int i = 0; i < v1.size(); i++){
        cout << v1.at(i).get_name() << endl;
    }
    
}
/* read artists test 
 * Test the readArtists function to see that it properly reads in the text file
 * and is able to properly populate a graph
 */
void read_artists_test()
{
    SixDegrees s1;
    vector<Artist> test_artists = s1.read_artists("test_artists.txt");
    for(int i = 0; i < test_artists.size(); i++){
        cout << test_artists.at(i).get_name() << " " << endl;
    }
    cout << test_artists.size() << endl;
    CollabGraph test_graph;
    test_graph.populate_graph(test_artists);
    test_graph.print_graph(cout);
}
/* bfs test 
 * Test the bgs function to see that it properly reports an existing path
 * between two Artists
 */
void bfs_test()
{
    SixDegrees s1;
    
    vector<Artist> test_artists;
    Artist a1,a2,a3,a4,a5;
    a1.set_name("a1");
    a1.add_song("s1");
    a2.set_name("a2");
    a2.add_song("s1");
    a3.set_name("a3");
    a3.add_song("s2");
    a3.add_song("s3");
    a4.set_name("a4");
    a4.add_song("s3");
    a4.add_song("s4");
    a5.set_name("a5");
    a5.add_song("s4");
    test_artists.push_back(a1);
    test_artists.push_back(a2);
    test_artists.push_back(a3);
    test_artists.push_back(a4);
    test_artists.push_back(a5);
    //populate the graph
    
    s1.collab_graph.populate_graph(test_artists);

    s1.collab_graph.set_predecessor(a2,a1);
    s1.collab_graph.set_predecessor(a3,a2);
    s1.collab_graph.set_predecessor(a4,a3);
    s1.collab_graph.set_predecessor(a5,a4);
    
    cout << "BFS Results: " << endl;
    s1.BFS("a1","a5",cout);
}
