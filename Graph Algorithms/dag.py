import math
from pickle import TRUE
import random



def createDAG(VERTICES, name):
    while True:
        graph = [[i] for i in range(VERTICES)]
        edges = []
        while len(graph)>1:
            r1 = random.choice(graph)
            graph.remove(r1)
            r2 = random.choice(graph)
            graph.remove(r2)
            graph.append(r1+r2)
            for v1 in r1:
                for v2 in r2:
                    edges.append([v1,v2])
        graph = graph[0]
        edgeCount = math.ceil(VERTICES*VERTICES*0.3)
        while len(edges)>edgeCount:
            edges.pop(random.randint(0,len(edges)-1))

        print(len(edges)/(VERTICES*VERTICES))

        connected = set()
        for e in edges:
            connected.add(e[0])
            connected.add(e[1])
        if len(connected)==VERTICES:
            break

    matrix =[]
    for i in range(VERTICES):
        matrix.append([])
        for j in range(VERTICES):
            matrix[i].append(0)

    for e in edges:
        matrix[e[0]][e[1]]=1
    with open(name,'w') as file:
        for l in matrix:
            file.write(''.join([str(s) for s in l])+'\n')

step= 100
# createDAG(10,'dag.txt')
for i in range(16,30):
    createDAG((i+1)*step,"output/dag_%s.txt" % (i))