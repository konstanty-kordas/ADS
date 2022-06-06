#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include <bits/stdc++.h>


using namespace std;

class knapsack{
    public: 
        vector<int> weights;
        vector<int> values;
        int capacity;
        int itemsCount;
        vector<double> density;
        vector<int> solution;
        void Greedy();
        void Exhaustive();
        void Dynamic();
        vector<vector<int>> powerset;
        void preparePowerset();
        int calcScore(vector<int> subset);
        void prepare(int size, int limit);
};


void knapsack:: Greedy(){
    for (int i=0;i<this->itemsCount;i++){
        this->density[i] = (double)this->values[i]/(double)this->weights[i];
    }
    int curr_weight=0;
    int k;
    while (this->solution.size()<this->itemsCount){
        k = max_element(this->density.begin(),this->density.end()) - this->density.begin();
        curr_weight+=weights[k];
        if (curr_weight>this->capacity){
            return;
        }
        this->solution.push_back(k);
        this->density[k] = 0;
    }
}


void knapsack::Exhaustive(){
    this->preparePowerset();
    int bestScore = 0;
    int bestScoreid = 0;
    int temp;
    for (int i=0;i<this->powerset.size();i++){
        temp = this->calcScore(this->powerset[i]);
        if (temp>bestScore){
            bestScore = temp;
            bestScoreid = i;
        }
    }
    this->solution =  powerset[bestScoreid];
}

void knapsack::Dynamic(){
    int arr[(this->itemsCount)+1][(this->capacity)+1];
    for(int i=0;i<(this->itemsCount)+1;i++){
        for (int j=0;j<(this->capacity)+1;j++){
            if (i==0){
                arr[i][j]=0;
                continue;
            }
            if (j==0){
                arr[i][j]=0;
                continue;
            }
            if (weights[i-1]>j){
                arr[i][j] = arr[i-1][j];
                continue;
            }
            else {
                arr[i][j] = max(arr[i-1][j],arr[i-1][j-this->weights[i-1]]+this->values[i-1]);
            }
        }
    }
    vector<int> sol;
    int i = (this->itemsCount);
    int j = (this->capacity);
    while (i!=0){
        if (j-this->weights[i-1]<0){
            i--;
            continue;
        }
        if (arr[i-1][j]!=arr[i][j]){
            sol.push_back(i-1);
            j-=this->weights[i-1];
        }
        i--;
    }
    this->solution = sol;
    // cout<<arr[i][j]<<endl;
    // for (int i=0;i<(this->itemsCount)+1;i++){
    //     for (int j=0;j<(this->capacity)+1;j++){
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}
int knapsack::calcScore(vector<int> subset){
    int totalScore = 0;
    int totalWeight = 0;
    for (int i = 0;i<subset.size();i++){
        totalScore+=this->values[subset[i]];
        totalWeight+=this->weights[subset[i]];
    }
    if (totalWeight>this->capacity){
        totalScore = 0;
    }
    return totalScore;
}


void knapsack::preparePowerset(){
    vector<vector<int>> all;
    vector<int> v;
    int size = this->itemsCount;
    int x = 0;
    for (int i=0;i<size;i++){
        x = all.size();
        for (int j=0;j<x;j++){
            v = all[j];
            v.push_back(i);
            all.push_back(v);
            v.clear();
        }
        vector<int> x (1,i);
        all.push_back(x);
    }
    this->powerset = all;
}

int rand50(){
    int p = 1 + rand()%10;
    return p;
}


void knapsack::prepare(int size, int limit){
    vector<int> vals(size,0);
    vector<int> weights(size,0);
    generate(vals.begin(), vals.end(), rand50); 
    generate(weights.begin(),weights.end(),rand50);
    this->values = vals;
    this->weights = weights;
    this->itemsCount = size;
    this->capacity = limit;
    vector<double> d(size,0);
    this->density = d;
}


int main(){
    srand(time(0));
    for (int SIZE = 10;SIZE<30;SIZE+=1){
        for (int LIMIT = 30;LIMIT<121;LIMIT+=15){
            knapsack k;
            k.prepare(SIZE,LIMIT);

            auto start = std::chrono::high_resolution_clock::now();
            k.Dynamic();
            auto stop = std::chrono::high_resolution_clock::now();
            // cout<<"DYNAMIC"<<endl<<k.itemsCount<<endl;
            // for (int i=0;i<k.solution.size();i++){
            //     cout<<k.solution[i]<<'\t';
            // }
            // cout<<endl;
            // cout<<k.calcScore(k.solution)<<endl;
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::ofstream file;
            file.open("dynamic.csv",std::ios::app);
            file<<SIZE<<","<<LIMIT<<','<<duration.count()<<','<<k.calcScore(k.solution)<<std::endl;
            file.close();
            k.solution.clear();


            start = std::chrono::high_resolution_clock::now();
            k.Greedy();
            stop = std::chrono::high_resolution_clock::now();
            // cout<<"GREEDY"<<endl;
            // for (int i=0;i<k.solution.size();i++){
            //     cout<<k.solution[i]<<'\t';
            // }
            // cout<<endl;
            // cout<<k.calcScore(k.solution)<<endl;
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            file.open("greedy.csv",std::ios::app);
            file<<SIZE<<","<<LIMIT<<','<<duration.count()<<','<<k.calcScore(k.solution)<<std::endl;
            file.close();
            k.solution.clear();


            start = std::chrono::high_resolution_clock::now();
            k.Exhaustive();
            stop = std::chrono::high_resolution_clock::now();
            // for (int i=0;i<k.solution.size();i++){
            //     cout<<k.solution[i]<<'\t';
            // }
            // cout<<endl;
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            file.open("exhaustive.csv",std::ios::app);
            file<<SIZE<<","<<LIMIT<<','<<duration.count()<<','<<k.calcScore(k.solution)<<std::endl;
            file.close();
            k.solution.clear();
        }
    }
    return 0;
}