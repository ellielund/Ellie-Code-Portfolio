# Dijkstra's Algorithm

## Overview
This project provides an implementation of  Dijkstra’s Algorithm in order to find the shortest path from a departure airport to an arrival airport. The program reads airport and flight data from a file, constructs a graph, and calculates the minimum cost path between two user-selected airports.

## Provided Code
This project included some starter code provided by my professor. Below is a breakdown of what was given:
- **Provided Components:** 
The graph class and all of it's methods were provided in order to ease implementation of Dijkstra's Algorithm by handling graph construction and traversal. This included methods for adding vertices, retrieving adjacent nodes, and fetching edge costs. 

## My Contributions
- **Features Implemented:** 
Implemented Dijkstra's Algorithm to determine the shortest path between airports.
Managed user input for departure and destination airports, ensuring valid entries. 
Calculated the total cost while considering optional departure and arrival costs.
Tracked the path using a backtracking approach and displayed the final route.

- **Challenges & Solutions:** 
Efficiently handled large graphs by tracking visited nodes to avoid checking every vertex. 
Prevented infinite loops as if the user entered an invalid airport, the program could behave unpredictably, I've added input validation to ensure proper input before proceeding. 
Reconstructed the path from destination to departures by tracking predecessors in a separate map (pathMap), by backtracking through this map, the shortest path printed in the correct order. 

## How to Run
```bash
g++ -c -Wall -ansi -pedantic -std=c++20 main.cpp 
g++ -c -Wall -ansi -pedantic -std=c++20 graph.cpp 
g++ -o proj main.o graph.o
./proj

Example Input:
Enter a filename for graph data: cities1.txt
What is the departure/arrival cost (0 for no cost): 10
Departure Airport: lax
Destination Airport: dfw
The minimum cost from lax to dfw is 528
lax->stl->ord->dfw
