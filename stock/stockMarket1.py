from datetime import timedelta, date
import subprocess
import numpy as numpy
import pandas as pd
from apyori import apriori
from itertools import combinations 



def daterange(date1, date2):
    for n in range(int ((date2 - date1).days)+1):
        yield date1 + timedelta(n)

f=open("date.txt","w")
start_dt = date(1986, 2, 20)
end_dt = date(1989, 3, 11)
for dt in daterange(start_dt, end_dt):
    f.write(dt.strftime("%Y-%m-%d"))
    f.write("\n")
subprocess.call(["cc", "stockk.c"])
subprocess.call("./a.out")


df = pd.read_csv('apron.csv')

df = df.dropna(how = 'all')

print(df.shape)

records = []

for i in range(0,df.shape[0]):
	records.append([str(df.values[i,j]) for j in range(0,df.shape[1])])

D = []
for i in range(0,df.shape[1]/2):
	D.append('D'+str(i))
	D.append('R'+str(i))

print("--------------------------------------------------")
print("Details of stock market:")
for i in range(0,len(records)):
	print(i+1,": ",records[i])
print("--------------------------------------------------")

c = 1
n = len(D)
while(c<n):
	comb = combinations(D,c)
	# print(list(comb))
	comb1 = []
	for each in list(comb):
	 comb1.append(list(each))
	# print(comb1)
	d = []
	for i in range(0,len(comb1)):
		d.append(0);

	#findin number of supCount
	for each in records:
		for each1 in comb1:
			flag = 1
			for each2 in each1:
				if(each2 not in each):
					flag = 0
			if(flag == 1):
				d[comb1.index(each1)] = d[comb1.index(each1)]+1
	#removing items with supcount less than 2
	for i in range(0,len(d)):
		if(d[i]<2):
			d[i]=0
			comb1[i]=[]
	# print(comb1)
	# print(d)
	while 0 in d:d.remove(0)
	while [] in comb1:comb1.remove([])
	if(c==2):
		if(len(d) >0):
			print("Id   Sup_count")
			for i in range(0,len(d)):
				print("If "+comb1[i][0]+" occurs then "+comb1[i][1]+" occurs")
		else:
			print("no combinations of count ",c," has sup count greater than 2")
	
	else:
		if(len(d) >0):
			print("Id   Sup_count")
			for i in range(0,len(d)):
				print(comb1[i],"   ",d[i])
		else:
			print("no combinations of count ",c," has sup count greater than 2")
	print(" ")
	D = []
	for each in comb1:
		for each1 in each:
			if(each1 not in D):
				D.append(each1)
	
	c=c+1

	n=len(D)
