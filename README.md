Author:  Kirk Karavouzis
Course:  Computer Networks (CSCI 5761) / Spring 2015
Description:  Linkstate is a program that takes an input file, represting a connected graph, and a source node and computes
the least-cost path for the source to all nodes using Dijkstra's algorithm


linkstate:  The program will read the first line from the file to determine how many nodes are in the graph.  It will then read the remaining lines and programmatically construct the graph using and array of 
linked lists to represent adjacent nodes for each node.  Dijkstra's algorithm is then run on the graph to compute the least-cost path to each node from the source node.  A timer is used to compute the execution 
time from the point of reading the file to the end of the least-cost path computation. 
The program is written in c++ but composed in one file in an attempt to improve the speed of computation.

The makefile will compile main.cpp and link dependencies.   
The makefile has two options:  make or make debug.  make debug will compile additional code to display additional information as described below.

The target executable is linkstate.  It takes 2 argurements:  the sample input file and and source node (represented by an integer value).
	Example:  ./linkstate sampleinput 10
	
The program will output a forwarding table to the standard out (screen) as well as the total execution time.
In debug mode mode the program will also display the immediate result for each iteration of Dijkstra's algorithm in a tabular format.