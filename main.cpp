//Author:  Kirk Karavouzis
//Course:  Computer Networks (CSCI 5761) / Spring 2015
//File:  main.cpp
//Description:  

#include <cstdio>			//Standard input-output
#include <cstdlib>			//C standard library
#include <cstring>			//C style strings
#include <string>			//C++ style strings
#include <iostream>		//cout, cin
#include <fstream>			//readfile
#include <list>
#include <vector>
#include <queue>

#define MAXLINEBUF 100
#define INFINITY 4294967295
using std::vector;
using std::list;
using std::priority_queue;


struct node 
{
	unsigned int id;
	unsigned int destination;
	unsigned int cost;
	list<node> adjList;			//adjacency list
	node* p;		 		     	//predecessor
	unsigned int d;			//distance	
	
	node(int _destination, int _cost)
	{
		destination = _destination;
		cost = _cost;
		p = NULL;
		d = INFINITY;		
	}  
	
	node(int _id, list<node> list){
		id = _id;
		adjList = list;
		p = NULL;
		d = INFINITY;
	}
};

struct compare
{
    bool operator() ( node i, node j)
        {return i.d > j.d;}
};


int main(int argc, char* argv[])
{
	
	char* filename;
	int sourceNode;
		
	//check for correct usage
	if (argc < 3)
	{	
		std::cerr << "\nUsage:  linkstate <input-file> <source node>\n" << "\nPlease enter a valid filename and source node.\n" << std::endl;
		exit(-1);
	}
	else{
		filename = argv[1];
		sourceNode = atoi(argv[2]);
	}
	
	//start timer
	
	//Read input file
	FILE *file;
	char line[MAXLINEBUF];
	int numberOfNodes;
	unsigned int source;
	unsigned int dest;
	unsigned int cost;
	char* next;
	
	
	//open file for reading
	file = fopen(filename, "r");
	
	//Get the first line which contains the number of nodes
	fgets(line,MAXLINEBUF, file);
	numberOfNodes = atoi(line);
	
	list<node> graph[numberOfNodes+1];
	
	while(fgets(line,MAXLINEBUF, file))
	{
		for (int i = 0;  i < strlen(line); ++i) 
		{
			strtok(line, " ");
			source = atoi(line);
			
			next = (char*)strtok(NULL, " ");
			dest = atoi(next);
			
			next = (char*)strtok(NULL, " ");
			cost = atoi(next);
			if((cost != 0) && (cost != INFINITY))
			{
				graph[source].push_back(node(dest,cost));
			}			
		}
	}
	fclose(file);
	
	//Create priority queue
	priority_queue<node, std::vector<node>, compare> Q;
	for (int i = 1; i <= numberOfNodes; ++i  ) {
		node v(i,graph[i]);
		v.d = i;
		Q.push(v);		
	}
	
	
	//~ for (int i = 1; i <= numberOfNodes; ++i  ) {
		//~ for (list<node>::iterator iNode = graph[i].begin(); iNode != graph[i].end(); ++iNode  )
		//~ {
			//~ std::cout << "There is an edge going from " << i << " to " << iNode->destination;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
		//~ }
		
	//~ }
	
	//~ for (int i = 0; i < numberOfNodes; ++i  ) {
		//~ for (list<node>::iterator iNode = Q[i].adjList.begin(); iNode != Q[i].adjList.end(); ++iNode  )
		//~ {
			//~ std::cout << "There is an edge going from " << Q[i].id << " to " << iNode->destination;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
		//~ }
		
	//~ }
	while(!Q.empty()){
		
		node x = Q.top();
		for (list<node>::iterator iNode = x.adjList.begin(); iNode != x.adjList.end(); ++iNode  )
		{
			std::cout << "There is an edge going from " << x.id << " to " << iNode->destination;
			std::cout << " with a weight of " << iNode->cost << std::endl;
		}
		Q.pop();
	}
		
	std::cout << "There are " << numberOfNodes << " nodes in the graph." << std::endl;
	//start linkstate algorithm
	
	//stop timer
	
	//output results
	
	return EXIT_SUCCESS;
}