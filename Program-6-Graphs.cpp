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
	//reads the edge list from the file and creates the adjacency list data structure
	ifstream inFile;
	inFile.open(edgelistFileName);
	if (inFile.is_open()) {
		int nodeId;
		int neighborId;
		while (inFile >> nodeId >> neighborId) {
			//add the node with neighborId as the neighbor of nodeId
			addNeighbor(nodeId, neighborId);
		}
	}
}

void Graph::dumpGraph(string adjListFileName) {
	//writes the adjacency list into the file
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

void Graph::printGraphInfo(){
	//Prints number of nodes, number of edges, and maximum degree on terminal
	int numNodes = getNumVertices();
	int numEdges = 0;
	int maxDegree = 0;
	for (int i = 0; i < vertices.size(); i++) {
		int degree = getNumNeighbors(vertices[i]->number);
		if (degree > maxDegree) {
			maxDegree = degree;
		}
		numEdges += degree;
	}
	cout << "Number of nodes: " << numNodes << endl;
	cout << "Number of edges: " << numEdges << endl;
	cout << "Maximum degree: " << maxDegree << endl;
}

int Graph::getNumNeighbors(int nodeId) {
	//returns the number of neighbor (degree) of a node
	int degree = 0;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i]->number == nodeId) {
			Node* temp = vertices[i]->next;
			while (temp != NULL) {
				degree++;
				temp = temp->next;
			}
		}
	}
	return degree;
}

int Graph::getNumVertices() {
	//returns the number of nodes in the graph
	return vertices.size();
}

void run(string edgeListFileName, string adjListFileName) {
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
