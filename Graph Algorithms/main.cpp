// Neighbourhood matrix
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


vector<vector<int>> Adjacency_to_Incidence_matrix(vector<vector<int>> adjacency,int v,int e){
    vector<vector<int>> incidence(
        v,
        vector<int>(e)
    );
    int curr_edge=0;
    for (int i = 0; i < v; i++){
        for (int j = i+1; j < v; j++){
            if(adjacency[i][j]==1){
                incidence[i][curr_edge]=1;
                incidence[j][curr_edge]=1;
                curr_edge++;
            }
        }
    }
    return incidence;
}

vector<vector<int>> Adjacency_to_edge_list(vector<vector<int>> adjacency,int v,int e){
    vector<vector<int>> edge_list;
    for (int i = 0; i < v; i++){
        for (int j = i+1; j < v; j++){
            if(adjacency[i][j]==1){
                vector<int> edge = {i,j};
                edge_list.push_back(edge);
            }
        }
    }
    return edge_list;
}
vector<vector<int>> Adjacency_to_adjacency_list(vector<vector<int>> adjacency,int v,int e) {
    vector<vector<int>> adjacency_list;
    for (int i = 0; i < v; i++){
        vector<int> vec;
        for (int j = 0; j < v; j++){
            if(adjacency[i][j]==1){
                vec.push_back(j);
            }
        }
        adjacency_list.push_back(vec);
    }
    return adjacency_list;
}

vector<vector<int>> readFile(int v){
    vector<vector<int>> matrix;
    string filename("data2.csv");
    
    char byte = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        // return EXIT_FAILURE;
    }
    for (int k=0;k<v;k++){
        int i=0;
        vector<int> line;
        while (i<v){
            input_file.get(byte);
            if (byte=='0' || byte=='1'){
                line.push_back((int) byte -48);
                i++;
            }
        }
        matrix.push_back(line);
    }

    // cout << endl;
    input_file.close();
    return matrix;    
}
void printMatrix(vector<vector<int>> matrix){
        for (int i=0;i<matrix.size();i++){
            for (int j=0;j<matrix[i].size();j++){
                cout<<matrix[i][j]<<' ';
            }
        cout<<endl;
    }
}

int getEdges(vector<vector<int>> matrix){
    int e=0;
    for (int i=1;i<matrix.size();i++){
            for (int j=i+1;j<matrix[i].size();j++){
                e+=matrix[i][j];
            }
    }
    return e;
}
int main(){
    
    int v=10;
    vector<vector<int>> Adjacency_matrix = readFile(10); //neighborhood matrix
    // {
    // //   1 2 3 4
    //     {0,1,1,1},  //1
    //     {1,0,0,0},  //2
    //     {1,0,0,1},  //3
    //     {1,0,1,0}   //4
    // };
    int e=getEdges(Adjacency_matrix);
    cout<<e<<endl;
    

    vector<vector<int>> Incidence_matrix = Adjacency_to_Incidence_matrix(Adjacency_matrix,v,e);
    // {
    //     {1,1,1,0,},
    //     {1,0,0,0,},
    //     {0,1,0,1,},
    //     {0,0,1,1,}
    // };

    printMatrix(Incidence_matrix);
    vector<vector<int>> Edge_list = Adjacency_to_edge_list(Adjacency_matrix,v,e);
    // {
    //     {0,1,},
    //     {0,2,},
    //     {0,3,},
    //     {2,3,}
    // };
    vector<vector<int>> Adjacency_list = Adjacency_to_adjacency_list(Adjacency_matrix,v,e);
    // {
    //     {1,2,3,},
    //     {0,},
    //     {0,3,},
    //     {0,2,}
    // };
    return 0;
}