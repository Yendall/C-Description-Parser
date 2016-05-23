import csv
from stop_words import get_stop_words
from nltk.corpus import stopwords

# Get English stop words
stop_words = get_stop_words('english')

myfile = open('../data/stop_words.csv', 'wb')
wr = csv.writer(myfile, quoting=csv.QUOTE_ALL)
wr.writerow(stop_words)