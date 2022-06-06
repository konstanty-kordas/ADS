#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Graph {       
    public:
        int vertices;        
        int edges;
        void readFile(string name);
        void printGraph();
        void printAdjecencyList();
        void measureTime();
        vector<int> sorted;
        void topologicalSort();
        void eulerian();
        bool eulerianExists();
        void printIncidenceMatrix();
        void printEulerianAdjecencyList();
        vector<vector<int>> eulerianlookup;
        int recCounter;
        bool Hamiltonian();
        bool hamCycleRec(int pos);
        int *HamiltonianPath;
        bool isSafe(int v, int pos);
        int counter;
		int findStartVert();
		bool isBridge(int u, int v);
		void fleuryAlgorithm(int start);
    private:
        void dfsEuler(int vertex);
        void dfsTopo(int vertex);
        vector<int> visited;
        vector<int> stackEuler;
        vector<vector<int>> AdjecencyMatrix;
        vector<vector<int>> IncidenceMatrix;
        vector<vector<int>> EdgeList;
        vector<vector<int>> AdjecencyList;
        vector<vector<int>> EulerianAdjL;

        void Adjacency_to_Incidence_matrix();
        void Adjacency_to_edge_list();
        void Adjacency_to_adjacency_list();
        void measureTimeAdjM(int r1,int r2);
        void measureTimeAdjL(int r1,int r2);
        void measureTimeEdgeL(int r1,int r2);
        void measureTimeIncM(int r1,int r2);
};

void Graph::printAdjecencyList(){
    for (int i=0;i<this->vertices;i++){
        cout<<i<<": ";
        for (int j=0;j<this->AdjecencyList[i].size();j++){
            cout<<AdjecencyList[i][j];
        }
        cout<<endl;
    }
}
void Graph::printEulerianAdjecencyList(){
    for (int i=0;i<this->vertices;i++){
        cout<<i<<": ";
        for (int j=0;j<this->EulerianAdjL[i].size();j++){
            cout<<EulerianAdjL[i][j];
        }
        cout<<endl;
    }
}
void Graph::printIncidenceMatrix(){
    for (int i=0;i<this->IncidenceMatrix.size();i++){
        // cout<<i<<": ";
        for (int j=0;j<this->IncidenceMatrix[i].size();j++){
            cout<<IncidenceMatrix[i][j];
        }
        cout<<endl;
    }
}
void Graph::readFile(string name){
    fstream newfile;
    vector<vector<int>> matrix;
    int e=0;
    int v=0;
    newfile.open(name,ios::in); 
    if (newfile.is_open()){   
        string tp;
            while(getline(newfile, tp)){
                v++;
                vector<int> a;
                for( int const& character : tp ) {
                    a.push_back(character-48);
                    e+=character-48;
                }
                matrix.push_back(a);
            }
        newfile.close();   //close the file object.
    }
    this->AdjecencyMatrix=matrix;
    this->edges = e/2;
    this->vertices = v;
    // vector<int> vec(v,0);
    // this->visited = vec;
    this->Adjacency_to_adjacency_list();
    // this->Adjacency_to_edge_list();
    // this->Adjacency_to_Incidence_matrix();
}

void Graph::Adjacency_to_Incidence_matrix(){
    int e = this->edges;
    int v = this->vertices;
    vector<vector<int>> matrix = this->AdjecencyMatrix;
    vector<vector<int>> incidence(
        v,
        vector<int>(e)
    );
    int curr_edge=0;
    for (int i = 0; i < v; i++){
        for (int j = i+1; j < v; j++){
            if(matrix[i][j]==1){
                incidence[i][curr_edge]=1;
                incidence[j][curr_edge]=1;
                curr_edge++;
            }
        }
    }
    this->IncidenceMatrix = incidence;
}

void Graph::Adjacency_to_edge_list(){
    int e = this->edges;
    int v = this->vertices;
    vector<vector<int>> matrix = this->AdjecencyMatrix;
    vector<vector<int>> edge_list;
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            if(matrix[i][j]==1){
                vector<int> edge = {i,j};
                edge_list.push_back(edge);
            }
        }
    }
    this->EdgeList = edge_list;
}
void Graph::Adjacency_to_adjacency_list() {
    int e = this->edges;
    int v = this->vertices;
    vector<vector<int>> matrix = this->AdjecencyMatrix;
    vector<vector<int>> adjacency_list;
    for (int i = 0; i < v; i++){
        vector<int> vec;
        for (int j = 0; j < v; j++){
            if(matrix[i][j]==1){
                vec.push_back(j);
            }
        }
        adjacency_list.push_back(vec);
    }
    this->AdjecencyList = adjacency_list;
}

void Graph::printGraph(){
    vector<vector<int>> matrix = this->AdjecencyMatrix;
    for (int i=0;i<matrix.size();i++){
        for (int j=0;j<matrix[i].size();j++){
            cout<<matrix[i][j]<<' ';
        }
        cout<<endl;
    }
}

int Graph::findStartVert(){
	for(int i = 0; i<this->vertices; i++){
		int deg = 0;
		for(int j = 0; j<this->vertices; j++){
			if(this->AdjecencyMatrix[i][j])
			deg++; //increase degree, when connected edge found
		}
      if(deg % 2 != 0) //when degree of vertices are odd
      return i; //i is node with odd degree
	}
   	return 0; //when all vertices have even degree, start from 0
}
bool Graph::isBridge(int u, int v){
	int deg = 0;
	for(int i = 0; i<this->vertices; i++)
			if(this->AdjecencyMatrix[v][i])
			deg++;
		if(deg>1){
			return false; //the edge is not forming bridge
		}
	return true; //edge forming a bridge
}

void Graph::fleuryAlgorithm(int start){
	static int edge = this->edges;
	for(int v = 0; v<this->vertices; v++){
		if(this->AdjecencyMatrix[start][v]){ //when (u,v) edge is presnt and not forming bridge
			if(edge <= 1 || !isBridge(start, v)){
				this->AdjecencyMatrix[start][v] = this->AdjecencyMatrix[v][start] = 0; //remove edge from graph
				edge--; //reduce edge
				fleuryAlgorithm(v);
			}
		}
	}
}
int main(){
    double fills[6] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};
    for (int j=0;j<6;j++){
        for (int i=0;i<10;i++){
            Graph *g = new Graph();
            ostringstream oss;
            oss << "euler/"<<fills[j] <<"/out_" << i<<".txt";
            // cout<<oss.str()<<endl;
            // return 0 ;
            g->readFile(oss.str());
            // continue;
            g->sorted.clear();
            // if (!g->eulerianExists()){
            //     continue;
            // }
            auto start = std::chrono::high_resolution_clock::now();
            g->fleuryAlgorithm(g->findStartVert());
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            // return 0;
            std::ofstream file;
            file.open("euler.csv",std::ios::app);
            file<<g->vertices<<','<<fills[j]<<','<<duration.count()<<std::endl;
            file.close();
            delete g;
        }
    }
}