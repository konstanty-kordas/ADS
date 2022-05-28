import matplotlib.pyplot as plt
import pandas as pd
FILES =  ['3_1_adjl.csv','3_1_adjm.csv','3_1_edgel.csv','3_1_incm.csv']
REPRESENTATIONS = ["Adjecency List", "Adjcecency Matrix", "Edge List", "Incident Matrix"]

def ex3_1():
    df = pd.read_csv(FILES[0])
    df = df.groupby(["vertices"]).mean()
    print(df)
    df.rename(columns={"vertices":"vertices", "time" :REPRESENTATIONS[0] },inplace=True)
    for i in range(1,4):
        temp = pd.read_csv(FILES[i])
        temp = temp.groupby(["vertices"]).mean()
        temp.rename(columns={"vertices ":"vertices", "time" : REPRESENTATIONS[i]},inplace=True)
        df = df.merge(temp,how='left',on="vertices")
    print(df)
    df.plot()
    plt.show()

def ex3_2():
    df = pd.read_csv('topo.csv')
    df  =df.groupby(['vertices']).mean()
    print(df)
    df.plot()
    plt.show()
ex3_2()