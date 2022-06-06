import random
import sys
sys.setrecursionlimit(20000)
def add_edge(arr):
    kl=random.sample(range(len(arr)), k=2)
    if arr[kl[0]][kl[1]]==1:
        return add_edge(arr)
    arr[kl[0]][kl[1]]=1
    arr[kl[1]][kl[0]]=1


def dfs(visited,v,m,start):
    visited[start]=True
    for i in range(v):
        if m[start][i]==1 and visited[i]==False:
            dfs(visited,v,m,i)

def get_ver(mat):
    h=random.sample(range(len(mat)), k=3)
    if mat[h[0]][h[1]]==1 or mat[h[0]][h[2]]==1 or mat[h[2]][h[1]]==1:
        return get_ver(mat)
    mat[h[0]][h[1]] = 1
    mat[h[1]][h[0]] = 1
    mat[h[0]][h[2]] = 1
    mat[h[2]][h[0]] = 1
    mat[h[2]][h[1]] = 1
    mat[h[1]][h[2]] = 1

def get_matrix(number_of_vertices,saturation):
    edges=int((number_of_vertices*(number_of_vertices-1))/2)*saturation
    matrix=[[0 for c in range(number_of_vertices)] for x in range(number_of_vertices)]
    edgecount=0
    while edgecount < edges:
        get_ver(matrix)
        edgecount+=3
    v=[False]*number_of_vertices
    dfs(v,number_of_vertices,matrix,0)
    if False in v:
        return get_matrix(number_of_vertices, saturation)
    for x in range(number_of_vertices):
        matrix[x]=str(matrix[x])[1:-1].replace(", ","")
    return matrix

step=20
saturations = [0.2, 0.3, 0.4, 0.6, 0.8, 0.95]

for x in range(10):
    for sat in saturations:
        filename = "ham/"+str(sat)+"/out_%s.txt" % (x)
        f = open(filename, 'w')
        m=get_matrix((x+1)*step, 0.2)
        for i in range((x+1)*step):
            f.write(m[i] + "\n")
        f.close()





