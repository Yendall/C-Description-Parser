from __future__ import print_function
import csv

matrix_file = open("matrix.csv","w+")
matrix_writer = csv.writer(matrix_file)
row_count = 0
val_count = 0
fuck_counter = 0
DataList = []
for x in range(0,256):
    with open(str(x)+'.csv', 'rb') as csvfile:
        reader = csv.reader(csvfile, delimiter='\n')
        for row in reader:
            DataList.append(','.join(row))

for x in range(0,len(DataList)):
    print(DataList[x],file = matrix_file)

matrix_file.close()