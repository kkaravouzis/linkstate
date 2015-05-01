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
	
	
	//~ while(!Q.empty()){
		//~ node u = Q.top();
		//~ printf("Node %u has %d adjacent nodes.  D is %u.\n",u.id, u.adjList.size(), u.d);
		//~ Q.pop();
	//~ }
	
	//~ while(!Q.empty()){
		//~ node u = Q.top();
		//~ S.push_back(u);
		//~ std::cout << "Pushing node " << u.id << std::endl;
		
		//~ for (list<node>::iterator iNode = u.adjList.begin(); iNode != u.adjList.end(); ++iNode  )
		//~ {
			//~ //std::cout << "To node" << iNode->destination << " costs " << iNode->cost << std::endl;
			//~ std::cout << "There is an edge going from " << u.id << " to " << iNode->destination;
			//~ std::cout << " with a weight of " << iNode->cost << std::endl;
			//~ if(iNode->d > (u.d + iNode->cost))
			//~ {				
				//~ iNode->d = u.d + iNode->cost;
				//~ iNode->p = u.id;
				//~ std::cout << "Node-" << iNode->id << " to node-" << iNode->destination << " is now " << iNode->d << " and its predecessor is " 
						//~ << (iNode->p) << std::endl;				
			//~ }
			
			
		//~ }
		
		//~ Q.pop();
	//~ }