import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from sqlalchemy import true


FILL = [k for k in range(45,121,15)]

def v2():
    dyn = pd.read_csv('dynamic.csv')
    ex = pd.read_csv('exhaustive.csv')


    temp = dyn.copy()
    temp = temp.loc[temp['limit']==30]
    temp.rename(columns={"size":"size", "time":"Dynamic Capacity:"+str(30)},inplace=True)
    temp.drop(columns=['score','limit'],inplace=True)
    for k in FILL:
        p = dyn.copy()
        p = p.loc[p['limit']==k]
        p.rename(columns={"size":"size", "time":"Dynamic Capacity:"+str(k)},inplace=True)
        p.drop(columns=['limit','score'],inplace=True)
        temp = temp.merge(p,how='left',on="size")

    temp2 = ex.copy()
    temp2 = temp2.loc[temp2['limit']==30]
    temp2.rename(columns={"size":"size", "time":"Exhaustive Capacity:"+str(30)},inplace=True)
    temp2.drop(columns=['score','limit'],inplace=True)
    temp = temp.merge(temp2,how='left',on="size")

    for k in FILL:
        p = ex.copy()
        p = p.loc[p['limit']==k]
        p.rename(columns={"size":"size", "time":"Exhaustive Capacity:"+str(k)},inplace=True)
        p.drop(columns=['limit','score'],inplace=True)
        temp = temp.merge(p,how='left',on="size")
        # print(p)
    # print(temp.head())
    temp.plot(x='size')
    plt.savefig('5_ex&dyn.png')



def v3():
    dyn = pd.read_csv('dynamic.csv')
    t = dyn.copy()
    t = t.loc[t['limit']==30]
    t.rename(columns={"size":"size", "time":"Capacity: "+str(30)},inplace=True)
    t.drop(columns=['score','limit'],inplace=True)
    for k in FILL:
        p = dyn.copy()
        p = p.loc[p['limit']==k]
        p.rename(columns={"size":"size", "time":"Capacity: "+str(k)},inplace=True)
        p.drop(columns=['limit','score'],inplace=True)
        t = t.merge(p,how='left',on="size")
    t.plot(x='size')
    plt.savefig("5_dynamic.png")
    # plt.show()
def v4():
    dyn = pd.read_csv('dynamic.csv')
    dyn.drop(columns=['size','limit','time'], inplace=True)
    dyn.rename(columns={'score':'dynamic'}, inplace=True)
    dyn['row_num'] = np.arange(len(dyn))
    greedy = pd.read_csv('greedy.csv')
    greedy.drop(columns=['size','limit','time'], inplace=True)
    greedy.rename(columns={'score':'greedy'}, inplace=True)
    greedy['row_num'] = np.arange(len(greedy))
    greedy = greedy.merge(dyn, how='left',on='row_num')
    greedy['ERROR'] = abs((greedy['greedy']-greedy['dynamic'])/greedy['dynamic'])*100
    print(greedy['ERROR'].describe())


def v5():
    dyn = pd.read_csv('dynamic.csv')
    greed = pd.read_csv('greedy.csv')
    temp = dyn.copy()
    temp = temp.loc[temp['limit']==30]
    temp.rename(columns={"size":"size", "time":"Dynamic Capacity:"+str(30)},inplace=True)
    temp.drop(columns=['score','limit'],inplace=True)
    for k in FILL:
        p = dyn.copy()
        p = p.loc[p['limit']==k]
        p.rename(columns={"size":"size", "time":"Dynamic Capacity:"+str(k)},inplace=True)
        p.drop(columns=['limit','score'],inplace=True)
        temp = temp.merge(p,how='left',on="size")

    temp2 = greed.copy()
    temp2 = temp2.loc[temp2['limit']==30]
    temp2.rename(columns={"size":"size", "time":"Greedy Capacity:"+str(30)},inplace=True)
    temp2.drop(columns=['score','limit'],inplace=True)
    temp = temp.merge(temp2,how='left',on="size")

    for k in FILL:
        p = greed.copy()
        p = p.loc[p['limit']==k]
        p.rename(columns={"size":"size", "time":"Greedy Capacity:"+str(k)},inplace=True)
        p.drop(columns=['limit','score'],inplace=True)
        temp = temp.merge(p,how='left',on="size")
        # print(p)
    # print(temp.head())
    temp.plot(x='size')
    plt.savefig('gre&dyn.png')
v2()
v3()
v4()
v5()
# plt.show()
# dyn.plot()
# plt.show()