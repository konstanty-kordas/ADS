// Neighbourhood matrix
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
    private:
        void dfsTopo(int vertex);
        vector<int> visited;
        vector<vector<int>> AdjecencyMatrix;
        vector<vector<int>> IncidenceMatrix;
        vector<vector<int>> EdgeList;
        vector<vector<int>> AdjecencyList;
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
    this->edges = e;
    this->vertices = v;
    vector<int> vec(v,0);
    this->visited = vec;
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
    for (int i=0;i<incm[r1].size();i++){
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
    for (int i=0;i<10;i++){ //ADJECENCY MATRIX
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

int main(){
    // Graph g;
    // for (int k=0;k<5;k++){
    //     for (int i=0;i<11;i++){
    //         ostringstream oss;
    //         oss << "output/out_" << i<<".txt";
    //         g.readFile(oss.str());
    //         g.measureTime();
    //     }
    // }
    Graph g;
    // g.readFile("dag.txt");
    // g.sorted.clear();
    // g.topologicalSort();
    // for (int i=0;i<g.sorted.size();i++){
    //     cout<<g.sorted[i]<<" ";
    // }
    // cout<<endl;
    // g.printAdjecencyList();
    
    for (int i=0;i<22;i++){
        ostringstream oss;
        oss << "output/dag_" << i<<".txt";
        g.readFile(oss.str());
        g.sorted.clear();
        auto start = std::chrono::high_resolution_clock::now();
        g.topologicalSort();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::ofstream file;
        file.open("topo.csv",std::ios::app);
        file<<g.vertices<<','<<duration.count()<<std::endl;
        file.close();
    }
    
    return 0;
}