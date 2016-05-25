import numpy
import csv
matrix_file = open("matrix.csv","w+")

for x in range(0,256):
    with open(str(x)+".txt","r") as ins:
        for line in ins:
            matrix_file.write(line)
            print line
matrix_file.close()
