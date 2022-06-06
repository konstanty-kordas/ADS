#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <fstream>

#include "sorts.h"
#include "distributions.h"


void prepare1(std::string name){
    std::ofstream file;
    file.open(name+".csv");
    file<<"Elements,Time"<<std::endl;
    file.close();
}

void prepare2(std::string name){
    std::ofstream file;
    file.open(name+".csv",std::ios::in);
    file<<"Elements,Time,Distribution"<<std::endl;
    file.close();

}

void timeSortBasic(int len, 
                    std::function<void(int, int*)> algorithm,
                    std::string algorithmName){
    int *arr = (int*)malloc(sizeof(int) * len);
    uniform(len,arr);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(len,arr);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::ofstream file;
    file.open(algorithmName+".csv",std::ios::app);
    file<<len<<','<<duration.count()<<std::endl;
    file.close();
}
void timeSort(int len, 
                    std::function<void(int, int*)> distribution,
                    std::string distributionName,
                    std::function<void(int, int*)> algorithm,
                    std::string algorithmName){
    int *arr = (int*)malloc(sizeof(int) * len);
    distribution(len,arr);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm(len,arr);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::ofstream file;
    file.open(algorithmName+".csv",std::ios::app);
    file<<len<<','<<duration.count()<<","<<distributionName<<std::endl;
    file.close();
}
int main(){   
    // prepare1("BS");
    // prepare1("HS");
    // prepare1("CS");
    // prepare1("ShS");
    int* q = (int*)malloc(sizeof(int) * 100);
    AShape(100,q);
    for (int i=0;i<100;i++){
        std::cout<<q[i]<<'\t';
    }
    std::cout<<std::endl<<"VSHAPE"<<std::endl<<std::endl<<std::endl;

    int* p = (int*)malloc(sizeof(int) * 100);
    VShape(100,p);
    for (int i=0;i<100;i++){
        std::cout<<p[i]<<'\t';
    }
    timeSort(100, AShape, "ASHAPE",QuickSort, "QS");
    timeSort(100, VShape, "VSHAPE",QuickSort, "QS");   
    // for (int k=99999;k<=100001;k++){
    //     timeSort(k, AShape, "ASHAPE",QuickSort, "QS");
    //     timeSort(k, VShape, "VSHAPE",QuickSort, "QS");   
    // }
    // srand(time(0));
    // prepare2("QS");

    // prepare2("MS");
    // for (int i=100;i<10000;i+=100){
    //     timeSortBasic(i, BubbleSort, "BS");
    //     timeSortBasic(i, HeapSort, "HS");
    //     timeSortBasic(i, CountingSort, "CS");
    //     timeSortBasic(i, ShellSort, "ShS");
    // }

    // for (int i=100;i<100000;i+=100){
    //     timeSort(i, uniform, "UNIFORM", QuickSort, "QS");
    //     timeSort(i, constant,"CONSTANT",QuickSort,"QS");

    //     timeSort(i, AShape, "ASHAPE",QuickSort, "QS");
    //     timeSort(i, VShape, "VSHAPE",QuickSort, "QS");


    //     timeSort(i, uniform, "UNIFORM", HeapSort, "HS2");
    //     timeSort(i, constant,"CONSTANT",HeapSort,"HS2");
    //     timeSort(i, ascending, "ASCENDING",HeapSort, "HS2");
    //     timeSort(i, descending,"DESCENDING",HeapSort, "HS2");
    //     timeSort(i, AShape, "ASHAPE",HeapSort, "HS2");
    //     timeSort(i, VShape, "VSHAPE",HeapSort, "HS2");


    //     timeSort(i, uniform, "UNIFORM", MergeSort, "MS");
    //     timeSort(i, constant,"CONSTANT",MergeSort,"MS");
    //     timeSort(i, ascending, "ASCENDING",MergeSort, "MS");
    //     timeSort(i, descending,"DESCENDING",MergeSort, "MS");
    //     timeSort(i, AShape, "ASHAPE",MergeSort, "MS");
    //     timeSort(i, VShape, "VSHAPE",MergeSort, "MS");
    // }
    return 0;   
}

