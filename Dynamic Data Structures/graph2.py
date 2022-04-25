from ast import Str
from xml.dom.minidom import Element
import matplotlib.pyplot as plt
import pandas as pd
STRUCTURES =  ['LIST','BST','BBST']
# STRUCTURES =  ['BST','BBST']
OPERATIONS = ["INSERT","REMOVE","SEARCH"]


df = pd.read_csv('data.csv')
data = df.loc[df['operation'] == OPERATIONS[2]]
data.drop('operation', axis=1, inplace=True)
d1 = data.loc[data['structure'] == STRUCTURES[0]]
d1.drop('structure', axis=1, inplace=True)
d1.rename(columns={"elements ":"elements", "time" :STRUCTURES[0] },inplace=True)
for i in STRUCTURES:
    if i==STRUCTURES[0]:
        continue
    temp = data.loc[data['structure'] == i]
    temp.drop('structure', axis=1, inplace=True)
    temp.rename(columns={"elements ":"elements", "time" :i },inplace=True)
    d1 = d1.merge(temp,how='left',on="elements")
# d3 = data.loc[data['structure'] == STRUCTURES[2]]
# d3.drop('structure', axis=1, inplace=True)
# d3.rename(columns={"elements ":"elements", "time" :STRUCTURES[2] },inplace=True)

# d1 = d1.merge(d3,how='left',on="elements")
print(d1)
d1.plot(x='elements',y=STRUCTURES)
plt.savefig("SEARCH.png")
# plt.show()

# print(d1)
# df.rename(columns={"Elements ":"Elements", "Time" :STRUCTURES[0] },inplace=True)
# for i in range(1,len(STRUCTURES)):
#     temp = pd.read_csv(STRUCTURES[i]+'.csv')
#     temp.rename(columns={"Elements ":"Elements", "Time" : STRUCTURES[i] },inplace=True)
#     df = df.merge(temp,how='left',on="Elements")
# print(df.columns)
# df.plot(x="Elements", y=EX1)
# plt.show()
# for i in STRUCTURES:
#     a = data.loc[data['structure']==i]
#     a.plot(x='elements', y='time')
# print(INSERT)
# plt.show()

