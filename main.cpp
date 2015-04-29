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
	unsigned p;		 		     	//predecessor
	unsigned int d;			//distance	
	
	node(int _id, int _destination, int _cost)
	{
		id = _id;
		destination = _destination;
		cost = _cost;
		p = 0;
		d = INFINITY;		
	}  
	
	node(int _id, list<node> list){
		id = _id;
		adjList = list;
		p = 0;
		d = INFINITY;
	}
};

struct compare
{
    bool operator() ( node i, node j)
        {return i.d > j.d;}
};

void Relax(node i, node j, int distance);


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
				graph[source].push_back(node(source,dest,cost));
			}			
		}
	}
	fclose(file);
	
	//Create priority queue and initialize
	priority_queue<node, std::vector<node>, compare> Q;
	for (int i = 1; i <= numberOfNodes; ++i  ) {
		node v(i,graph[i]);
		if(i == sourceNode){
			v.d = 0;
		}
		
		Q.push(v);		
	}
	
	//start linkstate algorithm
	//priority_queue<node, std::vector<node>, compare> S;
	vector<node> S;
	//~ while(!Q.empty()){
		//~ node u = Q.top();
		//~ printf("Node %u has %d adjacent nodes.  D is %u.\n",u.id, u.adjList.size(), u.d);
		//~ Q.pop();
	//~ }
	
	while(!Q.empty()){
		node u = Q.top();
		S.push_back(u);
		std::cout << "Pushing node " << u.id << std::endl;
		
		for (list<node>::iterator iNode = u.adjList.begin(); iNode != u.adjList.end(); ++iNode  )
		{
			//std::cout << "To node" << iNode->destination << " costs " << iNode->cost << std::endl;
			std::cout << "There is an edge going from " << u.id << " to " << iNode->destination;
			std::cout << " with a weight of " << iNode->cost << std::endl;
			if(iNode->d > (u.d + iNode->cost))
			{				
				iNode->d = u.d + iNode->cost;
				iNode->p = u.id;
				std::cout << "Node-" << iNode->id << " to node-" << iNode->destination << " is now " << iNode->d << " and its predecessor is " 
						<< (iNode->p) << std::endl;				
			}
		}
		Q.pop();
	}
	//stop timer
	
	
	
	
	
	
	//output results
	for(vector<node>::iterator v = S.begin(); v != S.end(); ++v){
		std::cout << v->id << "->";
	}
	
		std::cout << "\n";
	
	return EXIT_SUCCESS;
}

