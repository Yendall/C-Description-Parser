import csv
with open('../data/sets/ids.csv', 'rb') as csvfile:
    spamreader = csv.reader(csvfile, delimiter='\n')
    for row in spamreader:
        x = ', '.join(row) + ".txt"
        print ', '.join(row)