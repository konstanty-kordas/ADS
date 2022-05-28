import random

def get_matrix(number_of_vertices):
    matrix=[[0 for c in range(x)] + random.choices((1,0),weights=(6,4),k=(number_of_vertices-x)) for x in range(number_of_vertices)]
    for x in range(number_of_vertices):
        for y in range(x,number_of_vertices):
            if x==y:
                matrix[x][y]=0
            if matrix[x][y]==1:
                matrix[y][x]=1
        matrix[x]=str(matrix[x])[1:-1].replace(", ","")
    return matrix

step=100

for x in range(11):
    filename = "output/out_%s.txt" % (x)
    f = open(filename, 'a')
    m=get_matrix((x+1)*step)
    for i in range((x+1)*step):
        f.write(m[i] + "\n")
    f.close()