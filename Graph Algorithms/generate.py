import numpy as np
import pandas as pd

n = 1000
size = int(n*(n-1)/2)
np.zeros(n*n)
density = int(np.floor(size*0.7))
# print(size)
print(density)

x = np.ones(density)
y = np.zeros(size-density)
# print(x)
# print(y)
x = np.concatenate((x,y))
np.random.shuffle(x)
print(x)
graph = np.zeros((n,n),dtype=int)
k=0
for i in range(n):
    for j in range(i+1,n):
        graph[i][j] = x[k]
        graph[j][i] = x[k]
        k+=1
print(graph)
print(graph.sum()/2)

graph.tofile('data2.csv', sep = ',')

