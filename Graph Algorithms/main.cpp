// Neighbourhood matrix
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <algorithm>
#include <sys/resource.h>
#include <cmath>

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


void Graph::measureTimeAdjM(int r1,int r2){
    vector<vector<int>> adj = this->AdjecencyMatrix;
    bool exists = false;
    auto start = std::chrono::high_resolution_clock::now();
    if (adj[r1][r2]==1){
        exists=true;
    }
    else{
        exists=false;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::ofstream file;
    file.open("3_1_adjm.csv",std::ios::app);
    file<<this->vertices<<','<<duration.count()<<std::endl;
    file.close();
}


void Graph::measureTimeEdgeL(int r1,int r2){
    vector<vector<int>> edgel = this->EdgeList;
    bool exists = false;
    auto start = std::chrono::high_resolution_clock::now();
    for (int j=0;j<edgel.size();j++){
        if (edgel[j][0]==r1){
            if (edgel[j][1]==r2){
                exists=true;
                break;
            }
        }
        if (edgel[j][0]==r2){
            if(edgel[j][1]==r1){
                exists=true;
                break;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::ofstream file;
    file.open("3_1_edgel.csv",std::ios::app);
    file<<this->vertices<<','<<duration.count()<<std::endl;
    file.close();
}


void Graph::measureTimeAdjL(int r1,int r2){
    vector<vector<int>> adjl = this->AdjecencyList;
    bool exists = false;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0;i<adjl[r1].size();i++){
        if (adjl[r1][i]==r2){
            exists=true;
            break;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::ofstream file;
    file.open("3_1_adjl.csv",std::ios::app);
    file<<this->vertices<<','<<duration.count()<<std::endl;
    file.close();
}


void Graph::measureTimeIncM(int r1,int r2){
    vector<vector<int>> incm = this->IncidenceMatrix;
    bool exists = false;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0;i<this->edges;i++){
        if (incm[r1][i]==1){
            if (incm[r2][i]==1){
                exists=true;
                break;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::ofstream file;
    file.open("3_1_incm.csv",std::ios::app);
    file<<this->vertices<<','<<duration.count()<<std::endl;
    file.close();
}


void Graph::measureTime(){
    for (int i=0;i<20;i++){ //ADJECENCY MATRIX
        int r1 = rand()%this->vertices;    
        int r2 = rand()%this->vertices;
        this->measureTimeAdjM(r1,r2);
        this->measureTimeIncM(r1,r2);
        this->measureTimeAdjL(r1,r2);
        this->measureTimeEdgeL(r1,r2);
    }
}

void Graph::topologicalSort(){
    for (int i=0;i<this->vertices;i++){
        if (this->visited[i]==0){
            this->dfsTopo(i);
        }
    }
    reverse(this->sorted.begin(), this->sorted.end());
}

void Graph::dfsTopo(int vertex){
    if (this->visited[vertex]==0){
        return;
    }
    this->visited[vertex]=1;
    for (int i=0;i<this->AdjecencyList[vertex].size();i++){
            this->dfsTopo(this->AdjecencyList[vertex][i]);
        }
    this->sorted.push_back(vertex);
}

bool Graph::eulerianExists(){
    for (int i=0;i<this->vertices;i++){
        // cout<<this->AdjecencyList[i].size()<<endl;
        if ((this->AdjecencyList[i].size()%2!=0) || (this->AdjecencyList[i].size()==0)){
            
            return false;
        }
    }
    return true;
}
void Graph::eulerian(){
    this->recCounter = 0;
    this->EulerianAdjL = this->AdjecencyList;
    dfsEuler(0);
    // for (int i=0;i<this->stackEuler.size();i++){
    //     cout<<stackEuler[i]<<'\t';
    // }

    // cout<<endl;
}

void Graph::dfsEuler(int vertex){
    this->recCounter++;
    while (this->EulerianAdjL[vertex].size()!=0){
        int nextVertex = this->EulerianAdjL[vertex][0];
        this->EulerianAdjL[vertex].erase(this->EulerianAdjL[vertex].begin());
        remove(this->EulerianAdjL[nextVertex].begin(),
                this->EulerianAdjL[nextVertex].end(),
                vertex);
        this->EulerianAdjL[nextVertex].pop_back();
        // cout<<vertex<<'\t'<<nextVertex<<endl;
        // this->printEulerianAdjecencyList();
        // cout<<endl;
        dfsEuler(nextVertex);
    }
    this->stackEuler.push_back(vertex);
}
bool Graph::isSafe(int v, int pos)
{
	if (this->AdjecencyMatrix [this->HamiltonianPath[pos - 1]][ v ] == 0)
		return false;

	for (int i = 0; i < pos; i++)
		if (this->HamiltonianPath[i] == v)
			return false;

	return true;
}

bool Graph::hamCycleRec(int pos)
{
    if ((this->counter)>1000000*this->vertices){
        return false;
    }
    this->counter++;

	if (pos == this->vertices)
	{

		if (this->AdjecencyMatrix[this->HamiltonianPath[pos - 1]][this->HamiltonianPath[0]] == 1)
			return true;
		else
			return false;
	}
	for (int v = 1; v < this->vertices; v++)
	{
		if (isSafe(v, pos))
		{
			this->HamiltonianPath[pos] = v;

			if (hamCycleRec ( pos + 1) == true)
				return true;


			this->HamiltonianPath[pos] = -1;
		}
	}

	return false;
}


bool Graph::Hamiltonian()
{
	int *path = new int[this->vertices];
	for (int i = 0; i < this->vertices; i++)
		path[i] = -1;
    this->HamiltonianPath = path;
	path[0] = 0;
	if (hamCycleRec(1) == false )
	{
		// cout << "\nSolution does not exist";
		return false;
	}
	// for (int i = 0; i < this->vertices; i++)
		// cout << this->HamiltonianPath[i] << " ";
	return true;
}

int main(){
    //  rlimit R; // Unsigned integral type used for limit values.
    // getrlimit(RLIMIT_STACK, &R);
    // R.rlim_cur = R.rlim_max; // Limit on stack size. 
    // setrlimit(RLIMIT_STACK, &R);
    // for (int i=7;i<11;i++){
    //     Graph* g = new Graph();
    //     ostringstream oss;
    //     oss << "output/out_" << i<<".txt";
    //     g->readFile(oss.str());
    //     g->measureTime();
    //     delete g;
    // }
    

    // for (int i=0;i<22;i++){
    //     Graph *g = new Graph();
    //     ostringstream oss;
    //     oss << "output/dag_" << i<<".txt";
    //     g->readFile(oss.str());
    //     g->sorted.clear();
    //     auto start = std::chrono::high_resolution_clock::now();
    //     g->topologicalSort();
    //     auto stop = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //     std::ofstream file;
    //     file.open("topo.csv",std::ios::app);
    //     file<<g->vertices<<','<<duration.count()<<std::endl;
    //     file.close();
    //     delete g;
    // }


    double fills[6] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};
    for (int j=0;j<10;j++){
        for (int i=0;i<10;i++){
            Graph *g = new Graph();
            ostringstream oss;
            oss << "euler/"<<fills[j] <<"/out_" << i<<".txt";
            // cout<<oss.str()<<endl;
            // return 0 ;
            g->readFile(oss.str());
            // continue;
            g->sorted.clear();
            if (!g->eulerianExists()){
                continue;
            }
            auto start = std::chrono::high_resolution_clock::now();
            g->eulerian();
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
    // for (int i=0;i<7;i++){
    //     for (int j=0;j<6;j++){
    //         Graph *g = new Graph();
    //         ostringstream oss;
    //         oss << "ham/"<<fills[j] <<"/out_" << i<<".txt";
    //         // cout<<oss.str()<<endl;
    //         // return 0 ;
    //         g->readFile(oss.str());
    //         // continue;
    //         g->sorted.clear();
    //         auto start = std::chrono::high_resolution_clock::now();
    //         bool found = false;
    //         g->counter=0;
    //         if (g->Hamiltonian()){
    //             found  = true;
    //         }
    //         auto stop = std::chrono::high_resolution_clock::now();
    //         auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    //         // return 0;
    //         std::ofstream file;
    //         file.open("hamilton3.csv",std::ios::app);
    //         file<<g->vertices<<','<<fills[j]<<','<<duration.count()<<','<<found<<std::endl;
    //         file.close();
    //         delete g;
    //     }
    // }
    // Graph g;
    // // g.readFile("euler/0.2/out_0.txt");
    // g.readFile("euler.txt");
    // // vector<int> v{3,4,5,6,7,8,9};
    // // remove(v.begin(),v.end(),6);
    // // for (int i:v){
    // //     cout<<i<<'\t';
    // // }
    // // // cout<<"AA";
    // g.Hamiltonian();
    // // g.printAdjecencyList();
    // // cout<<g.edges;
    // // cout<<endl<<endl<<endl;
    // g.eulerian();
    // cout<<g.recCounter<<endl;
    return 0;
}