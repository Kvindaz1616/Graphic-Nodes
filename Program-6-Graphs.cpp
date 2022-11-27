/**************************
 *KEVIN DIAZ
  CSC-141 
  MFW 1:00-1:50PM
 WINDOWS 10 VISUAL STUDIO CODE
 PROGRAM 6 GRAPHS
 * ************************/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//************************** Node *************************

class Node {
	public:
	Node(int value);

	private:
	int number;
	Node* next;
};

Node::Node(int value) {
	this->number = value;
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
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i]->number == nodeId) {
			//create a new node with the neighborId
			Node* newNode = new Node(neighborId);
			//set the next of the new node to the next of the node with the id of nodeId
			newNode->next = vertices[i]->next;
			//set the next of the node with the id of nodeId to the new node
			vertices[i]->next = newNode;
		}
	}
}

void Graph::loadGraph(string edgelistFileName){
	//reads the edge list from the file and use it to make a vector of linked lists
	ifstream inFile;
	inFile.open(edgelistFileName);
	if (inFile.is_open()) {
		int node1;
		int node2;
		
		while (inFile >> node1 >> node2) {
			//check if the node1 is already in the vector
			bool node1Found = false;
			for (int i = 0; i < vertices.size(); i++) {
				if (vertices[i]->number == node1) {
					node1Found = true;
				}
			}
			//if the node1 is not in the vector, add it
			if (!node1Found) {
				Node* newNode = new Node(node1);
				vertices.push_back(newNode);
			}
			//check if the node2 is already in the vector
			bool node2Found = false;
			for (int i = 0; i < vertices.size(); i++) {
				if (vertices[i]->number == node2) {
					node2Found = true;
				}
			}
			//if the node2 is not in the vector, add it
			if (!node2Found) {
				Node* newNode = new Node(node2);
				vertices.push_back(newNode);
			}
			//add the neighbor to the node
			addNeighbor(node1, node2);
		}
	}
}

void Graph::dumpGraph(string adjListFileName) {
	//read the vector created within loadGraph and for each element in the vector, print the whole linked list connected to it
	ofstream outFile;
	outFile.open(adjListFileName);
	if (outFile.is_open()) {
		for (int i = 0; i < vertices.size(); i++) {
			outFile << vertices[i]->number << " ";
			Node* temp = vertices[i]->next;
			while (temp != NULL) {
				outFile << temp->number << " ";
				temp = temp->next;
			}
			outFile << endl;
		}
	}
}

int Graph::getNumVertices() {
	//returns the number of nodes in the graph
	return vertices.size();
}

int Graph::getNumNeighbors(int nodeId) {
	//returns the number of neighbor (degree) of a node
	int numNeighbors = 0; //set the number of neighbors to 0
	for (int i = 0; i < vertices.size(); i++) { //loop through vertices
		if (vertices[i]->number == nodeId) { //if verticies at i is equal to the node id
			Node* temp = vertices[i]->next; //create a temp node and set it to the next of the node
			while (temp != NULL) { //while the temp node is not null
				numNeighbors++; //increment the number of neighbors
				temp = temp->next; //set the temp node to the next of the temp node
			}
		}
	}
	return numNeighbors; //return the number of neighbors
}

void Graph::printGraphInfo(){
	//Prints number of nodes, number of edges, and maximum degree on terminal
	int numNodes = getNumVertices(); //get the number of nodes
	int numEdges = 0; //set the number of edges to 0
	int maxDegree = 0; //set the max degree to 0
	for (int i = 0; i < vertices.size(); i++) { //loop through vertices
		int degree = getNumNeighbors(vertices[i]->number); //get the degree of the node at i
		if (degree > maxDegree) { //if the degree is greater than the max degree
			maxDegree = degree; //set the max degree to the degree
		}
		numEdges += degree; //increment the number of edges by the degree
	}
	cout << "Number of nodes: " << numNodes << endl;
	cout << "Number of edges: " << numEdges << endl;
	cout << "Maximum degree: " << maxDegree << endl;
}

void run(string edgeListFileName, string adjListFileName) {
	Graph graph;
	graph.loadGraph(edgeListFileName);
	graph.dumpGraph(adjListFileName);
	graph.printGraphInfo();
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
