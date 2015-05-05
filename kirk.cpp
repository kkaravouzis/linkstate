//Author:  Kirk Karavouzis
//Course:  Computer Networks (CSCI 5761) / Spring 2015
//File:  main.cpp
//Description:  

#include <cstdio>			//Standard input-output
#include <cstdlib>			//C standard library
#include <cstring>			//C style strings
#include <string>			//C++ style strings
#include <sstream>
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
using std::string;


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
	
	//PRINT ALL OF THE EDGES
	//~ for (int i = 1; i <= numberOfNodes; ++i  ) {
		//~ for (list<node>::iterator iNode = graph[i].begin(); iNode != graph[i].end(); ++iNode  )
		//~ {
			//~ std::cout << "There is an edge going from " << i << " to " << iNode->id;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
		//~ }
		
	//~ }
	
	//Create priority queue and initialize
	vector<unsigned> distance(numberOfNodes+1);
	vector<unsigned>  predecessor(numberOfNodes+1);
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
	
	//FOR DEBUGGING
	std::cout << std::setw(5) << "Step";
	for(int i = 1; i <= numberOfNodes; ++i){
		std::ostringstream oss;
		oss << i;
		string output = "D(" + oss.str() + "),p(" + oss.str()+ ')';
		if(i != sourceNode)
			std::cout << std::setw(15) << output;
	}
	std::cout << "\n";

	int count = 0;
	while(!Q.empty()){
		node u = Q.top();
		Q.pop();
		//printf("\nPopping %u\n",u.id);
		
		
			//~ for(int i=1; i <=numberOfNodes; ++i){
				//~ bool x = visited.at(i);
				//~ printf("%d-%d, ",i,x);
			//~ }
		
		for (list<node>::iterator iNode = graph[u.id].begin(); iNode != graph[u.id].end(); ++iNode)
		{	
			if(!visited.at(iNode->id)){
				if(distance[iNode->id] > (distance[u.id] + iNode->cost))
				{				
					distance[iNode->id] = distance[u.id] + iNode->cost;
					node x(iNode->id, distance[iNode->id] );
					predecessor.at(iNode->id) = u.id;
					//printf("Pushing %u\n",x.id);
					Q.push(x);											
				}									
			}		
		}
		
			
			
			
			
		if(!visited.at(u.id)){	
		S.push_back(u);
		visited.at(u.id) = true;
		//FOR DEBUGGING
		std::cout << std::setw(5) << count;
		for(int i = 1; i <= numberOfNodes; ++i){
			std::ostringstream dist, pred;
			dist << distance.at(i);
			pred << predecessor.at(i);
			string output = dist.str() + "," + pred.str();
			if(i != sourceNode)
				if(visited.at(i))
					std::cout << std::setw(15) << "-";
				else
					if(distance.at(i)==INFINITY)
						std::cout << std::setw(15) << "INFINITY";
					else
						std::cout << std::setw(15) << output;
		}
		std::cout << "\n";
		++count;
			
		//printf("\tStoring %u\n",u.id);
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
		//printf("Node %u's predecessor is %u.\n",S.at(i).id, S.at(i).p);
	}
	
	//~ for(int i =0; i < S.size(); ++i){
		//~ std::cout << S.at(i).id;
		//~ if(i != S.size()-1)
			//~ std::cout << "->";
		//~ else
			//~ std::cout<< "\n" << std::endl;
	//~ }
	
	
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