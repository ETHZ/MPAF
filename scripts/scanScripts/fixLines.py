import os

f = open("fileNames", "r")
ff = f.readlines()
f.close()

f = open("fileNamesV1", "w")

for l in ff:
	l = l.replace(".root", "")
	f.write(l)

f.close()
