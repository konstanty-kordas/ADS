import random
def add_edge(arr):
    kl=random.sample(range(len(arr)), k=2)
    if arr[kl[0]][kl[1]]==1:
        return add_edge(arr)
    arr[kl[0]][kl[1]]=1
    arr[kl[1]][kl[0]]=1


def get_matrix(number_of_vertices):
    ver=[x for x in range(number_of_vertices)]
    random.shuffle(ver)
    edges=(int(((number_of_vertices*(number_of_vertices-1))/2)*0.2)-len(ver))
    matrix=[[0 for c in range(number_of_vertices)] for x in range(number_of_vertices)]
    for x in range(number_of_vertices-1):
        matrix[ver[x]][ver[x+1]]=1
        matrix[ver[x+1]][ver[x]]=1
    edgecount=0
    while edgecount < edges:
        add_edge(matrix)
        edgecount+=1

    for x in range(number_of_vertices):
        matrix[x]=str(matrix[x])[1:-1].replace(", ","")
    return matrix

step=100
filename = ".txt"
f = open(filename, 'a')
m=get_matrix(10)
for i in range(10):
    f.write(m[i] + "\n")
f.close()
for x in range(10):
    filename = "output/ham_%s.txt" % (x)
    f = open(filename, 'a')
    m=get_matrix((x+1)*step)
    for i in range((x+1)*step):
        f.write(m[i] + "\n")
    f.close()





