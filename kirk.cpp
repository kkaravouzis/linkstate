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
#define INFINITY 2147483647
using std::ifstream;
using std::vector;
using std::list;
using std::priority_queue;
using std::string;

//STRUCTS
struct node 
{
	unsigned int id;
	unsigned int cost;
	
	node(int _id, int _cost)
	{
		id = _id;
		cost = _cost;	
	}  		
};

struct compare
{
    bool operator() (node i, node j)
        {return i.cost > j.cost;}
};

//HELPER FUNCTIONS
unsigned NextHop(unsigned start, unsigned endIndex, vector<node> S, vector<unsigned int> pred);
void PrintGraphEdges(list<node> g[], int size);
void PrintShortestPath(vector<node> S);
void PrintForwardingTable(int sourceNode, vector<node> S, vector<unsigned>  pred);

int main(int argc, char* argv[])
{
	
	char* filename;
	int sourceNode;
		
	//CHECK FOR CORRECT USAGE
	if (argc < 3)
	{	
		std::cerr << "\nUsage:  linkstate <input-file> <source node>\n" << "\nPlease enter a valid filename and source node.\n" << std::endl;
		exit(-1);
	}
	else{
		filename = argv[1];
		sourceNode = atoi(argv[2]);
	}
	
	//START TIMER
	clock_t timer = clock();
	
	//READ INPUT FILE
	ifstream file;
	file.open(filename);
	int numberOfNodes;
	int source, dest, cost;	
	//Get the first line which contains the number of nodes
	file >> numberOfNodes;
	
	//read the rest of the file and create the graph
	list<node> graph[numberOfNodes+1];
	while(!file.eof()){
		file >> source >> dest >> cost;
		if((cost != 0) && (cost != INFINITY)){
			graph[source].push_back(node(dest,cost));
		}		
	}
	file.close();
		
	//PRINT ALL OF THE EDGES
	//PrintGraphEdges(graph, numberOfNodes);
	
	
	//Create priority queue and initialize
	vector<unsigned> distance(numberOfNodes+1);
	vector<unsigned>  predecessor(numberOfNodes+1);
	vector<bool> visited(numberOfNodes + 1);
	priority_queue<node, vector<node>, compare> Q;
	vector<node> S;
	
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
	
	
	
	
	#ifdef DEBUG
	//-------------FOR DEBUGGING-----------------------
	//Print Table Headers
	std::cout << std::setw(5) << "Step";
	for(int i = 1; i <= numberOfNodes; ++i){
		std::ostringstream oss;
		oss << i;
		string output = "D(" + oss.str() + "),p(" + oss.str()+ ')';
		if(i != sourceNode)
			std::cout << std::setw(15) << output;
	}
	std::cout << "\n";
	//-------------FOR DEBUGGING-----------------------
	#endif
	
	//START LINKSTATE ALGORITHM
	int count = 0;
	while(!Q.empty()){
		node u = Q.top();
		Q.pop();
		
		for (list<node>::iterator iNode = graph[u.id].begin(); iNode != graph[u.id].end(); ++iNode)
		{	
			if(!visited.at(iNode->id)){
				if(distance[iNode->id] > (distance[u.id] + iNode->cost))
				{				
					distance[iNode->id] = distance[u.id] + iNode->cost;
					node x(iNode->id, distance[iNode->id] );
					predecessor.at(iNode->id) = u.id;
					Q.push(x);											
				}									
			}		
		}
		
			
		if(!visited.at(u.id)){	
			S.push_back(u);
			visited.at(u.id) = true;
			
			#ifdef DEBUG
			//-------------FOR DEBUGGING-----------------------
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
			//-------------FOR DEBUGGING-----------------------
			#endif
		}		
	}
	
	
	
	//STOP TIMER
	timer = clock() - timer;
	float elapsedTime = ((float)timer)*1000/CLOCKS_PER_SEC;
	
	//OUTPUT RESULTS
	printf("\n%.3f milliseconds to compute the least-cost path from node %d.\n\n", elapsedTime, sourceNode);
	PrintForwardingTable(sourceNode, S, predecessor);

	//print predecessor list
	//~ for(unsigned int i = 1; i <= numberOfNodes;++i){
		//~ if(i !=sourceNode)
			//~ printf("%u's predecessor is %u.\n",i,predecessor.at(i));
	//~ }
	
	#ifdef DEBUG
	//PRINT SHORTEST PATH
	PrintShortestPath(S);
	#endif
	
	return EXIT_SUCCESS;
}

void PrintForwardingTable(int sourceNode, vector<node> S, vector<unsigned>  pred){
	std::cout << std::setw(15) << "Destination" << std::setw(15) << "Link" << std::endl;
	
	for(int i = 1; i < S.size(); ++i){
		unsigned int current = S.at(i).id;
		unsigned int p = pred.at(current);
		std::ostringstream source, next;
		source << sourceNode;
		
		while(p != sourceNode){
			current = p;
			p = pred.at(current);
		}
		
		next << current;
		string output = "(" + source.str()+ "," + next.str() + ")";
		
		std::cout << std::setw(15) << S.at(i).id
				<< std::setw(15) <<  output
				<< std::endl;
	}
}
void PrintShortestPath(vector<node> S){
	for(int i =0; i < S.size(); ++i){
		std::cout << S.at(i).id;
		if(i != S.size()-1)
			std::cout << "->";
		else
			std::cout<< "\n" << std::endl;
	}
}
void PrintGraphEdges(list<node> g[], int size){
	std::cout << "Printing Edges" << std::endl;
	for (int i = 1; i <= size; ++i  ) {
		for (list<node>::iterator iNode = g[i].begin(); iNode != g[i].end(); ++iNode  )
		{
			std::cout << "There is an edge going from " << i << " to " << iNode->id;
			std::cout << " with a weight of " << iNode->cost << std::endl;
		}
		
	}
}


unsigned NextHop(unsigned start, unsigned endIndex, vector<node> S, vector<unsigned int> pred)
{
	int i =endIndex;
		while(i != start)
		{
			i = pred.at(i);
		}
		
		
	return i;
	
}