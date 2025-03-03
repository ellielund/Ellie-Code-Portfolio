/*
 *FILE: main.cpp
 *Author: Ellie Lund
 *Project 3
 *
 *Calculates the shortest path and cost between
 *two user inputted airports
 *
 */


#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>

#include "graph.hpp"

using namespace std;
//new map with string index and string value called pathMap
//map <string, string> pathMap;
//new string called start
string start;

int main(int argc, const char * argv[]) {
    //read in filename
    cout << "Enter a filename for graph data: ";
    string fname;
    cin >> fname;
    
    //create filestream and open file
    ifstream ifile;
    ifile.open(fname);
    
    //use the provided graph class to create a graph out of the input file
    Graph data(ifile);
    
    //new set of strings called verts, with the vertexes stored using the getVertexes provided method
   set<string> verts = data.getVertexes();
    //stores the number of airports using .size method on the set
    unsigned int numOfPorts = verts.size();
    //cout << numOfPorts;
    
    //print out a message and read in the arrival and departure cost into cost
    cout << "\nWhat is the departure/arrival cost (0 for no cost): ";
    int cost;
    cin >> cost;
    
    //print out a message and read in the starting airport into start
    cout << "\nDeparture Airport: ";
    cin >> start;
    while(!verts.contains(start))
     {
         cout << endl << "Invalid departure airport, please try again: ";
         cin >> start;
     }

    
    //print out a message and read in the destination airport into destination
    cout << "\nDestination Airport: ";
    string destination;
    cin >> destination;
    while(!verts.contains(destination))
     {
         cout << endl << "Invalid arrival airport, please try again: ";
         cin >> destination;
     }
    
    //new map with index string and int value called costMap
    map <string, int> costMap;
    //new map with index string and string value called pathMap
    map <string, string> pathMap;
    
    //for every string in verts set
    for(string v: verts)
    {
        //set the cost map value of the same string to INT_MAX
        //this is to help calculate the minimum cost later
        costMap[v] = INT_MAX;
    }
    
    //new set of strings called visited
    set<string> visited;
    //sets the costMap value of the starting airport to 0, as they cost to get there is nothing since you start there
    costMap[start] = 0;
    
    //while visited set does not contain
    while(!visited.contains(destination))
    {
        //new int lowestValue set equal to
        int lowestValue = INT_MAX;
        //new string called index to store the index with the lowest value
        string index;
        
            //for string v in verts
            for(string v : verts)
            {
                //if the costMap value at vertex v is less than the lowest value and the visted set does not contain this airport
                if(costMap[v] < lowestValue && !visited.contains(v))
                {
                    //set the lowest value to the cost at costMap index v
                    lowestValue = costMap[v];
                    //update index with the airport v to use for later
                    index = v;
                }
            }
        //inserts the lowest cost airport into the visited set
        visited.insert(index);
        //new set of strings called adj which stores airports that are adjacent to the index using provided getAdjacencies method on the data graph
        //for every string a in adj
        set<string> adj = data.getAdjacencies(index);
        for(string a : adj)
        {
            //declare edgecost
            int edgecost;
            //set edgecost to the edge cost between index and a using provided getEdgeCost method on data graph
            edgecost = data.getEdgeCost(index, a);
            //if departure/arrival cost is greater than zero
            if(cost > 0)
            {
                //set edgecost equal to edgecost + 2* cost (for departing and arrival)
                edgecost = edgecost + (2*cost);
            }
            //set edgecost to edgecost + lowestValue to get the total cost to get to that location
            edgecost = edgecost + lowestValue;
            
            //if edgecost if less than cost at costMap index a
            if(edgecost < costMap[a])
            {
                //update int for cost at index a
                costMap[a] = edgecost;
                //update pathmap of a to index to keep track where the last airport was
                pathMap[a] = index;
            }
        }
    }
    //prints the value of costMap at index destination (will be the total cost from start to destination)
    cout << "The minimum cost from " << start << " to " << destination << " is ";
    cout << costMap[destination] << endl;
    
    //new string curr set equal to destination
    //this is to start the backtrack to find the actual path
    string curr = destination;
    //new string called pathPath with size of numOfPorts
    string pathPath[numOfPorts];
    //set int numEl (in path path) to 0
    int numEl = 0;
   //for i set equal to zero, while i is less than numOfPorts, incrementing i each time
    //this loop basically backtracks from the destination to get the most direct path from destination using pathMap
    for(int i = 0; i < numOfPorts; i++){
            //set pathPath of i equal to where pathMap of curr came from
            //i.e. if pathMap[lax] = stl, set pathPath[0] = stl
            pathPath[i] = pathMap[curr];
            //increment number of elements
            numEl++;
            //set curr equal to where pathMap of curr came from
            curr = pathMap[curr];
   }
   
    //for i set to numEl, while i is greater than or equal to zero, decmrementing i each time
    //this loop prints the path, but does it backwards, as they were entered from destination to departure airport
    for(int i = numEl; i >= 0; i--)
    {
        //some indexes will be empty as it is likely the shortest path will not be through every airport
        //so checks if the pathPath of index i's string length is greater than 0
        if(pathPath[i].length() > 0)
        //prints the value of pathPath at index i followed by an arrow
        cout << pathPath[i] << "->";
    }
    //destination was the original location and was not added to the path path array, so print this last, this also ensures there is not an extra arrow
    cout << destination << endl;
    
    return 0;
        
}

