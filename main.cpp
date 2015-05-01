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
#include <iomanip>		//standard output formatting
#include <list>
#include <vector>
#include <queue>
#include <ctime>

#define MAXLINEBUF 100
#define INFINITY 4294967295
using std::vector;
using std::list;
using std::priority_queue;


struct node 
{
	unsigned int id;
	unsigned int cost;
	unsigned int p;
		
	node(int _id, int _cost)
	{
		id = _id;
		cost = _cost;	
		p = 0;
	}  		
};

struct compare
{
    bool operator() (node i, node j)
        {return i.cost > j.cost;}
};

unsigned FindLink(unsigned start, unsigned endIndex, vector<node> S);

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
	clock_t timer = clock();
	
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
	
	
	//read the rest of the file and create the graph
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
	
	
	//~ for (int i = 1; i <= numberOfNodes; ++i  ) {
		//~ for (list<node>::iterator iNode = graph[i].begin(); iNode != graph[i].end(); ++iNode  )
		//~ {
			//~ std::cout << "There is an edge going from " << i << " to " << iNode->id;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
		//~ }
		
	//~ }
	//Create priority queue and initialize
	vector<int> distance(numberOfNodes+1);
	vector<bool> visited(numberOfNodes + 1);
	priority_queue<node, vector<node>, compare> Q;
	
	for (int i = 1; i <= numberOfNodes; ++i  ) {
		
		node v(i,INFINITY);
		if(i == sourceNode) {
			distance.at(i)= 0;
			v.cost = 0;
			Q.push(v);
		}else{
			distance.at(i) = INFINITY;
		}	
		
		visited.at(i) = false;
	}
	
	//start linkstate algorithm
	vector<node> S;
	while(!Q.empty()){
		node u = Q.top();
		Q.pop();
		if(!visited.at(u.id)){
			S.push_back(u);
			visited.at(u.id) = true;
				
			for (list<node>::iterator iNode = graph[u.id].begin(); iNode != graph[u.id].end(); ++iNode)
			{						
				if(distance[iNode->id] > (u.cost + iNode->cost))
				{				
					distance[iNode->id] = u.cost + iNode->cost;
					node x(iNode->id, distance[iNode->id] );
					x.p = u.id;
					Q.push(x);					
				}
			}	
		}			
	}
	
	
	
	//stop timer
	timer = clock() - timer;
	float elapsedTime = ((float)timer)*1000/CLOCKS_PER_SEC;
	
	//output results

	printf("\n%.3f milliseconds to compute the least-cost path from node %d.\n\n", elapsedTime, sourceNode);
	
	std::cout << std::setw(15) << "Destination" << std::setw(15) << "Link" << std::endl;
	for(int i = 0; i < S.size(); ++i){
		std::cout << std::setw(15) << S.at(i).id
				<< std::setw(15) <<  "(" <<  sourceNode << ", " << FindLink(sourceNode, S.at(i).id, S)
				<< std::endl;
		printf("Node %u's predecessor is %u.\n",S.at(i).id, S.at(i).p);
	}
	
	return EXIT_SUCCESS;
}

unsigned FindLink(unsigned start, unsigned endIndex, vector<node> S)
{
	unsigned p = INFINITY;
	unsigned z = INFINITY;
	
		for(int i =endIndex; p != start; --i )
		{
			p = S[i].p;
			z = S[i+1].p;
		}
		
		
	return z;
	
}