//Author:  Kirk Karavouzis
//Course:  Computer Networks (CSCI 5761) / Spring 2015
//File:  linkstatefunctions.h
//Description:  




void ReadFile();

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
	//~ while(!Q.empty()){
		
		//~ node x = Q.top();
		//~ for (list<node>::iterator iNode = x.adjList.begin(); iNode != x.adjList.end(); ++iNode  )
		//~ {
			//~ std::cout << "There is an edge going from " << x.id << " to " << iNode->destination;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
		//~ }
		//~ Q.pop();
	//~ }
	
	//std::cout << "There are " << numberOfNodes << " nodes in the graph.\n" << std::endl;
	
	
	void Relax(node u, node v){
	if(v.d > (u.d + v.cost))
	{
		v.d = u.d + v.cost;
		v.p = &u;
	}
}