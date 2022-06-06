import matplotlib.pyplot as plt
import pandas as pd
EX1 =  ['BS','CS','HS','ShS']
EX1_MODIFIED = ['CS','HS','ShS']
EX2 = ['HS2','MS','QS']


def EX1Norm():
    df = pd.read_csv(EX1[0]+'.csv')
    df.rename(columns={"Elements ":"Elements", "Time" :EX1[0] },inplace=True)
    for i in range(1,len(EX1)):
        temp = pd.read_csv(EX1[i]+'.csv')
        temp.rename(columns={"Elements ":"Elements", "Time" : EX1[i] },inplace=True)
        df = df.merge(temp,how='left',on="Elements")
    print(df.columns)
    df.plot(x="Elements", y=EX1)
    plt.show()

def EX1mod():
    df = pd.read_csv(EX1_MODIFIED[0]+'.csv')
    df.rename(columns={"Elements ":"Elements", "Time" :EX1_MODIFIED[0] },inplace=True)
    for i in range(1,len(EX1_MODIFIED)):
        temp = pd.read_csv(EX1_MODIFIED[i]+'.csv')
        temp.rename(columns={"Elements ":"Elements", "Time" : EX1_MODIFIED[i] },inplace=True)
        df = df.merge(temp,how='left',on="Elements")
    print(df.columns)
    df.plot(x="Elements", y=EX1_MODIFIED)
    plt.show()



df = pd.read_csv(EX2[0]+'.csv')
df.rename(columns={"Elements ":"Elements", "Time" :EX2[0] },inplace=True)
for i in range(1,len(EX2)):
    temp = pd.read_csv(EX2[i]+'.csv')
    temp.rename(columns={"Elements ":"Elements", "Time" : EX2[i], "Distribution": "Distribution"},inplace=True)
    df = df.merge(temp,how='left',on=["Elements","Distribution"])

print(df.columns)
dists = df.Distribution.unique()
print(dists)
for d in dists:
    AV = df.loc[df['Distribution'] == d]
    AV.plot(x="Elements", y=EX2)
    # df["Distribution"].plot(x="Elements", y=EX2)
    plt.show()
