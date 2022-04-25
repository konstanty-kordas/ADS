import random
import string
f=open('e.csv','a')
for i in range(100):
    line = ""
    line+="".join(random.choices(string.ascii_lowercase,k=12))
    line+=","
    line+="".join(random.choices(string.ascii_lowercase,k=12))
    line+=","
    line+="".join(random.choices(string.digits,k=7))
    line+='\n'
    f.write(line)
f.close()
# print(line)