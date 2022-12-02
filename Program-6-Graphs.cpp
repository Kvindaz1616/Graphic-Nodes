/**************************
 *KEVIN DIAZ
  CSC-141 
  MFW 1:00-1:50PM
 WINDOWS 10 VISUAL STUDIO CODE
 PROGRAM 6 GRAPHS
 * ************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

//************************** Node *************************

class Node {
	public:
	int id;
	Node* link;
	Node (int id);
};

Node::Node (int id) {
	this->id = id;
	link = NULL;
}

//************************** Graph ****************************
class Graph {
	public:
		//add the node with neighborId as the neighbor of nodeId
		void addNeighbor(int nodeId, int neighborId);

		//reads the edge list from file and creates the adjacency list data structure
		void loadGraph(string edgeListFileName);
		
		//writes the adjacency list into the file
		void dumpGraph(string adjListFileName);

		//Prints number of nodes, number of edges, and maximum degree on terminal
		void printGraphInfo();

		//returns the number of neighbor (degree) of a node
		int getNumNeighbors(int nodeId);

		//returns the number of nodes in the graph
		int getNumVertices();

	private:
		vector<Node*> vertices;
		
};

void Graph::addNeighbor(int nodeId, int neighborId) {
	//loop through verticies and find the node with the id of nodeId
	Node* temp = vertices.at(nodeId); //temp is the node with the id of nodeId
	if (temp->id == neighborId) { //if the node is already a neighbor, do nothing
		return;
	}

	if (temp->id > neighborId) { //if the neighborId is less than the id of the node, add the neighborId to the front of the list
		Node* newNode = new Node(neighborId); //create a new node with the id of neighborId
		Node* temp2 = temp->link; //temp2 is the next node in the list
		newNode->link = temp; //set the link of the new node to the node with the id of nodeId
		vertices[nodeId] = newNode; //set the node with the id of nodeId to the new node
	}
	else{
		bool done = false; //done is false
		while (temp->link !=NULL && !done) { //while the next node in the list is not null and done is false
			if (temp->link->id == neighborId) { //if the next node in the list is the neighborId, do nothing
				done = true; //set done to true
			}
			else if (temp->link->id <neighborId){ //if the next node in the list is less than the neighborId, move to the next node in the list
				temp = temp->link; //set temp to the next node in the list
				done = false; //set done to false
			}
			else if (temp->link->id > neighborId) { //if the next node in the list is greater than the neighborId, add the neighborId to the list
				Node* newNode = new Node(neighborId); //create a new node with the id of neighborId
				Node* temp2 = temp->link; //temp2 is the next node in the list
				newNode->link = temp2; //set the link of the new node to the next node in the list
				temp->link = newNode; // set the link of the node with the id of nodeId to the new node
				done = true; //set done to true
			}
		}
		if (temp->link == NULL && !done) { //if the next node in the list is null and done is false, add the neighborId to the end of the list
			Node* newNode = new Node(neighborId); //create a new node with the id of neighborId
			temp->link = newNode; //set the link of the node with the id of nodeId to the new node
		}
	}
}

void Graph::loadGraph(string edgelistFileName){ //reads the edge list from file and creates the adjacency list data structure

	ifstream inFile; //create an input file stream
	int node1=0; //node1 is the first node in the edge
	int node2=0; //node2 is the second node in the edge
	inFile.open(edgelistFileName); //open the file
	assert(inFile.fail()==false); //assert that the file opened successfully
	while (!(inFile.eof())){ //while the end of the file has not been reached
		inFile >> node1; //read the first node in the edge
		inFile >> node2; //read the second node in the edge
		if (node1 >= node2){
			while (node1 >= vertices.size()){ //while the size of the vector is less than the first node in the edge
				vertices.push_back(NULL); //add a null node to the vector
			}
		}

		else {
			while (node2 >= vertices.size()){ //while the size of the vector is less than the second node in the edge
				vertices.push_back(NULL); //add a null node to the vector
			}
		}

		if (vertices.at(node1) == NULL){ //if the node with the id of node1 is null
			Node* newNode = new Node(node2); //create a new node with the id of node2
			vertices.at(node1) = newNode; //set the node with the id of node1 to the new node
		}

		else {
			addNeighbor(node1, node2); //add the node with the id of node2 as the neighbor of the node with the id of node1
		}

		if (vertices.at(node2) == NULL){ //if the node with the id of node2 is null
			Node* newNode = new Node(node1); //create a new node with the id of node1
			vertices.at(node2) = newNode; //set the node with the id of node2 to the new node
		}

		else {
			addNeighbor(node2, node1); //add the node with the id of node1 as the neighbor of the node with the id of node2
		}
	}
	inFile.close(); //close the file
}

void Graph::dumpGraph(string adjListFileName) {//write the adjacency list to the file by reading it in
	ofstream outFile; //create an output file stream
	outFile.open(adjListFileName); //open the file
	assert(outFile.fail()==false); //assert that the file opened successfully
	int counter = 0; //counter is 0
	for (int i = 0; i < vertices.size(); i++){ //for each node in the vector
		Node* temp = vertices.at(i); //temp is the node at index i
		if (counter != 0 && temp != NULL){ //if counter is not 0 and temp is not null
			outFile << counter << ": "; //write a new line to the file
		}
		while (temp != NULL){ //while temp is not null
			outFile << temp->id; //write the id of temp to the file
			temp = temp->link; //set temp to the next node in the list
			if (temp != NULL){ //if temp is not null
				outFile << " "; //write a space to the file
			}
			if (temp == NULL){ //if temp is null
				outFile << endl; //write a new line to the file
			}
		}
		counter++; //increment counter
	}
	outFile.close(); //close the file
}

int Graph::getNumVertices() {
	//returns the number of nodes in the graph
	int numVertices = 0; //numVertices is the number of nodes in the graph
	for (int i =0; i < vertices.size(); i++){ //loop through the vector
		if (vertices.at(i) != NULL){ //if the node is not null
			numVertices++; // increment numVertices
		}
	}
	return numVertices; //return numVertices
}

int Graph::getNumNeighbors(int nodeId) {
	//returns the number of neighbor (degree) of a node
	int numNeighbors = 0; //numNeighbors is the number of neighbors of a node
	Node* temp = vertices.at(nodeId); //temp is the node with the id of nodeId
	while (temp != NULL){ //while the node is not null
		numNeighbors++; //increment numNeighbors
		temp = temp->link; //set temp to the next node in the list
	}
	return numNeighbors; //return numNeighbors
}

void Graph::printGraphInfo(){
	//Prints number of nodes, number of edges, and maximum degree on terminal
	int numNodes = getNumVertices(); //numNodes is the number of nodes in the graph
	int numEdges = 0; //numEdges is the number of edges in the graph
	int maxDegree = 0; //maxDegree is the maximum degree of a node in the graph
	for (int i = 0; i < vertices.size(); i++){ //loop through the vector
		int numNeighbors = getNumNeighbors(i); //numNeighbors is the number of neighbors of the node with the id of i
		if (numNeighbors > maxDegree) { //if numNeighbors is greater than maxDegree
			maxDegree = numNeighbors; //set maxDegree to numNeighbors
		}
		numEdges += numNeighbors; //increment numEdges by numNeighbors
	}
	numEdges = numEdges/2; //divide numEdges by 2
	cout << "Number of nodes: " << numNodes << endl; //print the number of nodes
	cout << "Number of edges: " << numEdges << endl; //print the number of edges
	cout << "Maximum degree: " << maxDegree << endl; //print the maximum degree
}

void run(string edgeListFileName, string adjListFileName) {
	Graph Graph;
	Graph.loadGraph(edgeListFileName);
	Graph.dumpGraph(adjListFileName);
	Graph.printGraphInfo();
}

//*****************************************************************************


// The main will be removed for testing, do not add any code in the main function 
int main() {
	//Change the filenames according to your local path.
    string edgeListFileName("karate.txt");
    string adjListFileName("karate_adj.txt");
	run(edgeListFileName, adjListFileName);
    return 0;
}
