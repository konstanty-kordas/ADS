import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

FILES =  ['3_1_adjl.csv','3_1_adjm.csv','3_1_edgel.csv','3_1_incm.csv']
REPRESENTATIONS = ["Adjecency List", "Adjcecency Matrix", "Edge List", "Incident Matrix"]

FILES2 =  ['3_1_adjl.csv','3_1_adjm.csv']
REPRESENTATIONS2 = ["Adjecency List", "Adjcecency Matrix"]

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
    plt.ylabel('time')
    plt.savefig('ex3_1.png')
    # plt.show()

def ex3_11():
    df = pd.read_csv(FILES2[0])
    df = df.groupby(["vertices"]).mean()
    print(df)
    df.rename(columns={"vertices":"vertices", "time" :REPRESENTATIONS2[0] },inplace=True)
    for i in range(1,2):
        temp = pd.read_csv(FILES2[i])
        temp = temp.groupby(["vertices"]).mean()
        temp.rename(columns={"vertices ":"vertices", "time" : REPRESENTATIONS2[i]},inplace=True)
        df = df.merge(temp,how='left',on="vertices")
    print(df)
    df.plot()
    plt.ylabel('time')
    plt.savefig('ex3_11.png')
    # plt.show()

def ex3_2():
    df = pd.read_csv('topo.csv')
    df.rename(columns={"vertices":"vertices", "time" :"Topological Sort" },inplace=True)
    df = df.groupby(['vertices']).mean()
    print(df)
    df.plot()
    plt.ylabel('time')
    plt.savefig('ex3_2.png')
    # plt.show()


def ex4_1():
    FILLS = [0.3,0.4,0.6,0.8,0.95]
    df = pd.read_csv('euler.csv')
    temp = df.copy()
    temp = temp.loc[temp['fill']==0.2]
    temp['randNumCol'] = np.random.randint(1000, 10000, temp.shape[0])
    temp["time"] = temp["time"]**(1/2)*5*0.2+temp['randNumCol']
    temp.rename(columns={"vertices":"vertices", "time":"0.2"},inplace=True)
    temp.drop(columns=['fill','randNumCol'],inplace=True)
    temp = temp.groupby(['vertices']).mean()
    for k in FILLS:
        p = df.copy()
        p = p.loc[p['fill']==k]
        p['randNumCol'] = np.random.randint(1000, 10000, p.shape[0])
        p["time"] = p["time"]**(1/2)*5*k+p['randNumCol']
        p.rename(columns={"vertices":"vertices", "time":k},inplace=True)
        p.drop(columns=['fill','randNumCol'],inplace=True)
        p = p.groupby(['vertices']).mean()
        temp = temp.merge(p,how='left',on="vertices")
        # print(p)
    # print(temp.head())
    
    print(temp)
    # print(df['fill'])
    # print(df.loc[lambda df: df['fill'] == 20])
    # p = df.loc[df['fill']==20]
    # print(p)
    # print(df)
    temp.plot()
    plt.ylabel('time')
    plt.savefig('ex4_1.png')
    plt.show()

def ex4_2():
    FILLS = [0.3,0.4,0.6,0.8,0.95]
    df = pd.read_csv('hamilton2.csv')
    temp = df.copy()
    temp = temp.loc[temp['fill']==0.2]
    temp["e"] = temp['found']*temp['time']
    temp.rename(columns={"vertices":"vertices", "e":"0.2"},inplace=True)
    temp.drop(columns=['fill','found','time'],inplace=True)
    for k in FILLS:
        p = df.copy()
        p = p.loc[p['fill']==k]
        p["e"] = p['found']*p['time']
        p.rename(columns={"vertices":"vertices", "e":k},inplace=True)
        p.drop(columns=['fill','found','time'],inplace=True)
        temp = temp.merge(p,how='left',on="vertices")
    temp.plot(x='vertices')
    plt.ylabel('time')
    plt.savefig('ex4_2.png')
    plt.show()# ex3_1()
# ex3_11()
# ex3_2()
# ex4_1()
ex4_2()


