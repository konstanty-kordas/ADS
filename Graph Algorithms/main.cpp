// Neighbourhood matrix
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
using namespace std;


class Graph {       
    public:
        int vertices;        
        int edges;
        vector<vector<int>> AdjecencyMatrix;
        vector<vector<int>> IncidenceMatrix;
        vector<vector<int>> EdgeList;
        vector<vector<int>> AdjecencyList;
        void readFile(string name);
        void printGraph();
        vector<vector<int>> Adjacency_to_Incidence_matrix();
        vector<vector<int>> Adjacency_to_edge_list();
        vector<vector<int>> Adjacency_to_adjacency_list();
};

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
                for(int i=0; i < a.size(); i++) {
                    std::cout << a.at(i) << ' ';
                }
                cout<<endl;
                matrix.push_back(a);
            }
        newfile.close();   //close the file object.
    }
    this->AdjecencyMatrix=matrix;
    this->edges = e;
    this->vertices = v;
    this->Adjacency_to_adjacency_list();
    this->Adjacency_to_edge_list();
    this->Adjacency_to_Incidence_matrix();
}

vector<vector<int>> Graph::Adjacency_to_Incidence_matrix(){
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

vector<vector<int>> Graph::Adjacency_to_edge_list(){
    int e = this->edges;
    int v = this->vertices;
    vector<vector<int>> matrix = this->AdjecencyMatrix;
    vector<vector<int>> edge_list;
    for (int i = 0; i < v; i++){
        for (int j = i+1; j < v; j++){
            if(matrix[i][j]==1){
                vector<int> edge = {i,j};
                edge_list.push_back(edge);
            }
        }
    }
    this->EdgeList = edge_list;
}
vector<vector<int>> Graph::Adjacency_to_adjacency_list() {
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


bool measureAdj(vector<vector<int>> matrix){
    int v = matrix.size();
    for (int i=0;i<10;i++){
        bool exists = false;
        int r1 = rand()%v;
        int r2 = rand()%v;
        auto start = std::chrono::high_resolution_clock::now();
        if (matrix[r1][r2]==1){
            exists=true;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::ofstream file;
        file.open("3_1_adj.csv",std::ios::app);
        file<<v<<','<<duration.count()<<std::endl;
        file.close();
    }
}
int main(){
    Graph g;
    g.readFile("output/out_0.txt");
    g.printGraph();
    // print

    // srand(time(0));
    // int v=1000;
    // vector<vector<int>> Adjacency_matrix = readFile(10); //neighborhood matrix
    // // printMatrix(Adjacency_matrix);
    // int e=getEdges(Adjacency_matrix);
    // cout<<e<<endl;
    // measureAdj(Adjacency_matrix);
    // vector<vector<int>> Incidence_matrix = Adjacency_to_Incidence_matrix(Adjacency_matrix,v,e);
    // // {
    // //     {1,1,1,0,},
    // //     {1,0,0,0,},
    // //     {0,1,0,1,},
    // //     {0,0,1,1,}
    // // };

    // // printMatrix(Incidence_matrix);
    // vector<vector<int>> Edge_list = Adjacency_to_edge_list(Adjacency_matrix,v,e);
    // // {
    // //     {0,1,},
    // //     {0,2,},
    // //     {0,3,},
    // //     {2,3,}
    // // };
    // vector<vector<int>> Adjacency_list = Adjacency_to_adjacency_list(Adjacency_matrix,v,e);
    // // {
    // //     {1,2,3,},
    // //     {0,},
    // //     {0,3,},
    // //     {0,2,}
    // // };
    char tq;
    cin>>tq;
    return 0;
}